
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/ipc.h>
#include <sys/msg.h>

//Struktura a message queue-hoz
struct mesg_buffer {
    long mesg_type;
    double a;
    double b;
    double c;
    double root1;
    double root2;
} message;

void masodfokumegoldo(double input[]);
void kuldes(double a,double b, double c, double root1, double root2);

int main(){

   double input[3]; // a, b, c
   double output[2];// x, y
   int egyenletek;

   FILE *fp = fopen("bemenet.txt","r"); //File pointer a bemeneti file-hoz
   if (fp < 0){
        perror("Hiba van a file-al");//Hiba kezeles
        exit(-1);
   }
   fscanf(fp,"%d",&egyenletek);//Beolvassuk az egyenletek szamat
   printf("A fileban talalhato egyenletek szama: %d \n",egyenletek);
   for(int i = 0; i < egyenletek; i++){
        for(int k = 0; k < 3; k++){
            fscanf(fp,"%lf",&input[k]);//Beolvassuk az adatokat
        }
        printf("%d. egyenlet: a = %.2lf, b=%.2lf, c=%.2lf\n",i + 1,input[0],input[1],input[2]);
        masodfokumegoldo(input);//Masodfoku egyenlet megoldo fuggveny
   }

   fclose(fp);

   return 0;
}

void masodfokumegoldo(double input[]){

    double a, b, c, discriminant, root1, root2, realPart, imagPart;

    a = input[0];
    b = input[1];
    c = input[2];

    discriminant = b * b - 4 * a * c;

    if (discriminant > 0) {
        root1 = (-b + sqrt(discriminant)) / (2 * a);
        root2 = (-b - sqrt(discriminant)) / (2 * a);
        kuldes(a,b,c,root1,root2);
    }

    else if (discriminant == 0) {
        root1 = root2 = -b / (2 * a);
        kuldes(a,b,c,root1,root2);
    }
    else{
        printf("Nincs megoldas!\n");
    }
}
void kuldes(double a,double b, double c, double root1, double root2){
    // message queue
	key_t key;//kulcs az uzenet sorhoz
	int msgid;
	key = ftok("progfile", 65);// ftok generál egy saját kulcsot

	msgid = msgget(key, 0666 | IPC_CREAT);// msgid csinál egy message queuet

	message.mesg_type = 1;

	message.a = a;
	message.b = b;
	message.c = c;
	message.root1 = root1;
	message.root2 = root2;

    msgsnd(msgid, &message, sizeof(message), 0);//msgnd elkuldi az uzenetet


    printf("Sikeres kuldes!\n");
}


