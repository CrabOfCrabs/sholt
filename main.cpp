#include <stdio.h>      //printf/getch itp.
#include <conio.h>      //kbhit()
#include <graphics.h>   //funkcje graficzne BGI
#include <windows.h>    //Sleep(xx)
#include <time.h>
#include <vector>
#include <iostream>

using namespace std;

class Figura
{
public :
    int x,y,b,k=WHITE;
    Figura()
    {
        b=(rand()%50)+25;
        x=(rand()%(640-2*b))+b;
        y=(rand()%(480-2*b))+b;
    };
    void givedata()
    {
        cout <<x<<" -x |"<<y<<"-y |"<<b<<"-b |"<<k<<"-k"<<endl;
    };
    virtual void rysuj()=0;
    void setcol()
    {
        setcolor(k);
        rysuj();
    };
};

class kolo      : public Figura
{
public :
    void rysuj()
    {
        circle(x,y,b/2);
    };
};
class kwadrat   : public Figura
{
public :
    void rysuj()
    {
        rectangle(x,y,x+b,y+b);
    };
};
class elipse    : public Figura
{
public :
    void rysuj()
    {
        ellipse(x,y,0,360,x%(b/2),y%(b/2));
    };
};

class TabFigur
{
public :
    std::vector<Figura*> figi;
    int indclr=-2;
    void rysall()
    {
        for(auto olo : figi)
        {

            olo->setcol();
        }
    }
    void setthat(int dod,int mod,int *ponlo)
    {
        cout << "rand - 0 manual -1" << endl;
        int wb=-1;
        cin >> wb;
        if(wb==1)
        {
            int co=-1;
            cout << "max-" << dod+mod-1<< "min-" << dod << endl;
            cin >> co;
            if(co>=dod&&co<=dod+mod-1)
            {
                setcolor(BLACK);
                figi.at(indclr)->rysuj();
                *ponlo=co;
                figi.at(indclr)->setcol();
            }
        }
        else if(wb==0)
        {
            setcolor(BLACK);
            figi.at(indclr)->rysuj();
            *ponlo=rand()%mod+dod;
            figi.at(indclr)->setcol();
        }
    };

