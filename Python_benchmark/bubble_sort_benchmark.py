import time
import random

random.seed(42)

def bubble_sort(arr):
    N = len(arr)
    for i in range(N - 1):
        swapped = False
        for j in range(N - 1 - i):
            if arr[j] > arr[j + 1]:
                arr[j], arr[j + 1] = arr[j + 1], arr[j]
                swapped = True
        if not swapped:
            break

def main():
    N = int(input("Enter array size: "))
    arr = [random.randint(0, 10000) for _ in range(N)]
    
    start_time = time.perf_counter()
    bubble_sort(arr)
    end_time = time.perf_counter()
    
    print(f"Bubble Sort | Array Size: {N} | Time: {(end_time - start_time) * 1000:.2f} ms")

if __name__ == "__main__":
    main()
