#include <stdio.h>      //printf/getch itp.
#include <conio.h>      //kbhit()
#include <graphics.h>   //funkcje graficzne BGI
#include <windows.h>    //Sleep(xx)
#include <time.h>
#include <vector>
#include <iostream>

using namespace std;

class Figura{
    public :
    int x,y,b,k=WHITE;
    Figura(){
        b=(rand()%50)+25;
        x=(rand()%(640-2*b))+b;
        y=(rand()%(480-2*b))+b;
    };
    void crobs(){
        cout << x << " | " << y << " | " << b << " | " << k << endl;
    };
    virtual void rysuj()=0;
    void setcol(){setcolor(k);rysuj();};
};

class kolo      : public Figura{
    public :
    void rysuj(){circle(x,y,b/2);};
};
class kwadrat   : public Figura{
    public :
    void rysuj(){rectangle(x,y,x+b,y+b);};
};
class elipse    : public Figura{
    public :
    void rysuj(){ellipse(x,y,0,360,x%(b/2),y%(b/2));};
};


class TabFigur{
    public :
        std::vector<Figura*> figi;
    void rysall(){
        for(auto olo : figi){
            olo->rysuj();
        }
    }
    void addfig(){
        int wb;
        cin >> wb;
        switch(wb){
        case 1:
            figi.push_back(new kwadrat);
            break;
        case 2:
            figi.push_back(new elipse);
            break;
        case 3:
            figi.push_back(new kolo);
            break;
        default:
            return;};
        figi.back()->rysuj();
    };
    void pokaz(){}
    void edycja(){
        if(figi.size()==0){cout << "brak elementow do edycji" << endl;return;}
        int wb=-2,indclr=-2;
        do{
        cin >> wb;
        switch(wb){
        case 1: //usun
            do{
            if(figi.size()==0){cout << "brak elementow do edycji" << endl;return;}
            cout << "Daj indeks(wyjdz -1) !!!  od:0 do max:" << figi.size()-1 << endl;
            cin >> indclr;
            if(indclr==-1){break;}
            setcolor(WHITE);
            rysall();
            setcolor(RED);figi.at(indclr)->rysuj();
            cout << "potwierdz=y kolejny indeks(do gory=w,w dol=s)" << endl ;
            char potwrd;
            do{
            cin >> potwrd;
            if(potwrd=='y'){
                setcolor(BLACK);
                figi.at(indclr)->rysuj();
                figi.erase(figi.begin()+indclr);
                rysall();}
            else if(potwrd=='w'){
                    figi.at(indclr)->setcol();
                    indclr++;
                    if(indclr==figi.size()){indclr=0;};
                    setcolor(RED);figi.at(indclr)->rysuj();}
            else if(potwrd=='s'){figi.at(indclr)->rysuj();indclr--;if(indclr==-1){indclr=figi.size()-1;};setcolor(RED);figi.at(indclr)->rysuj();}
            else{cout<< "takij ni ma" << endl;figi.at(indclr)->rysuj();}
            }while(potwrd!='y');
            for(auto olo : figi){olo->setcol();}
            }while(1);
            break;
        case 2: //przesun
            break;
        case 3: //skaluj
            break;
        case 4: //kolor
            break;
        default:
            break;
        }
        }while(wb!=0);
    };
};
int main()
{
    int GraphDriver = DETECT;
    int GraphMode;
    int ErrorCode;
    initgraph(&GraphDriver, &GraphMode,"");
    ErrorCode = graphresult();
    if(ErrorCode != grOk)
    {
        printf("Blad trybu graficznego: %s\n", grapherrormsg(ErrorCode) );
        exit(1);
    }
    //Tutaj kod związany z rysowaniem
    //******************************************************************************************************************
    srand(time(0));
    TabFigur ma;
    int gwb=0;
    do{
        scanf("%d",&gwb);
        switch(gwb){
        case 1:
            printf("1 kwadrat \n2 elibse\n3 kolo\n");
            ma.addfig();
            break;         //daj figura
        case 2:
            ma.edycja();
            break;         //zmien figure,pozycje,zmien wielkosc,zamien pozycje,usun
        case 3:
            ma.pokaz();
            break;         //info o figach
        }
    }while(gwb!=0);


    //******************************************************************************************************************
    //koniec rysowania
    //program czeka na naciœniêcie klawisza i ZAMYKA tryb graficzny!
    fflush(stdin);
    getch(); //tylko zatrzymanie programu, żeby nie zamykał natychmiast okna graficznego
    closegraph(); //koniec trybu graficznego

    return(0);
}
