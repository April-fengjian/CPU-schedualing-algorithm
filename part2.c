//
//assignment2_part2
//Zhiqi Bei (#250916374)
//zbei@uwo.ca
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
struct node{
    char processNum[100];
    int time;               //the total time need to be executed
    int begin;              //begin time of the process
    int finish;             //finish time of the process
};
void FCFS (char queue[1000][1000],int index,FILE *fp){
    int queueNum = atoi(queue[1]);
    
    fprintf(fp,"\nReady Queue %d Applying FCFS Scheduling:\n",queueNum);
    fprintf(fp,"Order of selection by CPU: \n");
    printf("\nReady Queue %d Applying FCFS Scheduling:\n",queueNum);
    printf("Order of selection by CPU: \n");
    
    for(int i=4;i<=index;i=i+2){
        fprintf(fp,"%s ",queue[i]);
        printf("%s ",queue[i]);
    }
    fprintf(fp,"\n");
    printf("\n");
    
    //calculate the waiting time for each process
    fprintf(fp,"\nIndividual waiting times for each process: \n");
    printf("\nIndividual waiting times for each process: \n");
    
    int waiting = 0;
    int num = 0;
    int total = 0;
    for(int i=4;i<index;i=i+2){
        //the waiting time of p1 is 0
        if(i==4){
            waiting = 0;
        }
        else{
            waiting = waiting + atoi(queue[i-1]);
        }
        num = num+1;
        total = total + waiting;
        fprintf(fp,"%s = %d\n",queue[i],waiting);
        printf("%s = %d\n",queue[i],waiting);
    }
    //calculate the average waiting time
    double average = (float)total/num;
    fprintf(fp,"\nAverage waiting time = %.1f\n",average);
    printf("\nAverage waiting time = %.1f\n",average);
}
void SJF (char queue[1000][1000], int index,FILE *fp){
    //create a new queue that store the same data as queue
    char newqueue[1000][1000];
    for (int i=0; i<index; i++) {
        strcpy(newqueue[i], queue[i]);
    }
    
    //sort the new queue from smallest to largest
    for(int i=4;i<index;i=i+2){
        for(int j=4;j<index;j=j+2){
            if(atoi(newqueue[i+1])<atoi(newqueue[j+1])){
                char time[1000];
                char pnum[1000];
                strcpy(pnum, newqueue[i]);
                strcpy(time, newqueue[i+1]);
                strcpy(newqueue[i+1], newqueue[j+1]);
                strcpy(newqueue[i], newqueue[j]);
                strcpy(newqueue[j+1], time);
                strcpy(newqueue[j], pnum);
            }
        }
    }
    int queueNum = atoi(queue[1]);
    fprintf(fp,"\nReady Queue %d Applying SJF Scheduling:\n",queueNum);
    fprintf(fp,"Order of selection by CPU: \n");
    printf("\nReady Queue %d Applying SJF Scheduling:\n",queueNum);
    printf("Order of selection by CPU: \n");
    
    for(int i=4;i<=index;i=i+2){
        fprintf(fp,"%s ",newqueue[i]);
        printf("%s ",newqueue[i]);
    }
    
    fprintf(fp,"\n");
    fprintf(fp,"\nIndividual waiting times for each process: \n");
    printf("\n");
    printf("\nIndividual waiting times for each process: \n");
    //calculate the waiting time for each process
    int waiting = 0;
    int num = 0;
    int total = 0;
    for(int i=4;i<index;i=i+2){
        //the waiting time of p1 is 0
        if(i==4){
            waiting = 0;
        }
        else{
            waiting = waiting + atoi(newqueue[i-1]);
        }
        num = num+1;
        total = total + waiting;
        fprintf(fp,"%s = %d\n",newqueue[i],waiting);
        printf("%s = %d\n",newqueue[i],waiting);
    }
    //calculate the average waiting time
    double average = (float)total/num;
    fprintf(fp,"\nAverage waiting time = %.1f\n",average);
    printf("\nAverage waiting time = %.1f\n",average);
    printf("\n");
    fprintf(fp, "\n");
}

