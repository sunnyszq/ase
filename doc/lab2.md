lab2

mkdir lab2

cd lab2

拷贝lab1中的hello.c文件到lab2的menu.c中

cp ../lab1/hello.c menu.c



vim下设置tab四个空格：e ~/.vimrc





```C
#include<stdio.h>
#include<stdlib.h>
int main()
{
    char cmd[128];
    while(1)
    {
        scanf("%s", cmd);
        if(strcmp(cmd,"help") == 0)
        {
            printf("This is help cmd!\n");
        }
        else if(strcmp(cmd,"quit") == 0)
        {
            exit(0);
        }
        else
        {
            printf("Wrong cmd!\n");
        }
    }
  return 0;
}

```

```C
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
```





代码风格的原则：简明 易读 无二义性

-缩进：4个空格

-行宽：<100个字符

-复杂表达式中用()清晰表达逻辑优先级

-所有{}都独占一行且成对对齐

-不要把多条语句和多个变量定义放在同一行



命名

合适的命名会大大增加代码的可读性

类型，类，函数名，变量名等的命令一定要与程序里的含义保持一致，以便阅读理解

-类型的成员变量通常用m_或 _来做前缀

一般变量使用lowerCamel风格，第一个单词首字母小写，之后的首字母大写，第一个单词一般用来表示变量类型，比如int型变量iCounter

类型 类 函数名一般使用Pascal风格，即所有首字母大写

类型 类 变量一般用名词或组合名词，如Member

函数名一般使用动词或动宾短语，如get/set,RenderPage



注释和版权信息

注释使用英文，不使用中文或者特殊字符，保持源代码时ASCII字符格式文件

不要解释程序是如何工作的，解释程序是做什么的，为什么这么做，以及特别需要注意的地方

