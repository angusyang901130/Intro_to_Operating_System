#include <iostream>
#include <thread>
#include <cmath>
#include <vector>
#include <pthread.h>
#include <unistd.h>
using namespace std;

#define MAX 500
long long matA[MAX][MAX];
long long matB[MAX][MAX];
long long matC[MAX][MAX]; // Result of Addition
long long matD[MAX][MAX]; // Result of Multiplication

int thr_num, iter_per_thr;


void Addition(int srow, int erow){
    // Addition -> matC
    for (int i = srow; i < erow; ++i){
        for (int j = 0; j < MAX; ++j){
            matC[i][j] = matA[i][j] + matB[i][j];
        }   
    }
}

void Multiplication(int srow, int erow){
    // Multiplication -> matD
    for (int i = srow; i < erow; ++i) {
        for (int j = 0; j < MAX; ++j) {
            matD[i][j] = 0;

            for (int k = 0; k < MAX; ++k){ 
                matD[i][j] += matA[i][k] * matB[k][j];
            }
        }
    }
}

void* child_thread(void* n){

    long long thr_no = (long long)n;
    int start_row = thr_no * iter_per_thr;
    int end_row = (thr_no+1)*iter_per_thr >= MAX ? MAX : (thr_no+1)*iter_per_thr;

    Addition(start_row, end_row);
    Multiplication(start_row, end_row);

    pthread_exit(NULL); // exit child thread 
}

int main(){
    //get input
    cin.sync_with_stdio(0);
    cin.tie(0);

    thr_num = 10;
    iter_per_thr = ceil(MAX / (double)thr_num);

    for (int i = 0; i < MAX; ++i) 
        for (int j = 0; j < MAX; ++j) 
            cin >> matA[i][j];
        
    for (int i = 0; i < MAX; ++i) 
        for (int j = 0; j < MAX; ++j) 
            cin >> matB[i][j];
    
    vector<pthread_t> threads(thr_num);

    //int tmp = 0;
    for(long i = 0; i < thr_num; ++i)
        pthread_create(&threads[i], NULL, child_thread, (void*)i);
    
    for(int i = 0; i < thr_num; ++i)
        pthread_join(threads[i], NULL);
    
    // calculate SUM of matC
    long long sum_C = 0;
    for (int i = 0; i < MAX; ++i) 
        for (int j = 0; j < MAX; ++j)
            sum_C +=  matC[i][j];     
    
    cout << sum_C << '\n';

    // calculate SUM of matD
    long long sum_D = 0;
    for (int i = 0; i < MAX; ++i) 
        for (int j = 0; j < MAX; ++j)
            sum_D += matD[i][j];
    
    cout << sum_D << '\n';
    
    return 0;
}
