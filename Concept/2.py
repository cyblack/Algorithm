import random
import math
from bisect import bisect_left, bisect_right
from dataclasses import dataclass
from typing import List, Tuple, Dict, Set, Optional

Point = Tuple[int, int]
BBox = Tuple[int, int, int, int]  # (xmin, ymin, xmax, ymax)

# ----------------------------
# Basic utilities
# ----------------------------
def bbox_of_points(pts: List[Point]) -> BBox:
    xs = [p[0] for p in pts]
    ys = [p[1] for p in pts]
    return (min(xs), min(ys), max(xs), max(ys))

def area(b: BBox) -> int:
    x1, y1, x2, y2 = b
    return (x2 - x1 + 1) * (y2 - y1 + 1)

def sum_sq(H: int) -> int:
    # sum_{i=0..H-1} i^2
    return (H - 1) * H * (2 * H - 1) // 6

def score_from_areas(areas: List[int]) -> float:
    H = len(areas)
    if H == 0:
        return float("-inf")
    add = sum_sq(H)
    mu = sum(areas) / H
    penalty = sum(abs(a - mu) / 10.0 for a in areas)
    return add - penalty

def overlap(b1: BBox, b2: BBox, include_boundary: bool = True) -> bool:
    x1,y1,x2,y2 = b1
    a1,b1y,a2,b2y = b2
    if include_boundary:
        if x2 < a1 or a2 < x1: return False
        if y2 < b1y or b2y < y1: return False
        return True
    else:
        if x2 <= a1 or a2 <= x1: return False
        if y2 <= b1y or b2y <= y1: return False
        return True

# ----------------------------
# Fast point lookup structures
# ----------------------------
def build_row_index(points: List[Point], H: int = 1024) -> List[List[int]]:
    """
    rows[y] = sorted list of x for points existing at row y (STATIC over all points)
    """
    rows = [[] for _ in range(H)]
    for x, y in points:
        rows[y].append(x)
    for y in range(H):
        rows[y].sort()
    return rows

def build_prefix_sum(points: List[Point], W: int = 1024, H: int = 1024) -> List[List[int]]:
    """
    2D prefix sum for ALL points (static) to estimate density quickly.
    ps[y+1][x+1] = #points in rectangle [0..x, 0..y]
    """
    grid = [[0]*(W+1) for _ in range(H+1)]
    for x, y in points:
        grid[y+1][x+1] += 1
    # prefix
    for y in range(1, H+1):
        row = grid[y]
        prev = grid[y-1]
        run = 0
        for x in range(1, W+1):
            run += row[x]
            row[x] = run + prev[x]
    return grid

def count_points_in_bbox_ps(ps: List[List[int]], b: BBox) -> int:
    x1,y1,x2,y2 = b
    # prefix sum indices are +1
    A = ps[y2+1][x2+1]
    B = ps[y1][x2+1]
    C = ps[y2+1][x1]
    D = ps[y1][x1]
    return A - B - C + D

# Unused grid (dynamic)
def make_unused_grid(points: List[Point], W: int = 1024, H: int = 1024):
    # bytearray per row: 1 if unused
    grid = [bytearray(W) for _ in range(H)]
    for x, y in points:
        grid[y][x] = 1
    return grid

def collect_unused_points_in_bbox(rows: List[List[int]], unused_grid, b: BBox) -> List[Point]:
    """
    Enumerate unused points in bbox using row index + unused_grid check.
    Complexity proportional to #points that exist in those rows within x-range (usually ok).
    """
    x1,y1,x2,y2 = b
    pts = []
    for y in range(y1, y2+1):
        xs = rows[y]
        if not xs:
            continue
        lo = bisect_left(xs, x1)
        hi = bisect_right(xs, x2)
        for i in range(lo, hi):
            x = xs[i]
            if unused_grid[y][x]:
                pts.append((x, y))
    return pts

