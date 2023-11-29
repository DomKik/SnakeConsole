#include <iostream>
#include <Windows.h>
#include <stdlib.h>
#include <list>
#include <conio.h>
#include <time.h>

using namespace std;

int weight,height,speed;
char WygladPlanszy=219;
void RysujPoziomo()
{
    for(int i=0; i<(weight+2); i++)
    {
        cout << WygladPlanszy << WygladPlanszy;
    }
}

void idzdoxy(int x, int y)
{
    HANDLE hCon;
    COORD dwPos;

    dwPos.X = x;
    dwPos.Y = y;

    hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hCon, dwPos);
}

int main()
{
    int Xweza,Yweza,Xfood,Yfood,historiaX,historiaY,czekanie,iter,hard,Xkolce,Ykolce,odp;
    unsigned int dlugosc,iloscFooda,maxi,limit;
    list <int> historiaXweza;
    list <int> historiaYweza;
    char kierunek,waz=219,klawisz,wczesniej,foodzik=3, kolce=15;
    cout << "Witaj w grze Snake by Dominik w wersji 1.2!\nSTEROWANIE: W-GORA, S-DOL, A-LEWO, D-PRAWO" << endl;
restart:
    iter=0; dlugosc=3; maxi=4; iloscFooda=0; limit=18;
    cout << "Jesli chcesz, by rozgrywka byla trudniejsza wpisz 1, jesli nie 0" << endl;
    cin>>hard;
    if(hard!=1) {hard=0;}
    else {cout << kolce << kolce << " Jesli zobaczysz taki znak, mozesz sie na nim skuc" << endl;}
szerokosc:
    cout << "Podaj szerokosc planszy (10-30)" << endl;
    cin>>weight;
    if(weight<10 || weight>30){ goto szerokosc;}
wysokosc:
    cout << "Podaj wysokosc planszy (10-30)" << endl;
    cin>>height;
    if(height<10 || height>30){ goto wysokosc;}
szybkosc:
    cout << "Podaj poczatkowa szybkosc gry (5-20)" << endl;
    cin>>speed;
    if(speed<5 || speed>20) {goto szybkosc;}
    char plansza[weight+2][height+2];
odNowa:
    system("cls");
    RysujPoziomo();
    cout << endl;
    for(int i=0; i<height; i++)
    {
        cout << WygladPlanszy << WygladPlanszy;
        for(int j=0; j<weight; j++)
        {
            cout << "  ";
        }
        cout << WygladPlanszy << WygladPlanszy << endl;
    }
    RysujPoziomo();
    for(int i=0; i<(weight+2); i++)
    {
        plansza[i][0]='!';
        plansza[i][height+1]='!';
    }
    for(int i=0; i<(height+2); i++)
    {
        plansza[0][i]='!';
        plansza[weight+1][i]='!';
    }
      for(int i=1; i<(height+1); i++)
    {
        for(int j=1; j<(weight+1); j++)
        {
            plansza[j][i]='P';
        }
    }
    /////////GRA WLASCIWA///////////
    srand (time(NULL));
    Xweza=rand()%(weight-3)+2;
    Yweza=rand()%(height-3)+2;
    wczesniej=0;
        for(;;)
    {
        iter++;
        if((iter%90)==0) {speed++;}
        idzdoxy((Xweza*2), Yweza);
        cout << waz << waz;
        historiaX=Xweza; historiaY=Yweza;
        historiaXweza.push_back(historiaX); historiaYweza.push_back(historiaY);
        if(dlugosc<historiaXweza.size())
            {
                idzdoxy(historiaXweza.front()*2,historiaYweza.front());
                cout << "  ";
                plansza[historiaXweza.front()][historiaYweza.front()]='P';
                historiaXweza.pop_front(); historiaYweza.pop_front();
            }
        idzdoxy(0,(height+2)); cout << "Obecna wielkosc: " << historiaXweza.size();
        czekanie=rand()%20+2;
losowanieFooda:
    if(((iter%czekanie)==0) && (maxi>=iloscFooda))
        {
            Xfood=rand()%weight+1;
            Yfood=rand()%height+1;
            if(plansza[Xfood][Yfood]=='W') {goto losowanieFooda;}
            plansza[Xfood][Yfood]='F';
            iloscFooda++;
            idzdoxy((Xfood*2), Yfood); cout << foodzik << foodzik;
        }
    if(hard==1 && (dlugosc%limit)==0)
        {
            srand(time(NULL));
LosowanieKolcy:
            Xkolce=rand()%weight+1;
            Ykolce=rand()%height+1;
            if(plansza[Xkolce][Ykolce]!='P') {goto LosowanieKolcy;}
            plansza[Xkolce][Ykolce]='!';
            idzdoxy((Xkolce*2),Ykolce);
            cout << kolce << kolce;
            limit--;
        }
        Sleep(((4000-(height*weight*2))/speed-5));
        if(kbhit())
        {
            klawisz=getch();
            switch(klawisz)
            {
        case 'w':
            if(wczesniej!='s') {kierunek='w';}
            else {kierunek=wczesniej;}
            break;
        case 'a':
            if(wczesniej!='d') {kierunek='a';}
            else {kierunek=wczesniej;}
            break;
        case 's':
            if(wczesniej!='w') {kierunek='s';}
            else {kierunek=wczesniej;}
            break;
        case 'd':
            if(wczesniej!='a') {kierunek='d';}
            else {kierunek=wczesniej;}
            break;
            }
        if(klawisz=='w' || klawisz=='a' || klawisz=='s'|| klawisz=='d') {wczesniej=kierunek;}
        }
        switch(kierunek)
        {
        case 'w':
            Yweza--;
            break;
        case 'a':
            Xweza--;
            break;
        case 's':
            Yweza++;
            break;
        case 'd':
            Xweza++;
            break;
        }
        if((plansza[Xweza][Yweza]=='!') || (plansza[Xweza][Yweza]=='W'))
            {
                idzdoxy(0,height+3);
                cout << "Koniec gry!  Twoja dlugosc: " << dlugosc << endl;
                historiaXweza.clear(); historiaYweza.clear();
                cout << "Chcesz zaczac od nowa z tymi samymi ustawieniami? jest tak napisz 1, jesli nie napisz 0" << endl;
                cin>>odp;
                if(odp==1) {goto odNowa;}
                else {goto restart;}
            }
        if(plansza[Xweza][Yweza]=='F')
            {
                dlugosc++;
                if((dlugosc%17)==0) {limit=18;}
                iloscFooda--;
                plansza[Xweza][Yweza]='P';
            }
        plansza[historiaX][historiaY]='W';
    }
    return 0;
    }
