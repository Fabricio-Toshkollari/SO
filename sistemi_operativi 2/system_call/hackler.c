/// @file client.c
/// @brief Contiene l'implementazione del client.

#include "defines.h"

char intestazione[]= "Id,Delay,Target,Action\n";
char buffer[10000 + 1];

int main(int argc, char * argv[]) {


    // struttura dati che mi servere per manipolare il file che devo leggere
    msg set,*p = &set;

    //legge il file
    readFile("InputFiles/F7.csv",buffer);
    sleep(2);
        
    if(existFile("OutputFiles/F7_out.csv") == 0){
            createFile("OutputFiles/F7_out.csv",intestazione);
    }
        
     //sistemo il file in una struct per poterla manipolare comodamente
    reverseBuff(buffer,p);
    //sistemo le varie array per poterle scrivere meglio sul file
    structCorrect2(p);

    //scrivo sul file inverso
    structWriteOnFile2("OutputFiles/F7_out.csv",p);
    return 0;
}

