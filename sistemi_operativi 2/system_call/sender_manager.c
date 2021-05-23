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


void S1();
void S2();
void S3();

char intestazioneF8[]= "Sender,Pid\n";
char intestazione123[]= "Id,Message,Id Sender,Id Receiver,Time arrival,Time dept\n";
char processo1[10] = "S1,";
char processo2[10] = "\nS2,";
char processo3[10] = "\nS3,";
char readBUffer[1000];


int main(int argc, char * argv[]) {

    S1();
    S2();
    S3();


    if(existFile("OutputFiles/F8.csv") == 0){
        createFile("OutputFiles/F8.csv",intestazioneF8);

    }else{
        truncFile("OutputFiles/F8.csv");
        writeOnFile("OutputFiles/F8.csv",intestazioneF8);

    }
    
    int prc = 1;
    pid_t pid ;
    int status = 0;
    while ( (pid = wait(&status)) != -1){
        if(prc == 1){
            processIdcorrect(processo1,pid);
            writeOnFile("OutputFiles/F8.csv",processo1);     
        }
        if( prc == 2){
            processIdcorrect(processo2,pid);
            writeOnFile("OutputFiles/F8.csv",processo2);
        }
        if(prc == 3){
            processIdcorrect(processo3,pid);
            writeOnFile("OutputFiles/F8.csv",processo3);
        }
        prc++;
        printf("Child %d exited, status=%d\n", pid, WEXITSTATUS(status));
    }
    
    return 0;

}


void S1(){

    pid_t pid = fork();
    if(pid == -1)
        ErrExit("S1 Error");
    if(pid == 0){
        instructionSet f1 ,*p1 = &f1;
        instructionSet f2 ,*p2 = &f2;
        instructionSet f3 ,*p3 = &f3;


        //legge un file e salva il contenuto in un buffer
        readFile("InputFiles/F0.csv",readBUffer);

        //organizza le righe in un astruct
        saveInStruct(readBUffer,p1,1);
        saveInStruct(readBUffer,p2,2);
        saveInStruct(readBUffer,p3,3);


    if(existFile("OutputFiles/F1.csv") == 0){
        createFile("OutputFiles/F1.csv",intestazione123);

    }else{
        truncFile("OutputFiles/F1.csv");
        writeOnFile("OutputFiles/F1.csv",intestazione123);

    }
        //sistema la stringa da scrivere nel file
        structCorrect(p1);
        structCorrect(p2);
        structCorrect(p3);

        //scrivo la struct nel file
        structWriteOnFile("OutputFiles/F1.csv",p1);
        structWriteOnFile("OutputFiles/F1.csv",p2);
        structWriteOnFile("OutputFiles/F1.csv",p3);

        
        printf("PID: %d , PPID: %d. Exit code: %d\n",
            getpid(), getppid(), 1);

        exit(1);
    }

}

void S2(){

    pid_t pid = fork();
    if(pid == -1)
         ErrExit("S2 Error");
    if(pid == 0){
        if(existFile("OutputFiles/F2.csv") == 0){
            createFile("OutputFiles/F2.csv",intestazione123);

        }else{
            truncFile("OutputFiles/F2.csv");
            writeOnFile("OutputFiles/F2.csv",intestazione123);

        }

        printf("PID: %d , PPID: %d. Exit code: %d\n",
                getpid(), getppid(), 2);
        sleep(2);
        exit(2);

    }

}

void S3(){

    pid_t pid = fork();
    if(pid == -1)
        ErrExit("S2 Error");
    if(pid == 0){
        if(existFile("OutputFiles/F3.csv") == 0){
            createFile("OutputFiles/F3.csv",intestazione123);

        }else{
            truncFile("OutputFiles/F3.csv");
            writeOnFile("OutputFiles/F3.csv",intestazione123);

    }
        printf("PID: %d , PPID: %d. Exit code: %d\n",
                getpid(), getppid(), 3);
        
        sleep(3);
        exit(3);

    }

}




