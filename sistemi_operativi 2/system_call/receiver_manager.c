/// @file receiver_manager.c
/// @brief Contiene l'implementazione del receiver_manager.

#include "err_exit.h"
#include "defines.h"
#include "shared_memory.h"
#include "semaphore.h"
#include "fifo.h"
#include "pipe.h"

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <time.h>
#include <string.h>
#include <sys/wait.h>


void R1();
void R2();
void R3();



char intestazioneF8[]= "Sender,Pid\n";
char intestazione123[]= "Id,Message,Id Sender,Id Receiver,Time arrival,Time dept\n";
char processo1[100] = "R1,";
char processo2[100] = "\nR2,";
char processo3[100] = "\nR3,";


int main(int argc, char * argv[]) {

    R1();
    R2();
    R3();


    if(existFile("OutputFiles/F9.csv") == 0){
        createFile("OutputFiles/F9.csv",intestazioneF8);

    }else{
        truncFile("OutputFiles/F9.csv");
        writeOnFile("OutputFiles/F9.csv",intestazioneF8);

    }


    int prc = 1;
    pid_t pid ;
    int status = 0;
    while ( (pid = wait(&status)) != -1){
        if(prc == 1){
            processIdcorrect(processo1,pid);
            writeOnFile("OutputFiles/F9.csv",processo1);     
        }
        if( prc == 2){
            processIdcorrect(processo2,pid);
            writeOnFile("OutputFiles/F9.csv",processo2);
        }
        if(prc == 3){
            processIdcorrect(processo3,pid);
            writeOnFile("OutputFiles/F9.csv",processo3);
        }
        prc++;
        printf("Child %d exited, status=%d\n", pid, WEXITSTATUS(status));
    }

    
    return 0;
}



void R1(){

    pid_t pid = fork();
    if(pid == -1)
        printf("S1 creation error");
    if(pid == 0){

        if(existFile("OutputFiles/F6.cvs") == 0){
            createFile("OutputFiles/F6.csv",intestazione123);
        }else{
            truncFile("OutputFiles/F6.csv");
            writeOnFile("OutputFiles/F.csv",intestazione123);
        }
        
        printf("PID: %d , PPID: %d. Exit code: %d\n",
            getpid(), getppid(), 1);


        sleep(1);
        exit(1);
    }

}

void R2(){
    pid_t pid = fork();
    if(pid == -1)
        printf("S1 creation error");
    if(pid == 0){
    

        if(existFile("OutputFiles/F5.cvs") == 0){
            createFile("OutputFiles/F5.csv",intestazione123);
        }else{
            truncFile("OutputFiles/F5.csv");
            writeOnFile("OutputFiles/F5.csv",intestazione123);
        }
        
        printf("PID: %d , PPID: %d. Exit code: %d\n",
            getpid(), getppid(), 1);


        sleep(2);
        exit(1);
    }

}

void R3(){

    pid_t pid = fork();
    if(pid == -1)
        printf("S1 creation error");
    if(pid == 0){

        if(existFile("OutputFiles/F4.cvs") == 0){
            createFile("OutputFiles/F4.csv",intestazione123);
        }else{
            truncFile("OutputFiles/F4.csv");
            writeOnFile("OutputFiles/F4.csv",intestazione123);
        }
        
        printf("PID: %d , PPID: %d. Exit code: %d\n",
            getpid(), getppid(), 1);


        sleep(3);
        exit(1);
    }

}
