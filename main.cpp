#include <iostream>
//#include "red_polje.h"
#include "red_pokazivac.h"
#include <ctime>
#include <stdlib.h>
#include <cstring>
using namespace std;
//-----------------------------------------------
int ukupno=0,N;
covjek*brzi_red;
char prioritet[][30]=
{
    "hitni slucajevi",
    "invalidi",
    "trudnice",
    "djeca mlada od 6 godina",
    "ostali pacijenti"
};

char vrsta_usluge[][30]=
{
    "pregled",
    "previjanje",
    "recepti",
    "uputnice"
};

char vrsta_ordinacije[][30]=
{
    "obiteljska medicina",
    "oftalmologija",
    "dermatovenerologija",
    "ginekologija",
    "urologija"
};
covjek*generirani_brojevi;
//-----------------------------------------------
void kopiraj(covjek*kopija,covjek*original){
     kopija->ai=original->ai;
     kopija->bi=original->bi;
     kopija->ci=original->ci;
     kopija->di=original->di;
     kopija->ei=original->ei;
     strcpy(kopija->ime,original->ime);
     strcpy(kopija->prezime,original->prezime);
     kopija->datum=original->datum;
     strcpy(kopija->spol,original->spol);
     }
void pacijenti(queue*red)
{
    cout<<"N = ";
    cin>>N;
    ukupno=N*3;
    generirani_brojevi=new covjek[N];
    for(int i=0; i<N; i++)
    {
        covjek*jedna_osoba=new covjek;
        generirani_brojevi[i].ai=rand()%251+50;
        generirani_brojevi[i].bi=rand()%251+50;
        generirani_brojevi[i].ci=rand()%5+1;
        generirani_brojevi[i].di=rand()%4+1;
        generirani_brojevi[i].ei=rand()%5+1;
        if(generirani_brojevi[i].ci==3   &&
                generirani_brojevi[i].ei==5)i--;
        else if(generirani_brojevi[i].ci==1   &&
                generirani_brojevi[i].ei==1)i--;
    }
}
//-----------------------------------------------
void ispis(covjek*jedna_osoba)
{
    cout<<"------------------------------\n";
    cout<<"Ime: "<<jedna_osoba->ime<<endl;
    cout<<"Prezime: "<<jedna_osoba->prezime<<endl;
    cout<<"Datum rodenja: "<<jedna_osoba->datum<<endl;
    cout<<"Spol: "<<jedna_osoba->spol<<endl;
}
//-----------------------------------------------
void ispis_reda(queue*red)
{
    while(!IsEmptyQ(red))
    {
        covjek*jedna_osoba=new covjek;
        jedna_osoba=FrontQ(red);
        ispis(jedna_osoba);
        DeQueueQ(red);
    }
}
//-----------------------------------------------
void dodaj(queue*red)
{
    covjek*pacijenti=new covjek[N*3];
    int br=0;
    for(int i=0; i<N; i++)
        for(int j=0; j<3; j++)
        {
        	int prioritet_int=generirani_brojevi[i].ci-1;
        	int vrsta_usluge_int=generirani_brojevi[i].di-1;
        	int vrsta_ordinacije_int=generirani_brojevi[i].ei-1;
            cout<<"Upisite podatke za pacijenta koji ima:"<<endl;
			cout<<"Prioritet: "<<prioritet[prioritet_int]<<endl;
            cout<<"Vrsta usluge: "<<vrsta_usluge[vrsta_usluge_int]<<endl;
            cout<<"Vrsta ordinacije: "<<vrsta_ordinacije[vrsta_ordinacije_int]<<endl;
            covjek*jedna_osoba=new covjek;
            cout<<"Ime: ";
            cin>>jedna_osoba->ime;
            cout<<"Prezime: ";
            cin>>jedna_osoba->prezime;
            cout<<"Datum rodenja: ";
            cin>>jedna_osoba->datum;
            cout<<"Spol: ";
            cin>>jedna_osoba->spol;
            jedna_osoba->ai=generirani_brojevi[i].ai;
            jedna_osoba->bi=generirani_brojevi[i].bi;
            jedna_osoba->ci=generirani_brojevi[i].ci;
            jedna_osoba->di=generirani_brojevi[i].di;
            jedna_osoba->ei=generirani_brojevi[i].ei;
            EnQueueQ(jedna_osoba,red);
            kopiraj(&pacijenti[br],jedna_osoba);
            //memcpy(&pacijenti[br],jedna_osoba,sizeof(covjek));
            br++;
        }
    for(int i=0; i<N*3; i++)
    {
        if((pacijenti[i].spol=="Z")  &&
                (pacijenti[i].ei==2)      &&
                (pacijenti[i].datum<19881201))ispis(&pacijenti[i]);
    }
}
//-----------------------------------------------

