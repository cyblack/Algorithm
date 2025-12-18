import random
from typing import List, Tuple

Point = Tuple[int, int]
BBox = Tuple[int, int, int, int]  # (xmin, ymin, xmax, ymax)

def generate_random_points(n: int, W: int = 1024, H: int = 1024, seed: int = 42) -> List[Point]:
    rng = random.Random(seed)
    idxs = rng.sample(range(W * H), n)  # unique
    return [(i % W, i // W) for i in idxs]

def bbox_of(points: List[Point]) -> BBox:
    xs = [p[0] for p in points]
    ys = [p[1] for p in points]
    return (min(xs), min(ys), max(xs), max(ys))

def build_houses_top_left_chunks(points: List[Point]) -> Tuple[List[List[Point]], List[BBox]]:
    """
    1) 좌상단 가까운 순으로 정렬 (y 오름차순, x 오름차순)
    2) 앞에서부터 4개씩 그룹
    3) 남는 자투리(1~3)는 마지막 그룹에 추가
    4) 각 그룹 bbox 생성
    """
    pts = sorted(points, key=lambda p: (p[1], p[0]))  # top-left priority

    groups: List[List[Point]] = []
    i = 0
    while i + 4 <= len(pts):
        groups.append(pts[i:i+4])
        i += 4

    leftover = pts[i:]  # 0~3개
    if leftover:
        if not groups:
            groups.append(leftover)
        else:
            groups[-1].extend(leftover)

    bboxes = [bbox_of(g) for g in groups]
    return groups, bboxes

# ---- (옵션) 겹침 체크 ----
def bbox_overlap(b1: BBox, b2: BBox, include_boundary: bool = True) -> bool:
    x1, y1, x2, y2 = b1
    a1, b1y, a2, b2y = b2
    if include_boundary:
        if x2 < a1 or a2 < x1: return False
        if y2 < b1y or b2y < y1: return False
        return True
    else:
        if x2 <= a1 or a2 <= x1: return False
        if y2 <= b1y or b2y <= y1: return False
        return True

def check_overlaps(bboxes: List[BBox], include_boundary: bool = True, max_print: int = 10) -> int:
    cnt = 0
    H = len(bboxes)
    for i in range(H):
        for j in range(i+1, H):
            if bbox_overlap(bboxes[i], bboxes[j], include_boundary=include_boundary):
                cnt += 1
                if cnt <= max_print:
                    print(f"[OVERLAP] {i} {bboxes[i]} <-> {j} {bboxes[j]}")
    return cnt

if __name__ == "__main__":
    N = 2000
    points = generate_random_points(N, seed=42)

    groups, bboxes = build_houses_top_left_chunks(points)

    print("N:", N)
    print("Houses:", len(bboxes))
    print("Last group size:", len(groups[-1]))

    overlap_cnt = check_overlaps(bboxes, include_boundary=True, max_print=5)
    print("Overlap pairs:", overlap_cnt)
