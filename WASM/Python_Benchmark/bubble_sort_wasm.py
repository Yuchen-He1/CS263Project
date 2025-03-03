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

# WebAssembly-compatible function
def run_bubble_sort(N):
    arr = [random.randint(0, 10000) for _ in range(N)]
    bubble_sort(arr)  # Sort array
    return arr  # Return sorted array (Pyodide allows returning lists)