covjek*pom;
covjek*pom2;
void pomocni(queue*red)
{
    cout<<"Izbacujem: \n";
    covjek pomocni[N*3];
    static int redni_broj_pomocni=0;
    static int redni_broj_pom=0;
    while(!IsEmptyQ(red))
    {
        covjek*jedna_osoba=new covjek;
        jedna_osoba=FrontQ(red);
        kopiraj(&pom[redni_broj_pom],jedna_osoba);
        redni_broj_pom++;
        DeQueueQ(red);
        if(jedna_osoba->datum<19631201   &&
                jedna_osoba->ci==2            &&
                jedna_osoba->ei==1            &&
                jedna_osoba->di==2)
        {
            ispis(jedna_osoba);
            ukupno--;
        }
        else{
            memcpy(&pomocni[redni_broj_pomocni],jedna_osoba,sizeof(covjek));
            redni_broj_pomocni++;
            }
    }
    InitQ(red);
    for(int i=0;i<redni_broj_pomocni;i++){
        covjek*jedna_osoba=new covjek;
        kopiraj(jedna_osoba,&pomocni[i]);
        EnQueueQ(jedna_osoba,red);
    }
    cout<<"Stanje na redu nakon izbacivanja: \n";
    for(int i=0;i<redni_broj_pom;i++)
          ispis(&pom[i]);  
}
//-----------------------------------------------
int br_pom,br_pomocni,br_brzi;
void rekurzija(queue*red,int posto,int pozicija)
{
    if(IsEmptyQ(red))return;
    covjek*pomocni=new covjek;
    if(pozicija<posto)
    {
        pomocni=FrontQ(red);
        DeQueueQ(red);
        pozicija++;
        kopiraj(&pom[br_pom],pomocni);
        br_pom++;
        rekurzija(red,posto,pozicija);
    }
    else
        while(!IsEmptyQ(red))
        {
            pomocni=FrontQ(red);
            kopiraj(&pom2[br_pomocni],pomocni);
            br_pomocni++;
            kopiraj(&brzi_red[br_brzi],pomocni);
            br_brzi++;
            DeQueueQ(red);
        }
    EnQueueQ(pomocni,red);
}

//-----------------------------------------------
void obrni_red(queue*red)
{
    if(IsEmptyQ(red))return;
    covjek*pomocni=new covjek;
    pomocni=FrontQ(red);
    DeQueueQ(red);
    EnQueueQ(pomocni,red);
}
//-----------------------------------------------
int main()
{
    queue*red=new queue;
    InitQ(red);
    int izbor;
    do
    {
        pom=new covjek[N*3];
        pom2=new covjek[N*3];
        brzi_red=new covjek[N*3];
        cout<<"1. Generiranje"<<endl;
        cout<<"2. Dodavanje pacijenata"<<endl;
        cout<<"3. Brisanje pacijenata invalida"<<endl;
        cout<<"4. Brzi red"<<endl;
        cin>>izbor;
        system("cls");
        if(izbor==1)pacijenti(red);
        else if(izbor==2)dodaj(red);
        else if(izbor==3)pomocni(red);
        else if(izbor==4)
        {
             br_pom=0,br_pomocni=0,br_brzi=0;
            int posto=0.7*ukupno;
            rekurzija(red,posto,0);
            cout<<"Stanje na glavnom redu: "<<endl;
            for(int i=0;i<br_pom;i++)
                    ispis(&pom[i]);
            cout<<"Stanje na pomocnom redu: "<<endl;
            for(int i=br_pomocni-1;i>=0;i--)
                    ispis(&pom2[i]);
        }
    }
    while(izbor!=9);
    return 0;
}
