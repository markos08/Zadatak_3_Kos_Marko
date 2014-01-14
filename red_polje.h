#include <iostream>
using namespace std;

struct covjek
{
    int ai,bi,ci,di,ei,datum;
    char ime[20],prezime[20],spol[1];
};

int AddOne(int n)
{
    return((n+1)%10000);
}

struct queue
{
    covjek*pacijent[10000];
    int front,rear;
};

void EnQueueQ (covjek*pacijent, queue *red)
{
    red->rear = AddOne(red->rear);
    red->pacijent[red->rear] = pacijent;
    
}

int IsEmptyQ(queue*red)
{
    if(AddOne(red->rear)==red->front)return 1;
    return 0;
}

covjek*FrontQ(queue*red)
{
    if(!IsEmptyQ)cout<<"Red je prazan!"<<endl;
    return red->pacijent[red->front];
}

void DeQueueQ(queue*red)
{
    red->front++;
}

void InitQ(queue*red)
{
    red->front=0;
    red->rear=9999;
}
