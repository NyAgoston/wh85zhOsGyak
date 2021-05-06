#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>
// struktura
struct mesg_buffer {
    long mesg_type;
    double a;
    double b;
    double c;
    double root1;
    double root2;
} message;

void fileKiiras(double a, double b, double c, double root1, double root2);

int main()
{
    key_t key;//kulcs az uzenet sorhoz
    int msgid;
    key = ftok("progfile", 65);// ftok generál egy saját kulcsot

    msgid = msgget(key, 0666 | IPC_CREAT);// msgid csinál egy message queuet

    if(msgid == -1){
        perror("msgget");
        exit(1);
    }

    for(;;){

        if(msgrcv(msgid, &message, sizeof(message), 1, 0) == -1){//msgrcv fogadja az uzenetet
            perror("msgrcv");
            exit(1);
        }

        fileKiiras(message.a,message.b,message.c,message.root1,message.root2);// kiiras fileba

    }
    msgctl(msgid, IPC_RMID, NULL);// a message queue törlése



    return 0;
}

void fileKiiras(double a, double b, double c, double root1, double root2){
    FILE *file_to_write = fopen("eredmeny.txt","a");

    if (file_to_write < 0){
        perror("Hiba a file-al");
        exit(-1);
    }

    printf("Sikeres file kiiras!\n");

    fprintf(file_to_write,"Egyenlet: a = %.2lf, b=%.2lf, c=%.2lf = x1=%lf, x2=%lf\n",message.a,message.b,message.c,message.root1,message.root2);

    fclose(file_to_write);
}
