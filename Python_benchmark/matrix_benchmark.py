import time
import random

random.seed(42)

def multiply_matrices(A, B, N):
    C = [[0] * N for _ in range(N)]
    for i in range(N):
        for j in range(N):
            for k in range(N):
                C[i][j] += A[i][k] * B[k][j]
    return C

def main():
    N = int(input("Enter matrix size: "))
    
    A = [[random.randint(1, 10) for _ in range(N)] for _ in range(N)]
    B = [[random.randint(1, 10) for _ in range(N)] for _ in range(N)]

    start_time = time.perf_counter()
    C = multiply_matrices(A, B, N)
    end_time = time.perf_counter()

    print(f"Matrix Multiplication | Size: {N}x{N} | Time: {(end_time - start_time) * 1000:.2f} ms")

if __name__ == "__main__":
    main()
