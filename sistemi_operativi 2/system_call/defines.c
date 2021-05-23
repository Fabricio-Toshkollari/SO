/// @file defines.c
/// @brief Contiene l'implementazione delle funzioni
///         specifiche del progetto.

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <time.h>
#include <string.h>
#include <sys/wait.h>

#include "defines.h"

int existFile(char *fileName){
    if(access(fileName, F_OK) == -1){
        return 0; 
    }
    return 1;
}


//crea un file con l'intestazione
void createFile(char *fileName, char *arr){
    int file;
    file = open(fileName, O_CREAT | O_EXCL | O_RDWR | S_IRWXU);   
    write(file, arr,strlen(arr)+1);
    close(file);  
}

//tronca un file
void truncFile(char * name){
    int file;
    file = open(name, O_TRUNC| O_RDWR , S_IRWXU);
    close(file);
}

//sistema il file per essere scritto
void processIdcorrect(char * p,pid_t pid){
    char tmp[100];
    sprintf(tmp, "%d",pid);
    strcat(p,tmp);
    
}

//scrive su un file
void writeOnFile(char * name, char *p){
    int file;
   
    file = open(name, O_WRONLY);
    lseek(file, -1, SEEK_END);
    write(file,p,strlen(p)+1);
    close(file); 
}

//legge un file
void readFile(char * name, char * buff){
    int file;
    file = open(name, O_RDONLY);
    read(file,buff,10000);
    close(file);
}

//sistema la struct per poterla scrivere dopo
void structCorrect(instructionSet *p){
    strcat(p->id,";");
    strcat(p->message,";");
    strcat(p->idSender,";");
    strcat(p->idReciver,"\n");
}

//scrivere la struct  su un file
void structWriteOnFile(char * name,instructionSet *p){
    writeOnFile(name,p->id);
    writeOnFile(name,p->message);
    writeOnFile(name,p->idSender);
    writeOnFile(name,p->idReciver);

}
//scrivere la struct  su un file
void structWriteOnFile2(char * name,msg *p){
    writeOnFile(name,p->riga4);
    writeOnFile(name,p->riga3);
    writeOnFile(name,p->riga2);
    writeOnFile(name,p->riga1);

}
//sistema la struct per poterla scrivere dopo
void structCorrect2(msg *p){
    strcat(p->riga4,"\n");
    strcat(p->riga3,"\n");
    strcat(p->riga2,"\n");
    strcat(p->riga1,"\n");
}


//salva in una struct la riga di un file

void reverseBuff(char * buff, msg *p){

    int j=0;
    int flag = 0;
    int i=0;
    int count= 0;

    while (buff[i] != '\0'){ 
           
        if(flag == 1 && buff[i] != '\n'){
            if(count == 0){
                p->riga1[j] = buff[i];
                j++;
            }
            if(count == 1){    
                p->riga2[j] = buff[i];
                j++;
            }
            if(count == 2){
                p->riga3[j] = buff[i];
                j++;
            }
            if(count == 3){    
                p->riga4[j] = buff[i];
                j++;
            }
        }

        if(flag == 1 && buff[i] == '\n'){
            count++;
            j=0;  
        }

        if(buff[i] == '\n' && flag == 0){
                flag = 1;
         }

        i++;

        }
}


    //salva le varie cele di un file in una struct
    void saveInStruct(char * buff, instructionSet *p,int riga){

        int tmp=1;
        int j=0;
        int flag = 0;
        int i=0;
        int count= 0;

        while (buff[i] != '\0'){ 
           
            if((flag == 1 && buff[i] != ';') && riga == tmp){
                if(count == 0){
                    p->id[j] = buff[i];
                    //printf("%c",p->id[j]);
                    j++;
                }
                if(count == 1){    
                    
                    p->message[j] = buff[i];
                    //printf("%c",p->message[j]);
                    j++;
                }
                if(count == 2){
                   
                    p->idSender[j] = buff[i];
                    //printf("%c",p->idSender[j]);
                    j++;
                }
                if(count == 3){    
                  
                    p->idReciver[j] = buff[i];
                    //printf("%c",p->idReciver[j]);
                    j++;
                    
                }
            }

            if(flag == 1 && buff[i] == ';'){
                count++;
                j=0;  
            }
            if(buff[i] == '\n' && flag == 1){
                tmp++;
                count=0;
            }
            //salta l'intestazione
            if(buff[i] == '\n' && flag == 0){
                flag = 1;
            }       
            i++;
        }
    }
    



    
    
    




