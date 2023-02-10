#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

using namespace std;

int main(){
    cout << "Main Process ID: " << getpid() << endl;
    pid_t pid;

    pid = fork(); // fork 1

    if(pid == 0){
        cout << "Fork 1: I'm the child " << getpid() << ", my parent is " << getppid() << "." << endl;
        pid = fork(); // fork 2
        if(pid == 0){
            cout << "Fork 2: I'm the child " << getpid() << ", my parent is " << getppid() << "." << endl;
            pid = fork(); // fork 3

            if(pid == 0){
                cout << "Fork 3: I'm the child " << getpid() << ", my parent is " << getppid() << "." << endl;
            }else if(pid > 0){
                wait(NULL);
            }
        }else if(pid > 0){
            wait(NULL);
        }
    }else if(pid > 0){
        wait(NULL);
        pid = fork(); // fork 4
            
        if(pid == 0){
            cout << "Fork 4: I'm the child " << getpid() << ", my parent is " << getppid() << "." << endl;
        }else if(pid > 0){
            wait(NULL);
            pid = fork(); // fork 6
                
            if(pid == 0){
                cout << "Fork 6: I'm the child " << getpid() << ", my parent is " << getppid() << "." << endl;   
            }else if(pid > 0){
                wait(NULL);
            }
        }

        pid = fork(); // fork 5
        if(pid == 0){
            cout << "Fork 5: I'm the child " << getpid() << ", my parent is " << getppid() << "." << endl;
        }else if(pid > 0){
            wait(NULL);
        }
        
    }

    
}