    void addfig(int wb)
    {
        switch(wb)
        {
        case 1:
            figi.push_back(new kwadrat);
            break;
        case 2:
            figi.push_back(new elipse);
            break;
        case 3:
            figi.push_back(new kolo);
            break;
        case 4:
            int r =rand()%4+1;
            addfig(r);

        }
        figi.back()->rysuj();
    };
    void pokaz()
    {
        for(auto olo : figi)
        {
            olo->givedata();
        }
    };
    void edycja()
    {
        if(figi.size()==0)
        {
            cout << "brak elementow do edycji" << endl;
            return;
        }
        int wb=-2;
        char potwrd;
        char litr='a';

        do
        {
            cout << "0 wyjdz\n1 usun\n2 translacja\n3 rozmiar\n4 kolo\n5 pokaz wszystko w vBecktorze" << endl;
            pokaz();
            cin >> wb;
            switch(wb)
            {
            case 1: //usun
                do
                {
                    if(figi.size()==0)
                    {
                        cout << "brak elementow do edycji" << endl;
                        return;
                    }
                    setcolor(WHITE);
                    rysall();
                    if(figi.size()!=1)
                    {
                        cout << "Daj indeks(wyjdz -1) !!!  od:0 do max:" << figi.size()-1 << endl;
                        cin >> indclr;
                        setcolor(RED);
                        figi.at(indclr)->rysuj();
                    }
                    else
                    {
                        indclr=0;
                    }
                    if(indclr==-1)
                    {
                        break;
                    }


                    cout << "potwierdz=y kolejny indeks(do gory=w,w dol=s,wyjdz=q)" << endl ;
                    do
                    {
                        cin >> potwrd;
                        if(potwrd=='y')
                        {
                            setcolor(BLACK);
                            figi.at(indclr)->rysuj();
                            figi.erase(figi.begin()+indclr);
                            rysall();
                        }
                        else if(potwrd=='w')
                        {
                            figi.at(indclr)->setcol();
                            indclr++;
                            if(indclr==figi.size())
                            {
                                indclr=0;
                            };
                            setcolor(RED);
                            figi.at(indclr)->rysuj();
                            setcolor(WHITE);
                        }
                        else if(potwrd=='s')
                        {
                            figi.at(indclr)->rysuj();
                            indclr--;
                            if(indclr==-1)
                            {
                                indclr=figi.size()-1;
                            };
                            setcolor(RED);
                            figi.at(indclr)->rysuj();
                            setcolor(WHITE);
                        }
                        else if(potwrd=='q')
                        {
                            rysall();
                            break;
                        }
                        else
                        {
                            cout<< "takij ni ma" << endl;
                            figi.at(indclr)->rysuj();
                        }

                    }
                    while(potwrd!='y');
                    for(auto ol : figi)
                    {
                        ol->setcol();
                    }
                }
                while(1);
                break;
            case 2: //przesun
                setcolor(WHITE);
                rysall();
                if(figi.size()!=1)
                {
                    cout << "Daj indeks(wyjdz -1) !!!  od:0 do max:" << figi.size()-1 << endl;
                    cin >> indclr;
                    setcolor(RED);
                    figi.at(indclr)->rysuj();
                }
                else
                {
                    indclr=0;
                }
                if(indclr==-1)
                {
                    break;
                }
                if(figi.size()==1)
                {
                    do
                    {
                        cout << "x czy y (q wraca)"<<endl;
                        cin>>litr;
                        if(litr=='x')
                        {
                            setthat(figi.at(indclr)->b,640-2*figi.at(indclr)->b,&figi.at(indclr)->x);

                        }
                        else if(litr=='y')
                        {
                            setthat(figi.at(indclr)->b,480-2*figi.at(indclr)->b,&figi.at(indclr)->y);
                        }
                        else
                        {
                            cout <<"tylko x y q"<<endl;
                        }
                    }
                    while(litr!='q');
                    break;
                }
                cout << "potwierdz=y kolejny indeks(do gory=w,w dol=s,wyjdz=q)" << endl ;
                do
                {
                    cin >> potwrd;
                    if(potwrd=='y')
                        do
                        {
                            cout << "x czy y (q wraca)"<<endl;
                            cin>>litr;
                            if(litr=='x')
                            {
                                setthat(figi.at(indclr)->b,640-2*figi.at(indclr)->b,&figi.at(indclr)->x);

                            }
                            else if(litr=='y')
                            {
                                setthat(figi.at(indclr)->b,480-2*figi.at(indclr)->b,&figi.at(indclr)->y);
                            }
                            else
                            {
                                cout <<"tylko x y q"<<endl;
                            }
                        }
                        while(litr!='q');

                    else if(potwrd=='w')
                    {
                        figi.at(indclr)->setcol();
                        indclr++;
                        if(indclr==figi.size())
                        {
                            indclr=0;
                        };
                        setcolor(RED);
                        figi.at(indclr)->rysuj();
                        setcolor(WHITE);
                    }
                    else if(potwrd=='s')
                    {
                        figi.at(indclr)->rysuj();
                        indclr--;
                        if(indclr==-1)
                        {
                            indclr=figi.size()-1;
                        };
                        setcolor(RED);
                        figi.at(indclr)->rysuj();
                        setcolor(WHITE);
                    }
                    else if(potwrd=='q')
                    {
                        rysall();
                        break;
                    }
                    else
                    {
                        cout<< "takij ni ma" << endl;
                        figi.at(indclr)->rysuj();
                    }

                }
                while(potwrd!='y');


                break;
            case 3: //skaluj
                setcolor(WHITE);
                rysall();
                if(figi.size()!=1)
                {
                    cout << "Daj indeks(wyjdz -1) !!!  od:0 do max:" << figi.size()-1 << endl;
                    cin >> indclr;
                    setcolor(RED);
                    figi.at(indclr)->rysuj();
                }
                else
                {
                    indclr=0;
                }
                if(indclr==-1)
                {
                    break;
                }
                if(figi.size()==1)
                {
                    setthat(25,50,&figi.at(indclr)->b);
                    break;
                }
                cout << "potwierdz=y kolejny indeks(do gory=w,w dol=s,wyjdz=q)" << endl ;
                do
                {
                    cin >> potwrd;
                    if(potwrd=='y')

                        setthat(25,50,&figi.at(indclr)->b);

                    else if(potwrd=='w')
                    {
                        figi.at(indclr)->setcol();
                        indclr++;
                        if(indclr==figi.size())
                        {
                            indclr=0;
                        };
                        setcolor(RED);
                        figi.at(indclr)->rysuj();
                        setcolor(WHITE);
                    }
                    else if(potwrd=='s')
                    {
                        figi.at(indclr)->rysuj();
                        indclr--;
                        if(indclr==-1)
                        {
                            indclr=figi.size()-1;
                        };
                        setcolor(RED);
                        figi.at(indclr)->rysuj();
                        setcolor(WHITE);
                    }
                    else if(potwrd=='q')
                    {
                        rysall();
                        break;
                    }
                    else
                    {
                        cout<< "takij ni ma" << endl;
                        figi.at(indclr)->rysuj();
                    }

                }
                while(potwrd!='y');



                break;
            case 4: //kolor
                setcolor(WHITE);
                rysall();
                if(figi.size()!=1)
                {
                    cout << "Daj indeks(wyjdz -1) !!!  od:0 do max:" << figi.size()-1 << endl;
                    cin >> indclr;
                    setcolor(RED);
                    figi.at(indclr)->rysuj();
                }
                else
                {
                    indclr=0;
                }
                if(indclr==-1)
                {
                    break;
                }


                if(figi.size()==1)
                {
                    setthat(0,16,&figi.at(indclr)->k);
                    break;
                }
                cout << "potwierdz=y kolejny indeks(do gory=w,w dol=s,wyjdz=q)" << endl ;
                do
                {
                    cin >> potwrd;
                    if(potwrd=='y')

                        setthat(0,16,&figi.at(indclr)->k);

                    else if(potwrd=='w')
                    {
                        figi.at(indclr)->setcol();
                        indclr++;
                        if(indclr==figi.size())
                        {
                            indclr=0;
                        };
                        setcolor(RED);
                        figi.at(indclr)->rysuj();
                        setcolor(WHITE);
                    }
                    else if(potwrd=='s')
                    {
                        figi.at(indclr)->rysuj();
                        indclr--;
                        if(indclr==-1)
                        {
                            indclr=figi.size()-1;
                        };
                        setcolor(RED);
                        figi.at(indclr)->rysuj();
                        setcolor(WHITE);
                    }
                    else if(potwrd=='q')
                    {
                        rysall();
                        break;
                    }
                    else
                    {
                        cout<< "takij ni ma" << endl;
                        figi.at(indclr)->rysuj();
                    }

                }
                while(potwrd!='y');
                break;

            case 5:
                pokaz();
                break;


            }
        }
        while(wb!=0);
    }
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
//Tutaj kod zwiazany z rysowaniem
//******************************************************************************************************************
    srand(time(0));
    TabFigur ma;
    int gwb=0;
    do
    {
        int jk=0;
        cout << "0 wyjdz\n1 dodaj figra\n2 edytuj(usuwanie translacja rozmiar kolor)\n3 pokaz wszystkie elementy" << endl;
        scanf("%d",&gwb);
        switch(gwb)
        {
        case 0:
            return 1;
            break;
        case 1:
            printf("1 kwadrat \n2 elibse\n3 kolo\n4 rand\n");

            cin >> jk;
            ma.addfig(jk);
            break;         //daj figura
        case 2:
            ma.edycja();
            break;         //zmien figure,pozycje,zmien wielkosc,zamien pozycje,usun
        case 3:
            ma.pokaz();
            break;         //info o figach

        }
    }
    while(gwb!=0);

    //******************************************************************************************************************
    //koniec rysowania
    //program czeka na naciœniêcie klawisza i ZAMYKA tryb graficzny!
    fflush(stdin);
    getch(); //tylko zatrzymanie programu, żeby nie zamykał natychmiast okna graficznego
    closegraph(); //koniec trybu graficznego

    return(0);
}
