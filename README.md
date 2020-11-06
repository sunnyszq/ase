### Menu项目代码中的软件工程

### 一、环境配置

　　本项目以VS Code + GCC工具集为主要环境编译，项目代码参考https://github.com/mengning/menu

#### 1.1 安装VS Code

　　下载安装好Vs code后安装C/C++插件，中文语言包等相关插件

![img](https://img2020.cnblogs.com/blog/2164343/202011/2164343-20201104144837362-1424556425.png)

 ![img](https://img2020.cnblogs.com/blog/2164343/202011/2164343-20201104145047928-10840910.png)

####  1.2 安装 C/C++编译器和调试器

　　VS code中没有C/C++编译器，需要自己进行安装。在不同的系统上，C/C++编译器是不同的，由于我的系统是windows，所以需要安装Mingw-w64。

　　安装完成后需要将安装目录中的mingw64\bin添加到系统环境变量Path中，完成后在cmd命令行窗口输入gcc -v测试是否安装成功。

![img](https://img2020.cnblogs.com/blog/2164343/202011/2164343-20201104150331834-655540968.png)

 ![img](https://img2020.cnblogs.com/blog/2164343/202011/2164343-20201104150421159-1626065691.png)

####  1.3 配置 Visual Studio Code 构建任务

 　新建项目文件夹，打开终端输入 code. 命令，就可以在VScode中打开该文件夹，同时会生成三个json配置文件：

1. tasks.json
2. launch.json
3. c_cpp_properties.json

需要修改task.json中的command，把之前安装的mingw64的bin\gcc.exe的路径加入进来，如下：

```
 "command": "D:\\MinGW-W64\\mingw64\\bin\\gcc.exe",
```

　　到现在，项目运行环境已经配置结束。可以写一个测试程序测试vs code是否配置成功。

### 二、结合menu项目中的分析常见的软件工程思想

#### 2.1 模块化设计

 **模块化的思想和关注点的分离:**

> **模块化（Modularity）**是在软件系统设计时保持系统内各部分相对独立，以便每一个部分可以被独立地进行设计和开发。这个做法背后的***基本原理是关注点的分离\*** (SoC, Separation of Concerns)，是由软件工程领域的奠基性人物Edsger Wybe **Dijkstra**（Dijkstra最短路径算法的作者）在1974年提出。
>
> **关注点的分离**在软件工程领域是最重要的原则，我们习惯上称为模块化，翻译成我们中文的表述其实就是“分而治之”的方法。
>
> 关注点的分离的思想背后的根源是由于人脑处理复杂问题时容易出错，把复杂问题分解成一个个简单问题，从而减少出错的情形。

**基本模块的写法：**

1. 开-闭 原则：对扩展是开放的，对修改是封闭的
2. 模块复用和系统复用
3. 业务逻辑层和数据存储层
4. 将系统模块放在不同的源文件中：将数据结构和操作放在独立的文件中，通过接口进行传递

##### **menu中的模块化设计：**

　　在menu项目中，把对链表的定义和对链表的操作函数声明放在了linklist.h 文件中，在linklist.c文件中对链表的操作函数进行实现。这样就可以在menu.c中的头文件包含linklist模块来进行调用。

```
//menu.c 
#include <stdio.h>
#include <stdlib.h>
#include "linktable.h"
```

**这里就将系统模块放在不同的源文件中：将数据结构和操作放在独立的linklist.h/linklist.c文件中，通过接口进行传递。**

**menu.c 和linklist.h/linklist.c模块之间的调用关系：**

![img](https://img2020.cnblogs.com/blog/2164343/202011/2164343-20201104170729646-1473501222.png)

#### 2.2 可重用接口

　　尽管已经做了初步的模块化设计，但是分离出来的数据结构和它的操作还有很多菜单业务上的痕迹，我们要求这一个软件模块只做一件事，也就是功能内聚，那就要让它做好链表数据结构和对链表的操作，不应该涉及菜单业务功能上的东西；同样我们希望这一个软件模块与其他软件模块之间松散耦合，就需要定义简洁、清晰、明确的接口。

 **接口的概念：**

> 　　接口就是互相联系的双方共同遵守的一种协议规范，在我们软件系统内部一般的接口方式是通过定义一组API函数来约定软件模块之间的沟通方式。换句话说，接口具体定义了软件模块对系统的其他部分提供了怎样的服务，以及系统的其他部分如何访问所提供的服务。

 **接口的五个要素：**

> •接口的目的；Purpose
>
> •接口使用前所需要满足的条件，一般称为前置条件或假定条件； preconditions
>
> •使用接口的双方遵守的协议规范；protocols
>
> •接口使用之后的效果，一般称为后置条件；postconditions
>
> •接口所隐含的质量属性。quality attributes

 **接口的分类：**

- 共享数据或变量名
- call-in functions
- callback functions
- 同步调用接口
- 异步调用接口 -- 信号量、消息队列等方式实现

 **接口与耦合度之间的关系：**

> 　　更细致地对耦合度进一步划分的话，耦合度依次递增可以分为无耦合、数据耦合、标记耦合、控制耦合、公共耦合和内容耦合。这些耦合度划分的依据就是接口的定义方式，我们接下来重点分析一下公共耦合、数据耦合和标记耦合。
>
> •公共耦合-common coupling
>
> 　　当软件模块之间**共享数据区或变量名**的软件模块之间即是**公共耦合**，显然两个软件模块之间的接口定义不是通过显式的调用方式，而是隐式的共享了共享了数据区或变量名。
>
> •数据耦合--data coupling-only data values
>
> 　　在软件模块之间仅通过显式的**调用传递基本数据类型即为数据耦合。**
>
> •标记耦合--stamp coupling
>
> 　　在软件模块之间仅通过显式的**调用传递复杂的数据结构(结构化数据）**即为标记耦合，这时数据的结构成为调用双方软件模块隐含的规格约定，因此**耦合度要比数据耦合高**。但相比公共耦合没有经过显式的调用传递数据的方式耦合度要低。

#####  **menu项目中的可重用接口：**

1.**通用Linktable模块的接口参见linktable.h，对应的实现代码linktable.c**

2.给Linktable增加Callback方式的接口

```
//linktable.h
/*
*给Linktable增加Callback方式的接口，需要两个函数接口，一个是call-in方式函数，如*SearchLinkTableNode函数，其中有一个函数作为参数，这个作为参数的函数就是callback函数，
*如代码中Conditon函数。
 */
tLinkTableNode * SearchLinkTableNode(tLinkTable *pLinkTable, int Conditon(tLinkTableNode * pNode));

//linktable.c
/*
 * Search a LinkTableNode from LinkTable
 * int Conditon(tLinkTableNode * pNode);
 */
tLinkTableNode * SearchLinkTableNode(tLinkTable *pLinkTable, int Conditon(tLinkTableNode * pNode))
{
    if(pLinkTable == NULL || Conditon == NULL)
    {
        return NULL;
    }
    tLinkTableNode * pNode = pLinkTable->pHead;
    while(pNode != pLinkTable->pTail)
    {    
        if(Conditon(pNode) == SUCCESS)
        {
            return pNode;				    
        }
        pNode = pNode->pNext;
    }
    return NULL;
}

//前置条件是tLinkTable * head需要指定一个链表，和一个搜索条件 搜索函数SearchCondition；还有判断这个节点是否符合搜索条件
int SearchCondition(tLinkTableNode * pLinkTableNode)
{
    tDataNode * pNode = (tDataNode *)pLinkTableNode;
    if(strcmp(pNode->cmd, cmd) == 0)
    {
        return  SUCCESS;  
    }
    return FAILURE;	       
}

/* find a cmd in the linklist and return the datanode pointer */
tDataNode* FindCmd(tLinkTable * head, char * cmd)
{
    return  (tDataNode*)SearchLinkTableNode(head,SearchCondition);
}
```

　　在menu子系统的重用机会和应用场景都比较有限，因此我们没有必要花非常多的心思把接口定义的太通用，通用往往意味着接口的使用不够直接明了.在menu子系统中的接口设计我们的原则是“**够用就好——不要太具体，也不要太通用**”。

如下代码是我们在menu.h中定义的两个接口，一个是通过给出命令的名称、描述和命令的实现函数定义一个命令；另一个是启动menu引擎。

```
/* add cmd to menu */
int MenuConfig(char * cmd, char * desc, int (*handler)());

/* Menu Engine Execute */
int ExecuteMenu()
```

3.**利用callback函数参数使Linktable的查询接口更加通用**

给call-in方式的函数接口SearchLinkTableNode**增加了一个参数args**，callback函数Conditon也增加一个参数args。

```
tLinkTableNode * SearchLinkTableNode(tLinkTable *pLinkTable, int Conditon(tLinkTableNode * pNode, void * args), void * args);


int SearchConditon(tLinkTableNode * pLinkTableNode,void * arg)
{
    char * cmd = (char*)arg;
    tDataNode * pNode = (tDataNode *)pLinkTableNode;
    if(strcmp(pNode->cmd, cmd) == 0)
    {
        return  SUCCESS;  
    }
    return FAILURE;	       
}
```

在上面 2 的方式中用户程序定义了卧底SearchCondition，这个卧底函数需要向基地查询目标信息，也就是使用了全局变量cmd。与现实世界的情况类似这样会大大增加卧底暴露的风险，**为了降低风险增加了args参数**，这样在派遣卧底的同时指定了目标情报的内容，卧底在行动过程中就不需要和基地建立联系，只有在搜集到目标情报args时才向基地报道完成任务。**因此利用callback函数参数使Linktable的查询接口更加通用，有效地提高了接口的通用性。**

#### 2.3 线程安全

　　先介绍一下什么是线程、函数调用堆栈、可重入函数和线程安全。

**线程**：

> 　　线程（thread）是操作系统能够进行运算调度的最小单位。它包含在进程之中，是进程中的实际运作单位。一个线程指的是进程中一个单一顺序的控制流，一个进程中可以并发多个线程，每条线程并行执行不同的任务。一般默认一个进程中只包含一个线程。

**函数调用堆栈：**

> 　　全局变量存储在堆里面，是线程之间共享的资源；局部变量存储在函数调用的栈中，函数参数和局部变量也是线程独自拥有的。
>
> 　　借助函数调用堆栈可以将我们写的函数调用代码整理成一个顺序执行的指令流，也就是一个线程，**每一个线程都有一个独自拥有的函数调用堆栈空间**，其中函数参数和局部变量都存储在函数调用堆栈空间中，因此**函数参数和局部变量也是线程独自拥有的**。除了函数调用堆栈空间，同一个进程的多个线程是共享其他进程资源的，比如全局变量是多个线程共享的。

**可重入函数：**

> 可重入（reentrant）函数可以由多于一个任务并发使用，而不必担心数据错误。
>
> 相反，不可重入（non-reentrant）函数不能由超过一个任务所共享，除非能确保函数的互斥（或者使用信号量，或者在代码的关键部分禁用中断）。
>
> 可重入函数可以在任意时刻被中断，稍后再继续运行，不会丢失数据。可重入函数要么使用局部变量，要么在使用全局变量时保护自己的数据。
>
> **可重入函数的基本要求：**
>
> • 不为连续的调用持有静态数据；
>
> • 不返回指向静态数据的指针；
>
> • 所有数据都由函数的调用者提供；
>
> • 使用局部变量，或者通过制作全局数据的局部变量拷贝来保护全局数据；
>
> • 使用静态数据或全局变量时做周密的并行时序分析，通过临界区互斥避免临界区冲突；
>
> • 绝不调用任何不可重入函数。

**例子：**

```
int g=0;
int function()
{
    g++;
    printf("%d",g);
}

//可重入是指两个或多个线程同时进入一个函数执行，因此上面的例子是不可重入的

int function2()
{
    a++;
    printf("%d",a);
}

//上面例子中就是可重入的函数，因为所有存储在函数调用堆栈上的数据都是线程独享的，这个例子是线程安全的
```

**线程安全：**

> 　　如果你的代码所在的进程中有多个线程在同时运行，而这些线程可能会同时运行这段代码。如果每次运行结果和单线程运行的结果是一样的，而且其他的变量的值也和预期的是一样的，就是线程安全的。
>
> 　　线程安全问题都是由全局变量及静态变量引起的。若每个线程中对全局变量、静态变量只有读操作，而无写操作，一般来说，这个全局变量是线程安全的；若有多个线程同时执行读写操作，一般都需要考虑线程同步，否则就可能影响线程安全。

**可重入函数和线程安全的关系**：线程安全的代码一定都是可重入的函数；可重入的不一定都是线程安全的

##### **menu项目中的“线程安全”：linktable.c**

```
/*
 * LinkTable Type
 */
struct LinkTable
{
    tLinkTableNode *pHead;
    tLinkTableNode *pTail;
    int			SumOfNode;
    pthread_mutex_t mutex;   //信号量

};


/*
 * Delete a LinkTable
 */
// 删除链表是线程安全的
int DeleteLinkTable(tLinkTable *pLinkTable)
{
    if(pLinkTable == NULL)
    {
        return FAILURE;
    }
    while(pLinkTable->pHead != NULL)
    {
        tLinkTableNode * p = pLinkTable->pHead;
        pthread_mutex_lock(&(pLinkTable->mutex));  //P操作 加锁
        pLinkTable->pHead = pLinkTable->pHead->pNext;
        pLinkTable->SumOfNode -= 1 ;
        pthread_mutex_unlock(&(pLinkTable->mutex));   //V操作
        free(p);
    }
    pLinkTable->pHead = NULL;
    pLinkTable->pTail = NULL;
    pLinkTable->SumOfNode = 0;
    pthread_mutex_destroy(&(pLinkTable->mutex));  //信号量销毁
    free(pLinkTable);
    return SUCCESS;		
}

/*
 * Add a LinkTableNode to LinkTable
 */
//添加节点的操作是线程安全的
int AddLinkTableNode(tLinkTable *pLinkTable,tLinkTableNode * pNode)
{
    if(pLinkTable == NULL || pNode == NULL)
    {
        return FAILURE;
    }
    pNode->pNext = NULL;
    //在要修改节点信息时，加锁
    pthread_mutex_lock(&(pLinkTable->mutex));
    if(pLinkTable->pHead == NULL)
    {
        pLinkTable->pHead = pNode;
    }
    if(pLinkTable->pTail == NULL)
    {
        pLinkTable->pTail = pNode;
    }
    else
    {
        pLinkTable->pTail->pNext = pNode;
        pLinkTable->pTail = pNode;
    }
    pLinkTable->SumOfNode += 1 ;
    pthread_mutex_unlock(&(pLinkTable->mutex));
    return SUCCESS;		
}

/*
 * Delete a LinkTableNode from LinkTable
 */
//删除节点在删除时添加了锁，是一个原子性操作，可以实现临界区互斥访问，是线程安全的
int DelLinkTableNode(tLinkTable *pLinkTable,tLinkTableNode * pNode)
{
    if(pLinkTable == NULL || pNode == NULL)
    {
        return FAILURE;
    }
    pthread_mutex_lock(&(pLinkTable->mutex));
    if(pLinkTable->pHead == pNode)
    {
        pLinkTable->pHead = pLinkTable->pHead->pNext;
        pLinkTable->SumOfNode -= 1 ;
        if(pLinkTable->SumOfNode == 0)
        {
            pLinkTable->pTail = NULL;	
        }
        pthread_mutex_unlock(&(pLinkTable->mutex));
        return SUCCESS;
    }
    tLinkTableNode * pTempNode = pLinkTable->pHead;
    while(pTempNode != NULL)
    {    
        if(pTempNode->pNext == pNode)
        {
            pTempNode->pNext = pTempNode->pNext->pNext;
            pLinkTable->SumOfNode -= 1 ;
            if(pLinkTable->SumOfNode == 0)
            {
                pLinkTable->pTail = NULL;	
            }
            pthread_mutex_unlock(&(pLinkTable->mutex));
            return SUCCESS;				    
        }
        pTempNode = pTempNode->pNext;
    }
    pthread_mutex_unlock(&(pLinkTable->mutex));
    return FAILURE;		
}

/*
 * Search a LinkTableNode from LinkTable
 * int Conditon(tLinkTableNode * pNode);
 */
//只有读，没有写，没有可重入问题
tLinkTableNode * SearchLinkTableNode(tLinkTable *pLinkTable, int Conditon(tLinkTableNode * pNode, void * args), void * args)
{
    if(pLinkTable == NULL || Conditon == NULL)
    {
        return NULL;
    }
    tLinkTableNode * pNode = pLinkTable->pHead;
    while(pNode != NULL)
    {    
        if(Conditon(pNode,args) == SUCCESS)
        {
            return pNode;				    
        }
        pNode = pNode->pNext;
    }
    return NULL;
}

/*
 * get LinkTableHead
 */
//只有读，没有写，没有可重入问题
tLinkTableNode * GetLinkTableHead(tLinkTable *pLinkTable)
{
    if(pLinkTable == NULL)
    {
        return NULL;
    }    
    return pLinkTable->pHead;
}
```

#### 2.4 软件设计方法论和设计原则

　　在软件设计过程中，要遵循“不断地重构”这一设计方法论，同时遵循下面的设计原则：

> •Modularity 模块化
>
> •Interfaces 接口 
>
> •Information hiding 信息隐藏
>
> •Incremental development 增量开发
>
> •Abstraction  抽象
>
> •Generality 一般化

**Modularity 模块化**

- 模块化 ，也叫关注点的分离，把一个系统不相干的部分分开独立。
- 优点：减少犯错，同时提高软件的可维护性 ；容易理解，开发，维护定位错误，变更系统

**模块化衡量标准：耦合性和内聚性**

- **功能内聚**是理想的内聚程度（如menu中把所有数据操作的放在一起）

**Interfaces 接口** 

- 模块之间要定义接口，模块化好不好，看接口定义的好不好
- 接口的定义明确了模块之间的耦合关系

**Information hiding 信息隐藏**

- **信息隐藏是由接口定义来达成的，定义接口时没有必要暴露在外的都需要隐藏**
- 信息隐藏可以提高软件的可维护性，即包容了变化。信息隐藏和内聚度和耦合度有密切的关系。

信息隐藏的层级：

- 信息内聚information cohesive：A moudle hides a data representation 隐藏了数据的表现形式
- 功能内聚：隐藏了一个算法。如menu中的链表把链表操作数据的 方法隐藏在内部
- 优点：使模块之间松耦合

**Incremental development 增量开发**

- 增量开发需要**以模块化设计为前提条件**；明确的**接口定义便于执行增量开发**

**Abstraction** 抽象

　　忽略细节

**Generality 一般化**

　　实际上就是写更通用的代码。 参数化上下文，移除前置条件，简化后置条件

#### 2.5 总结

　　结合具体的menu程序，学习了模块化设计、可重用接口、线程安全、设计原则等软件工程的方法，使自己对软件工程的思想方法深入理解和实践，受益匪浅。

end~