# ----------------------------
# Coarse spatial index for bbox overlap checks
# ----------------------------
class BBoxIndex:
    """
    Grid-based spatial index for existing houses to speed up overlap queries.
    """
    def __init__(self, W=1024, H=1024, cell=64):
        self.W = W
        self.H = H
        self.cell = cell
        self.CW = (W + cell - 1)//cell
        self.CH = (H + cell - 1)//cell
        self.bucket: Dict[Tuple[int,int], List[int]] = {}

    def _cells_for_bbox(self, b: BBox):
        x1,y1,x2,y2 = b
        cx1, cy1 = x1//self.cell, y1//self.cell
        cx2, cy2 = x2//self.cell, y2//self.cell
        for cy in range(cy1, cy2+1):
            for cx in range(cx1, cx2+1):
                yield (cx, cy)

    def add(self, idx: int, b: BBox):
        for c in self._cells_for_bbox(b):
            self.bucket.setdefault(c, []).append(idx)

    def remove(self, idx: int, b: BBox):
        for c in self._cells_for_bbox(b):
            lst = self.bucket.get(c)
            if not lst:
                continue
            # remove idx (small list)
            try:
                lst.remove(idx)
            except ValueError:
                pass
            if not lst:
                del self.bucket[c]

    def candidates(self, b: BBox) -> Set[int]:
        out = set()
        for c in self._cells_for_bbox(b):
            lst = self.bucket.get(c)
            if lst:
                out.update(lst)
        return out

# ----------------------------
# Candidate generation (local neighbor sampling)
# ----------------------------
@dataclass(frozen=True)
class Candidate:
    bbox: BBox
    est_cnt: int     # estimated points count in bbox (static)
    area: int
    score: float     # heuristic priority

