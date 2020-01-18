//
//assignment2 part1
//Zhiqi Bei
//zbei@uwo.ca

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <pthread.h>
#include <stdlib.h>

//initialize x,y,z
int x = 10;
int y = 20;
int z = 0;

void *thread_prints_msg(void* num)
{
    z = x+y;
    return 0;
}
int main(int argc, const char * argv[]) {
    pid_t pid;
    pthread_t thread_1;
    int pipes[2];
    pipe(pipes);
    pid = fork();
    
    //parent process
    if(pid >0){
        //waiting for child
        wait(NULL);
        printf("by fork: z = %d\n",z);
        //parent and child didn't share data by fork, so z must be 0
        //but in thread the data is shareing, so z must be 30
        pthread_create(&thread_1, NULL, thread_prints_msg,NULL);
        pthread_join(thread_1, NULL);
        printf("by thread :z = %d\n",z);
    }
    else{
        z = x + y;
        return 0;        
    }
    
}
