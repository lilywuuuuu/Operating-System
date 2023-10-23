#include <iostream>
#include <queue>
#include <vector>
using namespace std;

void print(vector<int> wait, vector<int> turnaround, int wait_sum, int turnaround_sum){
    for(int i=0; i<wait.size(); i++){
        cout << wait[i] << " " << turnaround[i] << endl;
    }
    cout << wait_sum << endl << turnaround_sum << endl;
}

bool FCFScompare(vector<int> a, vector<int> b) {
    return a[1] > b[1];
}

void FCFS(vector<vector<int> > process){
    vector<int> wait;
    vector<int> turnaround;
    wait.resize(process.size());
    turnaround.resize(process.size());
    int wait_sum = 0;
    int turnaround_sum = 0;
    int timeline = 0; 
    bool (*comparator)(vector<int>, vector<int>);
    comparator = FCFScompare;
    priority_queue<vector<int>, vector<vector<int> >, bool (*)(vector<int>, vector<int>)> pq(comparator);

    for (int i=0; i<process.size(); i++){
        vector<int> temp;
        temp.resize(3);
        temp[0] = i; // 第幾個 process
        temp[1] = process[i][0]; // arrival time
        temp[2] = process[i][1]; // burst time
        pq.push(temp);
    }
    for (int i=0; i<process.size(); i++){
        vector<int> top = pq.top();
        pq.pop();
        if (timeline > top[1]){ // check if processor is empty upon arrival
            wait[top[0]] = timeline - top[1]; // timeline - arrival time
        }else { // came later than current timeline
            wait[top[0]] = 0;
            timeline += top[1] - timeline; // add onto timeline
        } 
        turnaround[top[0]] = wait[top[0]] + top[2]; // wait time + burst time 
        turnaround_sum += turnaround[top[0]];
        timeline += top[2];
        wait_sum += wait[top[0]];
    }
    print(wait, turnaround, wait_sum, turnaround_sum);
}

bool SRTFcompare(vector<int> a, vector<int> b) {
    if (a[2] - a[3] == b[2] - b[3]) {
        return a[0] > b[0];
    }
    return a[2] - a[3] > b[2] - b[3];
}

bool RRcompare(vector<int> a, vector<int> b) {
    if (a[4] == b[4]) {
        return a[1] < b[1];
    }
    return a[4] > b[4];
}

int main(void){
    // handle input
    int n, m; // # of queues, # of processes
    vector<int> queue_mode;
    vector<int> time_quantum;
    vector<vector<int> > process; // arrive time, burst time
    cin >> n >> m;
    queue_mode.resize(n);
    time_quantum.resize(n);
    process.resize(m);
    for(int i=0; i<m; i++){
        process[i].resize(2);
    }
    for(int i=0; i<n; i++){
        cin >> queue_mode[i] >> time_quantum[i];
    }
    for(int i=0; i<m; i++){
        cin >> process[i][0] >> process[i][1];
    }
    
    // handle CPU scheduling
    if (n == 1){ // if there's only one queue
        if (queue_mode[0] == 0){
            FCFS(process);
        }
    }

    return 0;
}