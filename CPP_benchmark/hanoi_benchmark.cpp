#include <iostream>
#include <chrono>

using namespace std;
using namespace chrono;

void hanoi(int n, char from, char aux, char to) {
    if (n == 1) return;
    hanoi(n - 1, from, to, aux);
    hanoi(n - 1, aux, from, to);
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <num_disks>" << endl;
        return 1;
    }

    int n = stoi(argv[1]);
    auto start = high_resolution_clock::now();
    hanoi(n, 'A', 'B', 'C');
    auto end = high_resolution_clock::now();

    cout << "Hanoi | Disks: " << n 
         << " | Time: " << duration<double, milli>(end - start).count() << " ms" << endl;
    return 0;
}
