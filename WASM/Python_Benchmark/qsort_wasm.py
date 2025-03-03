import random

random.seed(42)

def run_qsort(N):
    arr = [random.randint(0, 10000) for _ in range(N)]
    return sorted(arr)  # Python's built-in Timsort
