def hanoi(n, from_rod, aux_rod, to_rod):
    if n == 1:
        return
    hanoi(n - 1, from_rod, to_rod, aux_rod)
    hanoi(n - 1, aux_rod, from_rod, to_rod)

def run_hanoi(N):
    hanoi(N, 'A', 'B', 'C')
    return N  # Returning N just for WebAssembly integration
