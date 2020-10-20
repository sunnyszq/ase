#include <stdio.h>
#include <stdlib.h>


int a = 0;
int b = 0;
void hello();
void help();
void display();
void sum();
void change();
void compare();
void input();
void quit();
void exchange();

int main ()
{

    char cmd[10];
    while (1)
    {
        printf("please input a cmd:\n");
        scanf("%s",cmd);
        if(!strcmp(cmd,"hello"))
        {
            hello();
        }
        if(!strcmp(cmd,"help"))
        {
            help();
        }
            if(!strcmp(cmd,"display"))
        {
            display();
        }
        if(!strcmp(cmd,"compare"))
        {
            compare();
        }
        if(!strcmp(cmd,"sum"))
        {
            sum();
        }
        if(!strcmp(cmd,"input"))
        {
            input();
        }
        if(!strcmp(cmd,"quit"))
        {
            quit();
        }
        if(!strcmp(cmd,"exchange"))
        {
            exchange();
        }
    }
}

void hello()
{
    printf("welcome to the menu!\n");
}

void help()
{
    printf("***************************\n");
    printf("*hello               hello*\n");
    printf("*help                 help*\n");
    printf("*display      show a and b*\n");
    printf("*sum        output the sum*\n");
    printf("*exchange exchange a and b*\n");
    printf("*compare output the maxnum*\n");
    printf("*quit        quit the menu*\n");
    printf("*input       input a and b*\n");
    printf("***************************\n");
}

void display()
{
    printf("a=%d   b=%d\n",a,b);
}

void compare()
{
    if (a>b)
        printf("the max num is a=%d\n",a);
    else
        printf("the max num is b=%d\n",b);
}

void sum()
{
    printf("the sum is %d\n",a+b);
}

void quit()
{
    exit(0);
}

void input()
{
    printf("please input a and b:\n");
    scanf("%d%d",&a,&b);
}

void exchange()
{
    int temp;
    temp = a;
    a = b;
    b =temp;
    printf("the num has been exchanged!\na=%d  b=%d\n",a,b);
}