void RR (char queue[1000][1000], int index,FILE *fp){
    int queueNum = atoi(queue[1]);
    int tq = atoi(queue[3]);
    int position = 0;
    int begin_time = 0;
    int finish_time = 0;
    
    //create a node that store the infomation of the process
    struct node process[1000];
    
    //make every process in the queue to be a node and store the node in the new array(process)
    for(int i=4;i<index;i=i+2){
        struct node data;
        strcpy(data.processNum, queue[i]);
        data.time = atoi(queue[i+1]);
        data.begin = begin_time;
        data.finish = 0;
        
        //calculate the finish time after execute of the process in the first round
        if(data.time < tq){
            data.finish = finish_time + data.time;
        }else{
            data.finish = finish_time + tq;
        }
        process[position] = data;
        
        //for next loop
        position = position + 1;
        if(data.time < tq){
            begin_time = begin_time + data.time;
        }else{
            begin_time = begin_time + tq;
        }
    }

    //the turnarround is use to store the node(process) which is complete, and is can be calculate the turnarround time;
    position = position-1;
    struct node turnarround[1000];
    //the position in the turnarround array
    int t_position = 0;
    
    //run each process in the process array, if the process is finish(time <= tq), put it into the turnarround array with the new finish time
    //else calculate the rest of time and put it into the tail of the process array.
    for (int i=0; i<=position; i++) {
        struct node newNode;
        if(process[i].time > tq){
            int leftTime = process[i].time - tq;
            strcpy(newNode.processNum,process[i].processNum);
            newNode.time = leftTime;
            finish_time = finish_time+tq;
            newNode.finish = finish_time;
            newNode.begin = process[i].begin;
            position++;
            process[position] = newNode;
        }
        if (process[i].time == tq) {
            strcpy(newNode.processNum,process[i].processNum);
            newNode.time = 0;
            finish_time = finish_time+tq;
            newNode.finish = finish_time;
            newNode.begin = process[i].begin;
            turnarround[t_position] = newNode;
            t_position++;
        }
        if(process[i].time < tq){
            strcpy(newNode.processNum,process[i].processNum);
            newNode.time = 0;
            finish_time = finish_time + process[i].time;
            newNode.finish = finish_time;
            newNode.begin = process[i].begin;

            turnarround[t_position] = newNode;
            t_position++;
        }
    }
    
    fprintf(fp,"Ready Queue %d Applying RR Scheduling:\n", queueNum);
    fprintf(fp,"\nOrder of selection by CPU: \n");
    printf("Ready Queue %d Applying RR Scheduling:\n", queueNum);
    printf("\nOrder of selection by CPU: \n");
    
    //the order in the process array is the order of selection by CPU
    for(int i=0;i<=position;i++){
        fprintf(fp,"%s ",process[i].processNum);
        printf("%s ",process[i].processNum);
    }
    
    fprintf(fp,"\n");
    fprintf(fp,"\nTurnaround times for each process: \n");
    printf("\n");
    printf("\nTurnaround times for each process: \n");
    
    //the node in the turnarround array is  used to calculate the turnarround time
    //calculate the turnarround time by (finish time - begin time)
    for(int i=0;i<=t_position-1;i++){
        fprintf(fp,"%s = %d\n",turnarround[i].processNum,turnarround[i].finish-turnarround[i].begin);
        printf("%s = %d\n",turnarround[i].processNum,turnarround[i].finish-turnarround[i].begin);
    }
    fprintf(fp,"\n");
    printf("\n");    
}


int main(int argc, const char * argv[]) {
    FILE *inputfile = NULL;
    FILE *outputfile = NULL;
    inputfile = fopen("cpu_scheduling_input_file.txt", "r");
    outputfile = fopen("cpu_scheduling_output_file.txt", "w+");
    char line[1024];
    char * c;
    char queue[1000][1000];
    
    if(inputfile == NULL){
        printf("There is no such file\n");
        return 0;
    }
    //read the file by line
    fgets(line, 1024, inputfile);
    while(!feof(inputfile)){
        //split the line by " "
        c = strtok(line," ");
        int index = 0;
        while(c != NULL){
            strcpy(queue[index], c);
            index = index + 1;
            c = strtok(NULL," ");
        }
        FCFS(queue, index,outputfile);
        SJF(queue,index,outputfile);
        RR(queue,index,outputfile);
        fgets(line, 1024, inputfile);
    }

    fclose(inputfile);
    fclose(outputfile);
    return 0;
}
