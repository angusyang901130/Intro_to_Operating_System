#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int FIFO(vector<int>& frames, int max_frame){
    queue<int> q;
    vector<int> ref(21, 0);

    int cnt = 0, cur = 0, page_fault = 0;

    while(cnt < max_frame && cur < frames.size()){
        
        // frame already in queue
        if(ref[frames[cur]]){
            cur++;
            continue;
        }

        // new frame into queue
        // ref of new frame become 1
        q.push(frames[cur]);
        ref[frames[cur]] = 1;
        page_fault++;
        cur++;
        cnt++;
    }

    for(int i = cur; i < frames.size(); i++){
        // frame already in queue
        if(ref[frames[i]])
            continue;
        
        // choose the frame on the top become victim
        // ref of frame become 0
        // ref of new frame become 1
        // push the new frame into queue
        int rm = q.front();
        q.pop();
        ref[rm] = 0;
        ref[frames[i]] = 1;
        page_fault++;
        q.push(frames[i]);
    }

    return page_fault;
}

int LRU(vector<int>& frames, int max_frame){
    vector<int> q(max_frame, 0);
    vector<int> ref(21, -1);

    int cnt = 0, cur = 0, page_fault = 0;

    while(cnt < max_frame && cur < frames.size()){
        
        // frame already in queue
        if(ref[frames[cur]] >= 0){
            ref[frames[cur]] = cur;
            cur++;
            continue;
        }

        // new frame into queue
        // update reference time (the position in frames)
        q[cnt] = frames[cur];
        ref[frames[cur]] = cur;
        page_fault++;
        cur++;
        cnt++;
    }

    for(int i = cur; i < frames.size(); i++){

        // frame already in queue
        if(ref[frames[i]] >= 0){
            ref[frames[i]] = i;
            continue;
        }

        // choose the victim frame referenced the earliest
        // ref of victim frame become 0
        // ref of new frame become current time (position in frames)
        // replace the old frame with new frame
        int rm = 0;
        for(int j = 1; j < max_frame; j++){
            if(ref[q[j]] < ref[q[rm]])
                rm = j;
        }

        ref[q[rm]] = -1;
        q[rm] = frames[i];
        ref[frames[i]] = i;
        
        page_fault++;
    }

    return page_fault;
}

int LFU(vector<int>& frames, int max_frame){
    vector<int> q(max_frame, 0);
    vector<int> ref(21, 0);
    vector<int> order(21, -1);

    int cnt = 0, cur = 0, page_fault = 0;

    while(cnt < max_frame && cur < frames.size()){
        
        // frame already in queue
        if(ref[frames[cur]]){
            ref[frames[cur]]++;
            cur++;
            continue;
        }

        //cout << "frame " << frames[cur] << " has been pushed into queue" << endl;

        // new frame into queue
        // update frequency being referenced
        // update order vector, which shows the time the frame has been pushed into queue
        q[cnt] = frames[cur];
        order[frames[cur]] = cnt;
        ref[frames[cur]] = 1;
        page_fault++;
        cur++;
        cnt++;
    }

    for(int i = cur; i < frames.size(); i++){

        // frame already in queue
        if(ref[frames[i]]){
            ref[frames[i]]++;
            continue;
        }

        // choose the victim frame referenced the least times
        // if referenced times are equal, then check whose order is earlier
        int rm = 0;
        for(int j = 1; j < max_frame; j++){
            if(ref[q[j]] < ref[q[rm]])
                rm = j;
            else if(ref[q[j]] == ref[q[rm]] && order[q[j]] < order[q[rm]]){
                rm = j;
            }
        }

        //cout << "frame " << frames[i] << " has been pushed into queue" << endl;
        //cout << "frame " << q[rm] << " has been poped out of queue" << endl;

        // update the value in order vector of new frame, and reset the value of victim frame in order vector to -1 
        // ref of victim frame become 0
        // ref of new frame become 1
        // replace the old frame with new frame
        order[frames[i]] = i;
        order[q[rm]] = -1;
        ref[q[rm]] = 0;
        q[rm] = frames[i];
        ref[frames[i]] = 1;
        
        page_fault++;
    }

    return page_fault;
}

int main(){
    int max_frame, length;
    cin >> max_frame >> length;

    vector<int> frames(length);

    for(int i = 0; i < length; i++)
        cin >> frames[i];

    cout << FIFO(frames, max_frame) << endl;
    cout << LRU(frames, max_frame) << endl;
    cout << LFU(frames, max_frame) << endl;
}