import random
from collections import defaultdict
from typing import List, Tuple, Dict

Point = Tuple[int, int]
BBox = Tuple[int, int, int, int]

W = 1024
H = 1024

# ----------------- scoring utils -----------------
def bbox_of(pts: List[Point]) -> BBox:
    xs = [p[0] for p in pts]
    ys = [p[1] for p in pts]
    return (min(xs), min(ys), max(xs), max(ys))

def area(b: BBox) -> int:
    x1, y1, x2, y2 = b
    return (x2 - x1 + 1) * (y2 - y1 + 1)

def sum_sq(hh: int) -> int:
    return (hh - 1) * hh * (2 * hh - 1) // 6

def score_from_bboxes(bboxes: List[BBox]) -> float:
    hh = len(bboxes)
    if hh == 0:
        return float("-inf")
    add = sum_sq(hh)
    areas = [area(b) for b in bboxes]
    mu = sum(areas) / hh
    pen = sum(abs(a - mu) / 10.0 for a in areas)
    return add - pen

# ----------------- pool packing: nearest 4 -----------------
def pack_pool_nearest4(pool: List[Point], rng: random.Random) -> Tuple[List[List[Point]], List[Point]]:
    """
    pool에서 4개씩 그룹을 만들되:
      - seed 1개 뽑고
      - 나머지 중 거리 가장 가까운 3개를 붙여서 4개 그룹 생성
    남는 1~3개는 leftover로 반환
    """
    groups: List[List[Point]] = []
    if len(pool) < 4:
        return groups, pool

    # 다양성 위해 한번 섞고 시작
    rng.shuffle(pool)

    # 리스트로 관리(2000 규모면 O(n^2)도 충분히 돌아감)
    pts = pool[:]  # copy

    while len(pts) >= 4:
        # seed 하나 고르기 (앞에서 pop)
        p = pts.pop()
        px, py = p

        # 남은 점들 중 가까운 3개 찾기
        # (n이 작으니 단순 선형 탐색으로도 충분)
        best = []
        for i, q in enumerate(pts):
            dx = q[0] - px
            dy = q[1] - py
            d2 = dx*dx + dy*dy
            best.append((d2, i))
        best.sort(key=lambda x: x[0])

        # 가까운 3개 선택
        idxs = sorted([best[0][1], best[1][1], best[2][1]], reverse=True)
        picked = [p]
        for idx in idxs:
            picked.append(pts.pop(idx))

        groups.append(picked)

    leftover = pts  # 0~3개
    return groups, leftover

# ----------------- tile pack core -----------------
def solve_tile_pack(points: List[Point], S: int, ox: int, oy: int, seed: int = 0):
    """
    - 타일 크기 S
    - 타일 오프셋 (ox, oy): 0 또는 S//2 권장
    - 타일 내부에서 4개씩 그룹 생성
    - 남는 자투리는 pool에 모은 뒤 '가까운 4개'로 재그룹
    - 마지막 1~3개는 마지막 그룹에 추가(요청사항)
    """
    rng = random.Random(seed)
    tiles: Dict[Tuple[int, int], List[Point]] = defaultdict(list)

    for x, y in points:
        tx = (x + ox) // S
        ty = (y + oy) // S
        tiles[(tx, ty)].append((x, y))

    for k in tiles:
        rng.shuffle(tiles[k])

    groups: List[List[Point]] = []
    pool: List[Point] = []

    # 1) 타일 내부 4개씩 생성, 남는 건 pool로
    for tid, pts in tiles.items():
        m = len(pts)
        q = (m // 4) * 4
        for i in range(0, q, 4):
            groups.append(pts[i:i+4])
        if q < m:
            pool.extend(pts[q:])

    # 2) pool을 '가까운 4개'로 묶기
    new_groups, leftover = pack_pool_nearest4(pool, rng)
    groups.extend(new_groups)

    # 3) leftover(1~3)는 마지막 그룹에 추가
    if leftover:
        if not groups:
            groups.append(leftover)
        else:
            groups[-1].extend(leftover)

    bboxes = [bbox_of(g) for g in groups]
    sc = score_from_bboxes(bboxes)
    return bboxes, sc, groups

# ----------------- sweep S + offsets -----------------
def solve_tile_sweep(points: List[Point],
                     S_candidates=(24, 32, 40, 48),
                     use_offsets=True,
                     seeds_per_setting: int = 3,
                     base_seed: int = 0):
    best = None  # (score, bboxes, groups, meta)
    for S in S_candidates:
        offsets = [(0, 0)]
        if use_offsets:
            h = S // 2
            offsets = [(0, 0), (h, 0), (0, h), (h, h)]

        for (ox, oy) in offsets:
            for t in range(seeds_per_setting):
                seed = base_seed + 100000 * S + 1000 * ox + 10 * oy + t
                bboxes, sc, groups = solve_tile_pack(points, S=S, ox=ox, oy=oy, seed=seed)
                meta = {"S": S, "ox": ox, "oy": oy, "seed": seed, "houses": len(bboxes)}
                if best is None or sc > best[0]:
                    best = (sc, bboxes, groups, meta)
    return best

# ----------------- demo -----------------
def generate_random_points(n: int, seed: int = 42) -> List[Point]:
    rng = random.Random(seed)
    idxs = rng.sample(range(W * H), n)
    return [(i % W, i // W) for i in idxs]

if __name__ == "__main__":
    pts = generate_random_points(2000, seed=42)

    best_score, best_bboxes, best_groups, meta = solve_tile_sweep(
        pts,
        S_candidates=(24, 28, 32, 36, 40, 48),
        use_offsets=True,
        seeds_per_setting=3,
        base_seed=123
    )

    print("BEST score:", best_score)
    print("Meta:", meta)
    print("Last group size:", len(best_groups[-1]))
