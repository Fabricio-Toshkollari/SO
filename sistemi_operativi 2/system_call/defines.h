/// @file defines.h
/// @brief Contiene la definizioni di variabili
///         e funzioni specifiche del progetto.

#ifndef DEF_H
#define DEF_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <time.h>
#include <string.h>
#include <sys/wait.h>

#pragma once

struct instructionSet{
    char id[10];
    char message[10];
    char idSender[4];
    char idReciver[4];
    time_t timeArr;
    time_t timeDep;
};
typedef struct instructionSet instructionSet;

struct msg{
    char riga1[100];
    char riga2[100];
    char riga3[100];
    char riga4[100];
    
};
typedef struct msg msg;


void writeOnFile(char * name, char * buff);
void writeOnFile2(char * name, char * buff);
void reverseBuff(char *buff, msg *p);
void writeReverse(char * name, char * buff); 
void readFile(char * name, char * buff);
int existFile(char * name);
void truncFile(char * name);
void createFile(char * name, char * arr);
void processIdcorrect(char * p, pid_t pid);
void structCorrect(instructionSet *s);
void structCorrect2(msg *s);
void structWriteOnFile(char* name,instructionSet *s);
void structWriteOnFile2(char* name,msg *s);
void saveInStruct(char * buff, instructionSet *p,int riga);

#endif