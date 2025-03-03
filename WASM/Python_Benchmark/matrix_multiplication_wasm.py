import random

random.seed(42)

def multiply_matrices(A, B, N):
    C = [[0] * N for _ in range(N)]
    for i in range(N):
        for j in range(N):
            for k in range(N):
                C[i][j] += A[i][k] * B[k][j]
    return C

def run_matrix_multiplication(N):
    A = [[random.randint(1, 10) for _ in range(N)] for _ in range(N)]
    B = [[random.randint(1, 10) for _ in range(N)] for _ in range(N)]
    
    return multiply_matrices(A, B, N)  # Returning the result for WebAssembly
