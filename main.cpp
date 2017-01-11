#include <iostream>
#include <time.h>
#include <cstdlib>
#include <fstream>
#include <stdlib.h>
#define NR_CARTI 52
#define NR_JUCATORI 1000
using namespace std;
ifstream deckIn("deck.txt");
ofstream deckkOut("deck.txt");
ifstream dataIn("database.txt");
ofstream dataOut("database.txt");
struct carte
{
    int numar;
    int simbol;
};
struct split
{
    carte hand1[NR_CARTI];
    carte hand2[NR_CARTI];
};
struct database
{
    string user;
    string pass;
    long earnings;
    long handsWon;
};
struct player
{
    bool stand;
    bool bust;
    int suma;
    carte carti[NR_CARTI];
    int bet;
    int money;
    int earnings;
    split splitHand;
    int nrCarti;
    string user;
    long handsWon;
    string pass;
};
struct dealer
{
    bool stand;
    bool bust;
    int suma;
    carte cartiDealer[NR_CARTI];
    int nrCarti;
};
void shuffle(carte v[NR_CARTI], carte z[NR_CARTI])
{
    int i, n=52, j, k;
    for(i=0;i<NR_CARTI;i++)
    {
        j=rand()%n;
        z[i].numar=v[j].numar;
        z[i].simbol=v[j].simbol;
        for(k=j;k<n;k++)
        {
            v[k].numar=v[k+1].numar;
            v[k].simbol=v[k+1].simbol;
        }
        n--;
    }
}
void moveCard(carte Deck[NR_CARTI], carte deckS[NR_CARTI], int &nr)
{
    int i;
    deckS[nr]=Deck[0];
    for(i=0;i<NR_CARTI-1;i++)
    {
        Deck[i]=Deck[i+1];
    }
    nr++;
    if(nr==52)
    {
       shuffle(deckS,Deck);
       nr=0;
    }
}
void hit(carte Cards[NR_CARTI], carte b[NR_CARTI], carte deck[NR_CARTI], int &s, int &i, int &bust, int &n)
{
    int j;
    Cards[i]=b[0];
    if(Cards[i].numar<=9) s=s+Cards[i].numar;
    else
    {
        if(Cards[i].numar>=10 && Cards[i].numar<=13) s=s+10;
        else
        {
            if(s+11<=21) s=s+11;
            else
            {
                Cards[i].numar=1;
                s=s+1;
            }
        }
    }
    moveCard(b,deck, n);
    i++;
    if(s>21)
    {
        for(j=0;j<i-1;j++)
        {
            if(Cards[i].numar==14)
            {
                s=s-10;
                Cards[i].numar=1;
            }
        }
    }
    if(s>21) bust=1;
}
void startGame(dealer a, carte deck[NR_CARTI], carte deckS[NR_CARTI], int &nr, player b[4], int nrPlayers)
{
    int i;
    a.suma=0;
    a.cartiDealer[0]=deckS[0];
    if(a.cartiDealer[0].numar<=10) a.suma=a.suma+a.cartiDealer[0].numar;
    else
    {
        if(a.cartiDealer[0].numar>10 && a.cartiDealer[0].numar<=13) a.suma=a.suma+10;
        else
        {
            if(a.cartiDealer[0].numar==14) a.suma+=11;
        }
    }
    moveCard(deckS, deck, nr);
    a.cartiDealer[1]=deckS[0];
    if(a.cartiDealer[1].numar<=10) a.suma=a.suma+a.cartiDealer[1].numar;
    else
    {
        if(a.cartiDealer[1].numar>10 && a.cartiDealer[1].numar<=13) a.suma=a.suma+10;
        else
        {
            if(a.cartiDealer[1].numar==14) a.suma+=11;
        }
    }
    moveCard(deckS, deck, nr);
    a.nrCarti=2;
    for(i=0;i<nrPlayers;i++)
    {
        b[i].suma=0;
        b[i].carti[0]=deckS[0];
        if(b[i].carti[0].numar<=10) b[i].suma+=b[i].carti[0].numar;
        else
        {
            if(b[i].carti[0].numar>10 && b[i].carti[0].numar<=13) b[i].suma+=10;
            else
            {
                if(b[i].carti[0].numar==14) b[i].suma+=11;
            }
        }
        moveCard(deckS, deck, nr);
        b[i].carti[1]=deckS[0];
        if(b[i].carti[1].numar<=10) b[i].suma+=b[i].carti[1].numar;
        else
        {
            if(b[i].carti[1].numar>10 && b[i].carti[1].numar<=13) b[i].suma+=10;
            else
            {
                if(b[i].carti[1].numar==14) b[i].suma+=11;
            }
        }
        moveCard(deckS, deck, nr);
        b[i].nrCarti=2;
    }

}
int main()
{
    int numberPlayers, l;
    player Players1[6];
    dataIn>>numberPlayers;
    database players[NR_JUCATORI];
    for(l=0;l<numberPlayers;l++)
    {
        dataIn>>players[l].user>>players[l].pass>>players[l].earnings>>players[l].handsWon;
    }
    int i;
    carte deck[NR_CARTI];
    for(i=0;i<52;i++)
    {
        deckIn>>deck[i].numar>>deck[i].simbol;
    }
    carte deckShuffled[NR_CARTI];
    shuffle(deck, deckShuffled);
    cout<<"BlackJack"<<endl;
    cout<<"Input anything to continue";
    string a;
    cin>>a;
    system("cls");
    Menu:
    cout<<"Menu"<<endl;
    cout<<"1) For Singleplayer, input 1."<<endl;
    cout<<"2) For Multiplayer, input 2."<<endl;
    cout<<"3) To view the Leaderboard, input 3."<<endl<<endl;
    cout<<"Your Answer:";
    int ans1;
    cin>>ans1;
    if(ans1!=1 && ans1!=2 && ans1!=3)
    {
        system("cls");
        cout<<"Error at input!"<<endl<<endl;
        goto Menu;
    }
    if(ans1==3)
    {
        leaderError:
        system("cls");
        int p=0;
        while(p<=10 && p<numberPlayers)
        {
            cout<<p+1<<") "<<players[p].user<<"   "<<players[p].earnings<<"   "<<players[p].handsWon<<endl;
        }
        cout<<"To go back to the menu, input Back."<<endl;
        string ansLeader;
        cout<<"Your answer: ";
        cin>>ansLeader;
        if(ansLeader!="Back")
        {
            system("cls");
            cout<<"Error at input!"<<endl<<endl;
            goto leaderError;
        }
        else
        {
            system("cls");
            goto Menu;
        }
    }
    int numPlayers;
    dealer AI;
    if(ans1==1)
    {
        numPlayers=1;
    }
    if(ans1==2)
    {
        system("cls");
        cout<<"Please enter the number of players (between 2 and 6): ";
        cin>>numPlayers;
    }
    for(i=0;i<numPlayers;i++)
    {
        loginOrRegister:
        cout<<"1) To login, input 1."<<endl;
        cout<<"2) To register, input 2."<<endl;
        cout<<"3) To go back to the menu, input 3."<<endl<<endl;
        cout<<"Your input: ";
        int rasp;
        cin>>rasp;
        if(rasp!=1 && rasp!=2 && rasp!=3)
        {
            system("cls");
            cout<<"Error at input!"<<endl<<endl;
            goto loginOrRegister;
        }
        if(rasp==3)
        {
            system("cls");
            goto Menu;
        }
        if(rasp==1)
        {
            system("cls");
            login:
            cout<<"Player "<<i+1<<":"<<endl;
            cout<<"If you want to go back, enter 1. Otherwise, enter your username."<<endl;
            cout<<"Username: ";
            cin>>Players1[i].user;
            cout<<endl;
            if(Players1[i].user=="1") goto loginOrRegister;
            bool gasit=false;
            for(l=0;l<numberPlayers;l++)
            {
                if(Players1[i].user==players[l].user)
                {
                    gasit=true;
                    break;
                }
            }
            if(gasit==false)
            {
                system("cls");
                cout<<"Wrong username!"<<endl;
                goto login;
            }
            else
            {
                cout<<"Password: ";
                cin>>Players1[i].pass;
                cout<<endl;
                if(Players1[i].pass!=players[l].pass)
                {
                    system("cls");
                    cout<<"Wrong password"<<endl;
                    goto login;
                }
            }

        }
        if(rasp==2)
        {
            system("cls");
            register1:
            cout<<"Player "<<i+1<<":"<<endl;
            cout<<"If you want to go back, enter 1. Otherwise, enter your desired username."<<endl;
            cout<<"Username: ";
            cin>>Players1[i].user;
            cout<<endl;
            if(Players1[i].user=="1") goto loginOrRegister;
            bool gasit=false;
            for(l=0;l<numberPlayers;l++)
            {
                if(Players1[i].user==players[l].user)
                {
                    gasit=true;
                    break;
                }
            }
            if(gasit)
            {
                system("cls");
                cout<<"Username already taken!"<<endl;
                goto register1;
            }
            else
            {
                cout<<"Please enter your desired password."<<endl;
                cout<<"Password: ";
                cin>>Players1[i].pass;
                cout<<endl;
            }

        }
    }
    for(i=0;i<numPlayers;i++)
    {
        system("cls");
        buyIn:
        cout<<Players1[i].user<<", please insert your buy-in (minimum of 100 and maximum of 5000 in multiples of 50): ";
        cin>>Players1[i].money;
        cout<<endl;
        if(Players1[i].money<100 || Players1[i].money>5000)
        {
            system("cls");
            cout<<"Error at buy-in!"<<endl;
            goto buyIn;
        }
        else
        {
            if(Players1[i].money%50!=0)
            {
                system("cls");
                cout<<"Error at buy-in!"<<endl;
                goto buyIn;
            }
        }
        Players1[i].earnings=0;
        Players1[i].handsWon=0;
    }


    return 0;

}
