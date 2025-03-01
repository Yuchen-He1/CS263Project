#include <iostream>
#include <chrono>
using namespace std;

void moveDisk(int n, char from, char to) {
    // move procedure
    // cout << "Move disk " << n << " from " << from << " to " << to << endl;
}

void hanoi(int n, char from, char aux, char to) {
    if(n == 1) {
        moveDisk(n, from, to);
        return;
    }
    hanoi(n - 1, from, to, aux);
    moveDisk(n, from, to);
    hanoi(n - 1, aux, from, to);
}

int main() {
    int n = 25; // number of disks
    auto start = chrono::high_resolution_clock::now();

    hanoi(n, 'A', 'B', 'C');

    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start).count();
    cout << "Hanoi Time: " << duration << " ms" << endl;

    return 0;
}
