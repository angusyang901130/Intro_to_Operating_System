#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

vector<pair<int, int>> arrival_order;
vector<int> task_time, arrive_time;

bool cmp(pair<int, int>& a, pair<int, int>& b){
    if(a.first < b.first)
        return true;
    else if(a.first == b.first && task_time[a.second] < task_time[b.second])
        return true;
    else return false;
}

int main(){
    int n, tq;
    cin >> n;
    
    arrival_order.resize(n);
    arrive_time.resize(n);
    task_time.resize(n);
    vector<int> finish_time(n);
    
    for(int i = 0; i < n; i++){
        pair<int, int> process;
        cin >> arrive_time[i];
        arrival_order[i] = make_pair(arrive_time[i], i);
    }

    for(int i = 0; i < n; i++)
        cin >> task_time[i];

    //vector<int> time_remain = task_time;
    cin >> tq;

    queue<pair<int, int>> rr, fcfs;
    sort(arrival_order.begin(), arrival_order.end(), cmp);

    int arr_idx = 1;
    int cur_time = arrival_order[0].first;
    rr.push(pair<int,int>(task_time[arrival_order[0].second], arrival_order[0].second));

    bool mode = true;

    while(arr_idx < n){
        
        if(mode){

            /* if(rr.empty()){
                cur_time = arrival_order[arr_idx].first;
                rr.push(pair<int,int>(task_time[arrival_order[arr_idx].second], arrival_order[arr_idx].second));
                arr_idx++;
                continue;
            } */

            pair<int,int> task = rr.front();
            rr.pop();

            task.first -= tq;

            if(task.first <= 0){
                finish_time[task.second] = cur_time + tq + task.first;
                cur_time = finish_time[task.second];
                //cout << "current time: " << cur_time << endl;
            }else{
                cur_time += tq;
                //cout << "current time: " << cur_time << endl;
            }

            while(arr_idx < n && arrival_order[arr_idx].first <= cur_time){
                rr.push(pair<int,int>(task_time[arrival_order[arr_idx].second], arrival_order[arr_idx].second));
                arr_idx++;
            }

            if(task.first > 0)
                fcfs.push(task);

            if(rr.empty())
                mode = false;
        }else{
            if(fcfs.empty()){
                mode = true;
                rr.push(pair<int,int>(task_time[arrival_order[arr_idx].second], arrival_order[arr_idx].second));
                cur_time = arrival_order[arr_idx].first;
                //cout << "current time: " << cur_time << endl;
                arr_idx++;
                continue;
            }

            pair<int, int> task = fcfs.front();
            fcfs.pop();

            int time_interval = arrival_order[arr_idx].first - cur_time;
            if(time_interval >= task.first){
                finish_time[task.second] = cur_time + task.first;
                cur_time += task.first;
                //cout << "current time: " << cur_time << endl;
            }else{
                task.first -= time_interval;
                cur_time += time_interval;
                fcfs.push(task);
                rr.push(pair<int,int>(task_time[arrival_order[arr_idx].second], arrival_order[arr_idx].second));
                arr_idx++;
                mode = true;
            }
        }
    }

    while(!rr.empty()){
        pair<int, int> task = rr.front();
        task.first -= tq;
        rr.pop();
        if(task.first <= 0){
            finish_time[task.second] = cur_time + tq + task.first;
            cur_time = finish_time[task.second];
            //cout << "current time: " << cur_time << endl;
        }else{
            fcfs.push(task);
            cur_time += tq;
        }
    }   

    while(!fcfs.empty()){
        pair<int, int> task = fcfs.front();
        fcfs.pop();
        finish_time[task.second] = cur_time + task.first;
        cur_time = finish_time[task.second];
        //cout << "current time: " << cur_time << endl;
    }

    int total_waiting = 0;
    int total_turnaround = 0;
    for(int i = 0; i < n; i++){
        //cout << "arrival time of task " << i << " is " << arrive_time[i] << endl;
        //cout << "turn around time of task " << i << " is " << finish_time[i]-arrive_time[i] << endl;
        //cout << "waiting time of task " << i << " is " << finish_time[i]-arrive_time[i]-task_time[i] << endl;   
        cout << finish_time[i]-arrive_time[i]-task_time[i] << " " << finish_time[i]-arrive_time[i] << endl;
        total_waiting += finish_time[i]-arrive_time[i]-task_time[i];
        total_turnaround += finish_time[i]-arrive_time[i];
    }
    
    cout << total_waiting << endl;
    cout << total_turnaround << endl;
}