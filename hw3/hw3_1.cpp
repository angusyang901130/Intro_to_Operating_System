#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

vector<pair<int, int>> arrival_order;
vector<int> task_time, arrive_time;

class Comp{
public:
    bool operator()(pair<int, int>& a, pair<int, int>& b){
        return a.first > b.first;
    }
};

bool cmp(pair<int, int>& a, pair<int, int>& b){
    if(a.first < b.first)
        return true;
    else if(a.first == b.first && task_time[a.second] < task_time[b.second])
        return true;
    else return false;
}

int main(){
    int n;
    cin >> n;
    
    arrival_order.resize(n);
    arrive_time.resize(n);
    task_time.resize(n);
    priority_queue<pair<int, int>, vector<pair<int, int>>, Comp> order;
    vector<int> finish_time(n);
    
    for(int i = 0; i < n; i++){
        pair<int, int> process;
        cin >> arrive_time[i];
        arrival_order[i] = make_pair(arrive_time[i], i);
    }

    for(int i = 0; i < n; i++)
        cin >> task_time[i];

    //vector<int> time_remain = task_time;

    sort(arrival_order.begin(), arrival_order.end(), cmp);
    pair<int, int> first_task = make_pair(task_time[arrival_order[0].second], arrival_order[0].second);
    order.push(first_task);
    
    int arr_idx = 1;
    int cur_time = arrival_order[0].first;

    while(arr_idx < n){
        //cout << "current time: " << cur_time << endl;

        if(order.empty()){
            cur_time = arrival_order[arr_idx].first;
            order.push(pair<int,int>(task_time[arrival_order[arr_idx].second], arrival_order[arr_idx].second));
            arr_idx++;
            continue;
        }

        pair<int,int> task = order.top();

        order.pop();
        task.first -= (arrival_order[arr_idx].first - cur_time);
        //cout << "current task is " << task.second << " and remaining time is " << task.first << endl;
        

        if(task.first <= 0){
            finish_time[task.second] = arrival_order[arr_idx].first + task.first;
            //cout << "finish time: " << finish_time[task.second] << endl;
            cur_time = finish_time[task.second];
        }else{
            order.push(task);
            cur_time = arrival_order[arr_idx].first;
        }

        if(cur_time < arrival_order[arr_idx].first)
            continue;

        order.push(pair<int,int>(task_time[arrival_order[arr_idx].second], arrival_order[arr_idx].second));
        arr_idx++;
    }

    while(!order.empty()){
        pair<int, int> task = order.top();
        finish_time[task.second] = cur_time + task.first;
        order.pop();

        cur_time = finish_time[task.second];
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