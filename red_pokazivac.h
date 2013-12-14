struct covjek
{
    int ai,bi,ci,di,ei,datum;
    char ime[20],prezime[20],spol[1];
    covjek*sljedeci;
};

struct queue
{
    covjek* front,*rear;
};

int AddOne(int n)
{
    return((n+1)%10000);
}

int InitQ(queue*red)
{
    covjek*glava=new covjek;
    glava->sljedeci=NULL;
    red->front=glava;
    red->rear=glava;
}

bool IsEmptyQ(queue*red)
{
    if(red->rear==red->front)return 1;
    return 0;
}

void EnQueueQ(covjek*pacijent,queue*red)
{
    red->rear->sljedeci=pacijent;
    pacijent->sljedeci=NULL;
    red->rear=pacijent;
}

covjek*FrontQ(queue*red)
{
    covjek*pacijent;
    pacijent=red->front->sljedeci;
    return pacijent;
}

void DeQueueQ(queue*red)
{
    covjek*glava=new covjek;
    glava=red->front;
    red->front=glava->sljedeci;
    delete glava;
}