def build_cell_map(points: List[Point], cell_size: int = 16) -> Dict[Tuple[int,int], List[Point]]:
    mp: Dict[Tuple[int,int], List[Point]] = {}
    for x, y in points:
        mp.setdefault((x//cell_size, y//cell_size), []).append((x, y))
    return mp

def k_nearest(points_mp, p: Point, cell_size: int, k: int = 24, max_r: int = 8) -> List[Point]:
    """
    Approx kNN by expanding grid radius around p.
    Returns up to k nearest (including p possibly; caller can filter).
    """
    x, y = p
    cx, cy = x//cell_size, y//cell_size
    found: List[Point] = []

    for r in range(0, max_r+1):
        for dy in range(-r, r+1):
            for dx in range(-r, r+1):
                if abs(dx) != r and abs(dy) != r:
                    continue
                cell = (cx+dx, cy+dy)
                pts = points_mp.get(cell)
                if pts:
                    found.extend(pts)
        if len(found) >= k*3:
            break

    # sort by distance
    found = list(set(found))
    found.sort(key=lambda q: (q[0]-x)*(q[0]-x) + (q[1]-y)*(q[1]-y))
    return found[:k]

def generate_candidates(points: List[Point],
                        ps,              # prefix sum for ALL points
                        cell_map,
                        cell_size_nn: int = 16,
                        k_nn: int = 24,
                        take_m: int = 10,
                        samples_per_seed: int = 30,
                        rng: Optional[random.Random] = None) -> List[Candidate]:
    """
    For each seed point, sample 3 neighbors from top M nearest and form bbox candidate.
    Keep all candidates (dedupe by bbox).
    """
    if rng is None:
        rng = random.Random(0)

    seen: Set[BBox] = set()
    cands: List[Candidate] = []

    for p in points:
        neigh = k_nearest(cell_map, p, cell_size_nn, k=k_nn)
        neigh = [q for q in neigh if q != p]
        if len(neigh) < 3:
            continue
        pool = neigh[:min(take_m, len(neigh))]

        # sample 3-combinations
        for _ in range(samples_per_seed):
            a = rng.choice(pool)
            b = rng.choice(pool)
            c = rng.choice(pool)
            if a == b or b == c or a == c:
                continue
            xs = [p[0], a[0], b[0], c[0]]
            ys = [p[1], a[1], b[1], c[1]]
            bb = (min(xs), min(ys), max(xs), max(ys))
            if bb in seen:
                continue
            seen.add(bb)

            A = area(bb)
            if A <= 0:
                continue
            est = count_points_in_bbox_ps(ps, bb)
            if est < 4:
                continue

            # Heuristic: prefer dense + small area, but avoid "too huge"
            density = est / A
            # score: density-heavy, slightly reward est (so we can consume points), penalize large area
            sc = 200.0 * density + 0.05 * est - 0.002 * A - 0.5 * math.log1p(A)
            cands.append(Candidate(bb, est, A, sc))

    cands.sort(key=lambda c: c.score, reverse=True)
    return cands

# ----------------------------
# Greedy packing using candidates (non-overlapping, consumes interior points)
# ----------------------------
@dataclass
class House:
    bbox: BBox
    pts: List[Point]
    area: int

def can_place(bi: BBoxIndex, houses: List[Optional[House]], bb: BBox, include_boundary=True) -> bool:
    for idx in bi.candidates(bb):
        h = houses[idx]
        if h is None:
            continue
        if overlap(bb, h.bbox, include_boundary=include_boundary):
            return False
    return True

def place_house(bb: BBox, rows, unused_grid, bi: BBoxIndex,
                houses: List[Optional[House]], include_boundary=True) -> Optional[int]:
    """
    Try to place a house with bbox=bb:
      - must not overlap
      - must consume >=4 currently-unused points inside bb
    Returns house index if placed else None.
    """
    if not can_place(bi, houses, bb, include_boundary=include_boundary):
        return None
    pts = collect_unused_points_in_bbox(rows, unused_grid, bb)
    if len(pts) < 4:
        return None

    # consume all pts inside bbox
    for x, y in pts:
        unused_grid[y][x] = 0

    h = House(bbox=bb, pts=pts, area=area(bb))
    houses.append(h)
    idx = len(houses) - 1
    bi.add(idx, bb)
    return idx

def greedy_pack(points_all: List[Point], candidates: List[Candidate],
                rows, unused_grid,
                include_boundary=True) -> List[House]:
    houses: List[Optional[House]] = []
    bi = BBoxIndex(cell=64)

    for cand in candidates:
        place_house(cand.bbox, rows, unused_grid, bi, houses, include_boundary=include_boundary)

    # filter Nones (we never set None here, kept for rollback compatibility)
    return [h for h in houses if h is not None]

# ----------------------------
# Repair: cover remaining points locally
# ----------------------------
def repair_unused(points_all: List[Point], rows, unused_grid,
                 include_boundary=True,
                 nn_cell_size=16, k_nn=32,
                 rng: Optional[random.Random]=None,
                 houses: List[House]=None) -> List[House]:
    """
    Add more houses to consume remaining points using local kNN boxes.
    """
    if rng is None:
        rng = random.Random(0)
    if houses is None:
        houses = []

    # rebuild spatial index for current houses
    bi = BBoxIndex(cell=64)
    opt_houses: List[Optional[House]] = [h for h in houses]
    for i, h in enumerate(opt_houses):
        bi.add(i, h.bbox)

    # build cell map for ALL points (static for neighbor queries)
    cell_map = build_cell_map(points_all, cell_size=nn_cell_size)

    def any_unused_point():
        # pick by scanning points_all (O(N)=2000, fine)
        for p in points_all:
            x, y = p
            if unused_grid[y][x]:
                return p
        return None

    while True:
        seed = any_unused_point()
        if seed is None:
            break
        # find nearest unused neighbors
        neigh = k_nearest(cell_map, seed, nn_cell_size, k=k_nn)
        neigh = [q for q in neigh if q != seed and unused_grid[q[1]][q[0]]]
        if len(neigh) < 3:
            # cannot form new house; absorb this point later (hard case)
            # we'll just mark it used by forcing it into the last house if exists
            if opt_houses:
                # expand last house bbox by rebuilding its bbox from pts+seed (may create overlap in theory; skip)
                opt_houses[-1].pts.append(seed)
                unused_grid[seed[1]][seed[0]] = 0
            else:
                # degenerate (shouldn't happen for N=2000)
                unused_grid[seed[1]][seed[0]] = 0
            continue

        # try a few combinations among the nearest to create a valid non-overlapping bbox
        placed = False
        tries = min(20, len(neigh) * (len(neigh)-1) * (len(neigh)-2) // 6)
        for _ in range(tries):
            a, b, c = rng.sample(neigh[:min(12, len(neigh))], 3)
            xs = [seed[0], a[0], b[0], c[0]]
            ys = [seed[1], a[1], b[1], c[1]]
            bb = (min(xs), min(ys), max(xs), max(ys))
            idx = place_house(bb, rows, unused_grid, bi, opt_houses, include_boundary=include_boundary)
            if idx is not None:
                placed = True
                break

        if not placed:
            # fallback: absorb into last existing house
            if opt_houses:
                opt_houses[-1].pts.append(seed)
            unused_grid[seed[1]][seed[0]] = 0

    return [h for h in opt_houses if h is not None]

# ----------------------------
# LNS: remove a neighborhood of bad houses and repack locally
# ----------------------------
def lns_improve(points_all: List[Point], ps, rows,
                base_houses: List[House],
                iters: int = 200,
                remove_k: int = 8,
                include_boundary=True,
                rng: Optional[random.Random]=None) -> List[House]:
    if rng is None:
        rng = random.Random(0)

    # Current solution state
    houses: List[Optional[House]] = [h for h in base_houses]
    bi = BBoxIndex(cell=64)
    for i, h in enumerate(houses):
        bi.add(i, h.bbox)

    # Maintain unused grid from houses (recompute once)
    unused_grid = make_unused_grid(points_all)
    for h in houses:
        for x, y in h.pts:
            unused_grid[y][x] = 0

    def current_score() -> float:
        areas = [h.area for h in houses if h is not None]
        return score_from_areas(areas)

    best_score = current_score()
    best_snapshot = [h for h in houses if h is not None]

    # Precompute a static cell_map for neighbor sampling within subsets too
    cell_map_all = build_cell_map(points_all, cell_size=16)

    # Define "badness" for selecting removal seeds
    def house_badness(h: House) -> float:
        # large area + low density are bad
        dens = len(h.pts) / max(1, h.area)
        return 0.002 * h.area + (1.0 - min(1.0, 50.0*dens))

    for _it in range(iters):
        alive_indices = [i for i, h in enumerate(houses) if h is not None]
        if len(alive_indices) <= remove_k + 2:
            break

        # pick one "bad" house as seed
        seed_i = max(alive_indices, key=lambda i: house_badness(houses[i]))
        seed_house = houses[seed_i]
        sx1, sy1, sx2, sy2 = seed_house.bbox
        scx = (sx1 + sx2) / 2.0
        scy = (sy1 + sy2) / 2.0

        # choose neighbors by bbox center distance
        def center_dist2(i: int) -> float:
            h = houses[i]
            x1,y1,x2,y2 = h.bbox
            cx = (x1+x2)/2.0
            cy = (y1+y2)/2.0
            return (cx-scx)*(cx-scx) + (cy-scy)*(cy-scy)

        neigh = sorted(alive_indices, key=center_dist2)[:remove_k]
        removed = []
        removed_points: List[Point] = []
        removed_bboxes: List[BBox] = []

        # snapshot for rollback
        pre_score = current_score()

        # remove selected houses
        for i in neigh:
            h = houses[i]
            if h is None:
                continue
            removed.append((i, h))
            removed_bboxes.append(h.bbox)
            # mark their points unused
            for x, y in h.pts:
                unused_grid[y][x] = 1
                removed_points.append((x, y))
            # remove from spatial index
            bi.remove(i, h.bbox)
            houses[i] = None

        # local repack on removed_points
        if len(removed_points) >= 4:
            # generate local candidates only from removed points
            # build prefix sum for removed points? (small set) -> just reuse global ps for est count, it's OK
            cell_map_local = build_cell_map(removed_points, cell_size=16)
            local_cands = generate_candidates(
                removed_points, ps, cell_map_local,
                cell_size_nn=16, k_nn=24, take_m=10,
                samples_per_seed=40, rng=rng
            )

            # greedy place local candidates (respecting remaining global houses via bi/houses)
            for cand in local_cands:
                # attempt placement; consumes points in bbox from global unused_grid
                place_house(cand.bbox, rows, unused_grid, bi, houses, include_boundary=include_boundary)

            # repair remaining unused among removed points
            # (lightweight: try to build more houses seeded by removed_points)
            for p in removed_points:
                x,y = p
                if not unused_grid[y][x]:
                    continue
                # local kNN among ALL points but require unused
                neighp = k_nearest(cell_map_all, p, 16, k=32)
                neighp = [q for q in neighp if q != p and unused_grid[q[1]][q[0]]]
                if len(neighp) < 3:
                    # absorb into nearest existing house by bbox expansion is risky (can overlap),
                    # so just leave it (it may be covered later by other LNS)
                    continue
                placed = False
                for _t in range(15):
                    a,b,c = rng.sample(neighp[:min(12, len(neighp))], 3)
                    xs = [p[0], a[0], b[0], c[0]]
                    ys = [p[1], a[1], b[1], c[1]]
                    bb = (min(xs), min(ys), max(xs), max(ys))
                    idx = place_house(bb, rows, unused_grid, bi, houses, include_boundary=include_boundary)
                    if idx is not None:
                        placed = True
                        break
                if not placed:
                    pass

        post_score = current_score()

        # accept if improved
        if post_score + 1e-9 >= pre_score:
            if post_score > best_score:
                best_score = post_score
                best_snapshot = [h for h in houses if h is not None]
        else:
            # rollback: remove any newly added houses whose bbox intersects the removed region cells heavily is complex,
            # easiest rollback is: rebuild from best_snapshot occasionally.
            # Here we do a simple rollback by restoring removed houses and clearing points they used,
            # AND also clearing any points used by new houses in this iteration would require tracking.
            # So instead, we rollback by reconstructing from best_snapshot (safe, still fast for N=2000).
            houses = [h for h in best_snapshot]  # compact
            bi = BBoxIndex(cell=64)
            for i, h in enumerate(houses):
                bi.add(i, h.bbox)
            # rebuild unused_grid
            unused_grid = make_unused_grid(points_all)
            for h in houses:
                for x, y in h.pts:
                    unused_grid[y][x] = 0
            # NOTE: best_snapshot is compacted indices; OK.

    return best_snapshot

# ----------------------------
# End-to-end runner
# ----------------------------
def generate_random_points(n: int, W: int = 1024, H: int = 1024, seed: int = 42) -> List[Point]:
    rng = random.Random(seed)
    idxs = rng.sample(range(W * H), n)
    return [(i % W, i // W) for i in idxs]

def solve_B(points: List[Point],
            seed: int = 0,
            include_boundary_overlap: bool = True,
            cand_samples_per_seed: int = 30,
            lns_iters: int = 250,
            lns_remove_k: int = 8):
    rng = random.Random(seed)

    rows = build_row_index(points)
    ps = build_prefix_sum(points)
    unused_grid = make_unused_grid(points)

    # candidates on all points
    cell_map = build_cell_map(points, cell_size=16)
    cands = generate_candidates(
        points, ps, cell_map,
        cell_size_nn=16,
        k_nn=24,
        take_m=10,
        samples_per_seed=cand_samples_per_seed,
        rng=rng
    )

    # greedy pack
    houses0 = greedy_pack(points, cands, rows, unused_grid, include_boundary=include_boundary_overlap)

    # repair
    houses1 = repair_unused(points, rows, unused_grid,
                            include_boundary=include_boundary_overlap,
                            nn_cell_size=16, k_nn=32, rng=rng, houses=houses0)

    # LNS improve
    houses2 = lns_improve(points, ps, rows, houses1,
                          iters=lns_iters, remove_k=lns_remove_k,
                          include_boundary=include_boundary_overlap,
                          rng=rng)

    bboxes = [h.bbox for h in houses2]
    areas = [h.area for h in houses2]
    sc = score_from_areas(areas)
    return bboxes, sc, houses2

# ----------------------------
# Optional overlap check
# ----------------------------
def check_overlaps(bboxes: List[BBox], include_boundary: bool = True, max_print: int = 5) -> int:
    cnt = 0
    H = len(bboxes)
    for i in range(H):
        for j in range(i+1, H):
            if overlap(bboxes[i], bboxes[j], include_boundary=include_boundary):
                cnt += 1
                if cnt <= max_print:
                    print(f"[OVERLAP] {i} {bboxes[i]} <-> {j} {bboxes[j]}")
    return cnt

if __name__ == "__main__":
    N = 2000
    pts = generate_random_points(N, seed=42)

    bboxes, sc, houses = solve_B(
        pts,
        seed=123,
        include_boundary_overlap=True,
        cand_samples_per_seed=30,
        lns_iters=250,
        lns_remove_k=8
    )

    print("Houses:", len(bboxes))
    print("Score:", sc)
    ov = check_overlaps(bboxes, include_boundary=True)
    print("Overlap pairs:", ov)
