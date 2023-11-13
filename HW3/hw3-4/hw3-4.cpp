#include <atomic>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

using namespace std;

int n, m;
vector<uint64_t> subsets;
uint64_t one = static_cast<uint64_t>(1);
uint64_t global_count(0);
mutex mtx;

void solve(int start, int end) {
    uint64_t local_count = 0;
    for (int i = start; i <= end; i++) {
        uint64_t current = 0;
        for (int j = 0; j < m; j++) {
            if ((i & (1 << j)) != 0) {
                current |= subsets[j];
            }
        }
        if (current == (one << n) - 1) {
            local_count++;
        }
    }
    lock_guard<mutex> lock(mtx);
    global_count += local_count;
}

int main(int argc, char *argv[]) {
    int t = 1;
    if (argc > 2 && string(argv[1]) == "-t") // check if there's argument -t 
        t = stoi(argv[2]); // use t threads

    cin >> n >> m;

    subsets.resize(m);
    for (int i = 0; i < m; i++) {
        int p, temp;
        cin >> p;
        for (int j = 0; j < p; j++) {
            cin >> temp;
            subsets[i] |= (one << temp);
        }
    }

    vector<thread> threads;
    int num_per_t = (1 << m)/t; // num per thread
    for (int i = 0; i < t; i++) {
        int start = i * num_per_t;
        int end = (i == t - 1) ? (1 << m) - 1 : start + num_per_t - 1;
        threads.emplace_back(thread(solve, start, end));
        // cout << start << " " << end << endl;
    }

    for (auto &t : threads) {
        t.join();
    }

    cout << global_count << endl;
    return 0;
}
