#include <iostream>
#include <vector>
using namespace std;

int main(void){
    int blocks, k, n, miss = 0; 
    cin >> blocks >> k >> n;
    int sets = blocks/k; 
    vector<vector<int> > cache(sets); // cache -> sets -> blocks
    for (int index=0; index<n; index++){
        bool found = false; 
        int data; 
        cin >> data;
        for(int i=0; i<sets; i++){
            for (int j=0; j<cache[i].size(); j++){
                // data is found 
                if (data == cache[i][j]){ 
                    // move data to the back (most recently used)
                    // cout << "[ O ] " << data << " found at (" << i << ", " << j << ")\n";
                    for(int l=j; l<cache[i].size()-1; l++){ 
                        cache[i][l] = cache[i][l+1];
                    } cache[i][cache[i].size()-1] = data;
                    found = true; 
                    break; 
                } 
            }
            if (found) break; 
        }
        if (!found){
            int s = index % sets; 
            // data is not found and set isn't full
            if (cache[s].size() < k){
                cache[s].push_back(data);
            } 
            // data is not found and set is full
            else {
                for (int j=0; j<k-1; j++){
                    cache[s][j] = cache[s][j+1];
                } cache[s][k-1] = data;
            }
            // cout << "[ X ] " << data << " pushed at (" << s << ", " << cache[s].size()-1 << ")\n";
            miss++;
        }
        // for(int i=0; i<sets; i++){
        //     cout << "cache " << i << ": ";
        //     for (int j=0; j<cache[i].size(); j++){
        //         cout << cache[i][j] << " ";
        //     } cout << endl; 
        // } cout << endl; 
    }
    cout << "Total Cache Misses:" << miss; 
    return 0;
}