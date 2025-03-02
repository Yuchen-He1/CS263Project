import time
import random

def main():
    N = int(input("Enter array size: "))
    arr = [random.randint(0, 10000) for _ in range(N)]

    start_time = time.perf_counter()
    sorted_arr = sorted(arr)  # Python's built-in Timsort
    end_time = time.perf_counter()

    print(f"QuickSort | Array Size: {N} | Time: {(end_time - start_time) * 1000:.2f} ms")

if __name__ == "__main__":
    main()
