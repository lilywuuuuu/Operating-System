#include <iostream>
#include <vector>
#include <queue>
using namespace std;

void print(vector<int> wait, vector<int> turnaround, int wait_sum, int turnaround_sum){
    for(int i=0; i<wait.size(); i++){
        cout << wait[i] << " " << turnaround[i] << endl;
    }
    cout << wait_sum << endl << turnaround_sum << endl;
}

bool FCFScompare(vector<int> a, vector<int> b) {
    return a[4] > b[4]; // smaller queue time first
}

bool SRTFcompare(vector<int> a, vector<int> b){
   if(a[2] - a[3] == b[2] - b[3]){ 
        return a[1] > b[1]; // if remaining time is the same, smaller arrival time is in front
    }
    return a[2] - a[3] > b[2] - b[3]; // burst time - process finished = remaining time 
}

bool RRcompare(vector<int> a, vector<int> b){
    if(a[4] == b[4]){ 
        return a[1] < b[1]; // if queue time is the same, larger arrival time is in front
    }
    return a[4] > b[4]; // smaller queue time first
}

void multilevel(vector<vector<int> > process, vector<int> queue, vector<int> time){
    vector<int> wait;
    vector<int> turnaround;
    vector<priority_queue<vector<int>, vector<vector<int> >, bool (*)(vector<int>, vector<int>)> > pqs;
    wait.resize(process.size(), 0);
    turnaround.resize(process.size());
    int wait_sum = 0;
    int turnaround_sum = 0;
    int timeline = 0; 
    int count = 0;
    int time_quantum;
    bool break_flag = false;

    bool (*comparator)(vector<int>, vector<int>);
    for (int i=0; i<queue.size(); i++){
        if (queue[i] == 0) comparator = FCFScompare;
        else if (queue[i] == 1) comparator = SRTFcompare;
        else if (queue[i] == 2) comparator = RRcompare;
        priority_queue<vector<int>, vector<vector<int> >, bool (*)(vector<int>, vector<int>)> pq(comparator);
        pqs.push_back(pq);
    }

    while(true){
        vector<int> top;
        int run_period;
        int compare_type;
        int next_queue_index; 
        bool empty_flag = false;

        // add new process into queue if time reached
        int del_count = 0;
        for(int i=0; i<process.size(); i++){ 
            if(process[i][0] <= timeline){ // arrival time <= timeline
                vector<int> new_process;
                new_process.resize(5);
                new_process[0] = count; // 第幾個 process
                new_process[1] = process[i][0]; // arrival time
                new_process[2] = process[i][1]; // burst time
                new_process[3] = 0; // process finished time
                new_process[4] = process[i][0]; // queue time
                count++;
                del_count++;
                pqs[0].push(new_process); // add to first pq
                // cout << "pushed: " << new_process[0] << " " << new_process[1] << " "  << new_process[2] << " "  << new_process[3] << " "  << new_process[4] << endl;
            }
        } process.erase(process.begin(), process.begin() + del_count);

        // find the highest priority, non-empty queue
        for(int i=0; i<pqs.size(); i++){
            if (!pqs[i].empty()){
                top = pqs[i].top();
                pqs[i].pop();
                compare_type = queue[i];
                next_queue_index = i + 1;
                if (compare_type == 2){
                    time_quantum = time[i];
                }
                break;
            }
            if ((i == pqs.size() - 1) && process.empty()){ // pqs are empty and there is no process left
                break_flag = true;
            }else if ((i == pqs.size() - 1) && (!process.empty())){ // pqs are empty but there are still processes left
                timeline++; // let timeline + 1 and continue
                empty_flag = true;
            }
        }
        if (break_flag) break; // no process left
        if (empty_flag) continue; // currently no process in queue
        run_period = top[2] - top[3]; // remaining time
        if ((compare_type == 2) && (run_period > time_quantum)){
            run_period = time_quantum;
        }
        // check for incoming process
        // only check if pq0 == SRTF or this isn't running on pq0
        if (((compare_type == 1) && (next_queue_index == 1)) || !(next_queue_index == 1)){
            // a new process comes in before this process finish its remaining time
            for (int i=0; i<process.size(); i++){
                // a new process comes in before this process finish its remaining time
                if(process[i][0] < timeline + run_period){ 
                    int time_to_next_proc = process[i][0] - timeline; 
                    int time_remaining_after_run_period = run_period - time_to_next_proc; 
                    if((next_queue_index == 1) && (process[i][1] >= time_remaining_after_run_period)){
                        continue;
                    }
                    run_period = process[i][0] - timeline; // new process arrival time - timeline
                    break;
                }
            }
        }
        wait[top[0]] += timeline - top[4]; // timeline - queue time
        top[3] += run_period;
        timeline += run_period;
        top[4] = timeline;
        if(top[2] == top[3]){ // process finished running
            wait_sum += wait[top[0]];
            turnaround[top[0]] = timeline - top[1]; // finish time - arrival time
            turnaround_sum += turnaround[top[0]];
        } else{ // process haven't finished
            if (next_queue_index < pqs.size()){ // if there's still queues after this one
                pqs[next_queue_index].push(top); // add to next queue down the priority
            }else{ // this is the last queue
                pqs[next_queue_index - 1].push(top);
            }
        }
        cout << top[0] << " ran for " << run_period << " from " << timeline-run_period << " to " << timeline << " in queue " << next_queue_index - 1 << endl;;
    }
    print(wait, turnaround, wait_sum, turnaround_sum);
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
    multilevel(process, queue_mode, time_quantum);

    return 0;
}