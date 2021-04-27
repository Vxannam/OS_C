
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <setjmp.h>
#include <stdlib.h>
#include <ctype.h>
#include <locale.h>
#include <wait.h>

sigjmp_buf o; /* область памяти для запоминания состояния процесса */
int counter = 0;   /* счетчик прерывания */
char data[10];
char day[4];
int year=0;


/* Подпрограмма обработки прерывания */
void interrupt()
{
    counter ++;
    if (counter % 3 == 0)	/* не больше трех прерываний */
    {

        printf("%c\n",'\n');


       if (year==0) printf("%s\n","Не введена дата");
       else{
           if (year%4==0 && year!=0) printf("%i\n",366);
           else printf("%i\n",365);
       }



    }
    printf("\n");
    siglongjmp (o, 1);    /* возвращение на последний setjmp*/
}

void check(){
    int s=0;
    int current_year;
    int current_day;
    current_year= (data[0]-'0')*1000+(data[1]-'0')*100+(data[2]-'0')*10+(data[3]-'0');
    current_day=(data[8]-'0')*10+(data[9]-'0');

    for (int i=0;i<10;i++){
        if (isdigit(data[i])){
            s++;
        }
    }
    if (s!=8){

        if (current_year!=2021){

            if (data[5]!='0' || data[6]!='3')  {

                if (data[4]!='-' || data[7]!='-'){

                    if (current_day>31){


                    }
                }

            }

        }


    }
    s=0;
    printf("%s\n","Некорректный ввод, введите еще раз");
    scanf("%s",data);

}


int main() {
    signal(SIGINT, interrupt);

    char n[10000];
    int c[2];
    pipe(c);

    if (fork() == 0) {
        close(1);
        close(c[0]);
        dup2(c[1], 1);
        close(c[1]);
        execl("/usr/bin/ncal", "ncal", 0);
        _exit(-1); //на всякий пожарный, если execl не сработал
    } else {
        wait(NULL);
        close(c[1]);
        memset(n, 0, 10000);
        read(c[0], n, 10000);
        printf("%s\n", n);
    }

    sigsetjmp(o,1);
    printf("Введите date XXXX-XX-XX\n");

    scanf("%s",data);
    int s=0;
    int current_year;
    int current_day;
    while(1){


        current_year= (data[0]-'0')*1000+(data[1]-'0')*100+(data[2]-'0')*10+(data[3]-'0');
        current_day=(data[8]-'0')*10+(data[9]-'0');

        for (int i=0;i<10;i++){
            if (isdigit(data[i])){
                s++;
            }
        }
        if (s==8){

            if (current_year==2021){

                if (data[5]=='0' || data[6]=='3')  {

                    if (data[4]=='-' || data[7]=='-'){

                        if (current_day<31){

                            break;
                        }
                    }

                }
            }


        }
        s=0;
        printf("%s\n","Некорректный ввод, введите еще раз");
        scanf("%s",data);

    }

    year=(data[0]-'0')*1000+(data[1]-'0')*100+(data[2]-'0')*10+(data[3]-'0');
    day[0]=data[8];
    day[1]=data[9];
    if (day[1]==0){
        day[1]=' ';
    }
    //day[3]=0;
    char dot[3];
    char* a = strstr(n+23, day);
    do{
        if (*a != '\n') {
            a--;
        } else{
            dot[0]=*(a+1);
            dot[1]=*(a+2);
            dot[2]=0;
            break;
        }



    }
    while (1);
    printf("%s\n", dot);
    sigsetjmp(o,1);
    while (getchar()!='q'){

    }
    return 0;

}









