#include <iostream>
#include <time.h>
#include <cstdlib>
#include <fstream>
#include <stdlib.h>
#include <string>
#define NR_CARTI 52
#define NR_JUCATORI 1000
using namespace std;
struct carte
{
    int numar;
    int simbol;
};
struct split
{
    carte hand1[NR_CARTI];
    carte hand2[NR_CARTI];
    int suma1;
    int suma2;
    bool bust1;
    bool bust2;
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
void hit(carte deck[NR_CARTI], carte deckS[NR_CARTI], int &nr, player &a)
{
    int l, gasit=1;
    a.carti[a.nrCarti]=deckS[0];
    if(a.carti[a.nrCarti].numar<=10) a.suma=a.suma+a.carti[a.nrCarti].numar;
    else
    {
        if(a.carti[a.nrCarti].numar>10 && a.carti[a.nrCarti].numar<=13) a.suma=a.suma+10;
        else
        {
            if(a.carti[a.nrCarti].numar==14) a.suma=a.suma+11;
        }
    }
    moveCard(deckS, deck, nr);
    a.nrCarti++;
    while(a.suma>21 && gasit==1)
    {
        gasit=0;
        for(l=0;l<a.nrCarti;l++)
            if(a.carti[l].numar==14)
            {
                a.carti[l].numar=1;
                a.suma=a.suma-10;
                gasit=1;
                break;
            }
    }
    if(a.suma>21) a.bust=true;
}
void startGame(dealer &a, carte deck[NR_CARTI], carte deckS[NR_CARTI], int &nr, player b[7], int nrPlayers)
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
    if(a.suma>21)
    {
        a.cartiDealer[0].numar=1;
        a.suma-=10;
    }
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
        if(b[i].suma>21)
        {
            b[i].carti[0].numar=1;
            b[i].suma-=10;
        }
    }

}
void dealerCards(dealer AI,player Players1[7], int numPlayers, int i)
{
    int l,j;
    char simbol;
    for(l=0;l<AI.nrCarti;l++)
    {
        if(AI.cartiDealer[l].numar>=2 && AI.cartiDealer[l].numar<=10) cout<<AI.cartiDealer[l].numar;
            else
            {
                if(AI.cartiDealer[l].numar==11) cout<<'J';
                else
                {
                    if(AI.cartiDealer[l].numar==12) cout<<'Q';
                    else
                    {
                        if(AI.cartiDealer[l].numar==13) cout<<'K';
                        else
                        {
                            if(AI.cartiDealer[l].numar==14 || AI.cartiDealer[l].numar==1) cout<<'A';
                        }
                    }
                }
            }
            if(AI.cartiDealer[l].simbol==1) simbol=003;
            if(AI.cartiDealer[l].simbol==2) simbol=004;
            if(AI.cartiDealer[l].simbol==3) simbol=005;
            if(AI.cartiDealer[l].simbol==4) simbol=006;
            cout<<simbol<<";  ";
    }
    cout<<endl;
    cout<<"Total= "<<AI.suma;
    cout<<endl;
    for(j=0;j<numPlayers;j++)
    {
        cout<<Players1[j].user<<"'s cards:"<<endl;
        for(l=0;l<Players1[j].nrCarti;l++)
        {
            if(Players1[j].carti[l].numar>=2 && Players1[j].carti[l].numar<=10) cout<<Players1[j].carti[l].numar;
            else
            {
                if(Players1[j].carti[l].numar==11) cout<<'J';
                else
                {
                    if(Players1[j].carti[l].numar==12) cout<<'Q';
                    else
                    {
                        if(Players1[j].carti[l].numar==13) cout<<'K';
                        else
                        {
                            if(Players1[j].carti[l].numar==14 || Players1[j].carti[l].numar==1) cout<<'A';
                        }
                    }
                }
            }
            if(Players1[j].carti[l].simbol==1) simbol=003;
            if(Players1[j].carti[l].simbol==2) simbol=004;
            if(Players1[j].carti[l].simbol==3) simbol=005;
            if(Players1[j].carti[l].simbol==4) simbol=006;
            cout<<simbol<<"; ";
        }
        cout<<endl;
        cout<<"Total="<<Players1[j].suma<<endl;
    }
}
void showcards(dealer AI, player Players1[7], int numPlayers, int i)
{
    char simbol;
    int l, j;
    cout<<"Dealer's cards: ";
    for(l=0;l<AI.nrCarti;l++)
    {
        if(l==0)
        {
            if(AI.cartiDealer[0].numar>=2 && AI.cartiDealer[0].numar<=10) cout<<AI.cartiDealer[0].numar;
            else
            {
                if(AI.cartiDealer[0].numar==11) cout<<'J';
                else
                {
                    if(AI.cartiDealer[0].numar==12) cout<<'Q';
                    else
                    {
                        if(AI.cartiDealer[0].numar==13) cout<<'K';
                        else
                        {
                            if(AI.cartiDealer[0].numar==14 || AI.cartiDealer[0].numar==1) cout<<'A';
                        }
                    }
                }
            }
            if(AI.cartiDealer[0].simbol==1) simbol=003;
            if(AI.cartiDealer[0].simbol==2) simbol=004;
            if(AI.cartiDealer[0].simbol==3) simbol=005;
            if(AI.cartiDealer[0].simbol==4) simbol=006;
            cout<<simbol<<"; ";
        }
        else
        {
            cout<<"?; ";
        }
        cout<<endl;
        cout<<"Total=?";
        cout<<endl;
    }
    for(j=0;j<numPlayers;j++)
    {
        cout<<Players1[j].user<<"'s cards:"<<endl;
        for(l=0;l<Players1[j].nrCarti;l++)
        {
            if(Players1[j].carti[l].numar>=2 && Players1[j].carti[l].numar<=10) cout<<Players1[j].carti[l].numar;
            else
            {
                if(Players1[j].carti[l].numar==11) cout<<'J';
                else
                {
                    if(Players1[j].carti[l].numar==12) cout<<'Q';
                    else
                    {
                        if(Players1[j].carti[l].numar==13) cout<<'K';
                        else
                        {
                            if(Players1[j].carti[l].numar==14 || Players1[j].carti[l].numar==1) cout<<'A';
                        }
                    }
                }
            }
            if(Players1[j].carti[l].simbol==1) simbol=003;
            if(Players1[j].carti[l].simbol==2) simbol=004;
            if(Players1[j].carti[l].simbol==3) simbol=005;
            if(Players1[j].carti[l].simbol==4) simbol=006;
            cout<<simbol<<"; ";
        }
        cout<<endl;
        cout<<"Total="<<Players1[j].suma<<endl;
    }

}


bool isSplit(player a)
{
    int i, j;
    for(i=0;i<a.nrCarti;i++)
        for(j=i+1;j<a.nrCarti;j++)
        {
            if(a.carti[i].numar==a.carti[j].numar) return true;
        }
    return false;
}
int main()
{
    ifstream dataIn("database.txt");
    bool play=true;
    int numberPlayers, l=0, j;
    int nr=0;
    database players[NR_JUCATORI];
    player Players1[7];
    dataIn>>numberPlayers;
    while(!dataIn.eof())
    {
        dataIn>>players[l].user;
        dataIn>>players[l].pass;
        dataIn>>players[l].earnings;
        dataIn>>players[l].handsWon;
        l++;
    }
    int i;
    carte deck[NR_CARTI];
    ifstream deckIn("deck.txt");
    for(i=0;i<52;i++)
    {
        deckIn>>deck[i].numar>>deck[i].simbol;
    }
    deckIn.close();
    dataIn.close();
    carte deckShuffled[NR_CARTI];
    shuffle(deck, deckShuffled);
    cout<<"BlackJack"<<endl;
    cout<<"Input anything to continue: ";
    string a;
    cin>>a;
    system("cls");
    Menu:
    cout<<"Menu"<<endl;
    cout<<"1) For Singleplayer, input 1."<<endl;
    cout<<"2) For Multiplayer, input 2."<<endl;
    cout<<"3) To view the Leaderboard, input 3."<<endl;
    cout<<"4) To quit the game, input 4."<<endl<<endl;
    cout<<"Your Answer:";
    int ans1;
    cin>>ans1;
    if(ans1!=1 && ans1!=2 && ans1!=3 && ans1!=4)
    {
        system("cls");
        cout<<"Error at input!"<<endl<<endl;
        goto Menu;
    }
    if(ans1==4) goto endGame;
    if(ans1==3)
    {
        leaderError:
        system("cls");
        int p=0;
        while(p<=10 && p<numberPlayers)
        {
            cout<<p+1<<") "<<players[p].user<<"   "<<players[p].earnings<<"   "<<players[p].handsWon<<endl;
            p++;
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
        Multi:
        cin>>numPlayers;
        if(numPlayers<2 || numPlayers>6)
        {
            system("cls");
            cout<<"Please enter a number between 2 and 6: ";
            goto Multi;
        }
    }
    Players1[numPlayers].user="stuff";
    Players1[numPlayers].pass="stuff";

    for(i=0;i<numPlayers;i++)
    {
        system("cls");
        loginOrRegister:
        cout<<"1) To login, enter 1."<<endl;
        cout<<"2) To register, enter 2."<<endl;
        cout<<"3) To go back to the menu, enter 3."<<endl<<endl;
        cout<<"Your answer: ";
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
                players[numberPlayers].user=Players1[i].user;
                players[numberPlayers].pass=Players1[i].pass;
                players[numberPlayers].earnings=0;
                players[numberPlayers].handsWon=0;
                numberPlayers++;
            }

        }
    }
    Players1[i].user="stuff";
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
    system("cls");
    while(play)
    {
        for(i=0;i<numPlayers;i++)
        {
            Players1[i].bust=false;
            Players1[i].stand=false;
            system("cls");
            notEnoughFunds:
            cout<<Players1[i].user<<",your current balance is "<<Players1[i].money<<". Please insert your bet (minimum of 10 and maximum of 100 in multiples of 5): ";
            bet:
            cin>>Players1[i].bet;
            cout<<endl;
            if(Players1[i].bet<10 || Players1[i].bet>100)
            {
                system("cls");
                cout<<"Please enter a value between 10 and 100 that is a multiple of 5: ";
                goto bet;
            }
            else
            {
                if(Players1[i].bet%5!=0)
                {
                    system("cls");
                    cout<<"Please enter a value that is a multiple of 5 and is between 10 and 100: ";
                    goto bet;
                }
                else
                {
                    if(Players1[i].bet>Players1[i].money)
                    {
                        system("cls");
                        cout<<"Not enough funds!";
                        goto notEnoughFunds;
                    }
                }
            }
        }
        startGame(AI,deck,deckShuffled,nr,Players1,numPlayers);
        system("cls");
        int insurance=0;
        string ins, stuff, answer;
        for(i=0;i<numPlayers;i++)
        {
            while(Players1[i].bust==false &&Players1[i].stand==false)
            {
                game:
                bool decision=false;
                showcards(AI,Players1,numPlayers,i);
                cout<<endl;
                cout<<Players1[i].user<<"'s turn:"<<endl;
                if(Players1[i].nrCarti==2)
                {
                    if(Players1[i].suma==21)
                    {
                        Players1[i].bet+=Players1[i].bet/2;
                        Players1[i].earnings+=Players1[i].bet;
                        Players1[i].money+=Players1[i].bet;
                        Players1[i].handsWon++;
                        cout<<"Blackjack! Enter anything to continue: ";
                        cin>>answer;
                        goto fin;
                    }
                }
                cout<<"1) For another card, enter HIT."<<endl;
                cout<<"2) To stay, enter STAND."<<endl;
                cout<<"3) To double down, enter DOUBLE."<<endl;
                cout<<"4) To surrender, enter SURRENDER."<<endl;
                int num=5, insBet;
                if((AI.cartiDealer[0].numar==1 || AI.cartiDealer[0].numar==14) && insurance==0)
                {
                    cout<<num<<") For insurance, enter INSURANCE."<<endl;
                    num++;
                }
                /*if(isSplit(Players1[i]))
                {
                    cout<<num<<") To split, enter SPLIT."<<endl;
                }*/
                cin>>answer;
                cout<<endl;
                if(answer=="HIT" || answer=="hit")
                {
                    decision=true;
                    hit(deck, deckShuffled, nr, Players1[i]);
                    if(Players1[i].bust)
                    {
                        Players1[i].earnings-=Players1[i].bet;
                        Players1[i].money-=Players1[i].bet;
                    }
                }
                if(answer=="STAND" || answer=="stand") {Players1[i].stand=true; decision=true;}
                if(answer=="SURRENDER" || answer=="surrender")
                {
                    decision=true;
                    Players1[i].bust=true;
                    Players1[i].earnings-=Players1[i].bet/2;
                    Players1[i].money-=Players1[i].bet/2;
                }
                if(answer=="DOUBLE" || answer=="double")
                {
                    decision=true;
                    hit(deck, deckShuffled, nr, Players1[i]);
                    Players1[i].bet*=2;
                    if(Players1[i].bust!=false) Players1[i].stand=true;
                    else
                    {
                        Players1[i].earnings-=Players1[i].bet;
                        Players1[i].money-=Players1[i].bet;
                    }
                }
                if(answer=="INSURANCE" || answer=="insurance")
                {
                    decision=true;
                    insBet=Players1[i].bet;
                    insurance=1;
                    if(AI.suma==21)
                    {
                        Players1[i].earnings+=2*insBet;
                        Players1[i].money+=2*insBet;
                        cout<<"You have won the insurance. Enter anything to continue: ";
                        cin>>ins;
                    }
                    else
                    {
                        Players1[i].earnings-=insBet;
                        cout<<"You have lost the insurance. Enter anything to continue: ";
                        cin>>ins;
                    }
                }
                if(answer=="SPLIT" || answer=="split")
                {
                    decision=true;

                }
                if(decision==false)
                {
                    system("cls");
                    cout<<"Error at input";
                    cout<<endl;
                    goto game;
                }
                system("cls");
            }
            showcards(AI,Players1,numPlayers,i);
            cout<<endl;
            if(Players1[i].bust==1) cout<<"You have lost!";
            fin:
            cout<<endl;
            cout<<"Enter anything to continue: ";
            cin>>stuff;
            system("cls");
            if(i+1==numPlayers)
            {
                cout<<"Dealer's turn. Enter anything to continue: ";
                cin>>stuff;
            }
            else
            {
                cout<<Players1[i+1].user<<"'s turn. Enter anything to continue: ";
                cin>>stuff;
            }
            system("cls");
        }
        AI.bust=false;
        while(AI.suma<17 && AI.bust==false)
        {
            AI.cartiDealer[AI.nrCarti]=deckShuffled[0];
            if(AI.cartiDealer[0].numar<=10) AI.suma=AI.suma+AI.cartiDealer[0].numar;
            else
            {
                if(AI.cartiDealer[0].numar>10 && AI.cartiDealer[0].numar<=13) AI.suma=AI.suma+10;
                else
                {
                    if(AI.cartiDealer[0].numar==14) AI.suma+=11;
                }
            }
            AI.nrCarti++;
            moveCard(deckShuffled, deck, nr);
            int gasit=1;
            while(AI.suma>21 && gasit==1)
            {
                gasit=0;
                for(l=0;l<AI.nrCarti;l++)
                    if(AI.cartiDealer[l].numar==14)
                    {
                        AI.cartiDealer[l].numar=1;
                        AI.suma=AI.suma-10;
                        gasit=1;
                        break;
                    }
            }
            if(AI.suma>21) AI.bust=true;
            dealerCards(AI, Players1,numPlayers,i);
            cout<<"Enter anything to continue: ";
            cin>>stuff;
            system("cls");
        }
        dealerCards(AI, Players1,numPlayers,i);
        cout<<"Winners: ";
        for(i=0;i<numPlayers;i++)
        {
            if(Players1[i].stand && Players1[i].bust==false)
            {
                if(AI.bust==false)
                {
                    if(Players1[i].suma>AI.suma)
                    {
                        cout<<Players1[i].user<<"; ";
                        Players1[i].money+=Players1[i].bet;
                        Players1[i].earnings+=Players1[i].bet;
                        Players1[i].handsWon++;
                    }
                    else
                    {
                        Players1[i].money-=Players1[i].bet;
                        Players1[i].earnings-=Players1[i].bet;
                    }
                }
                else
                {
                    if(Players1[i].bust==false)
                    {
                        cout<<Players1[i].user<<"; ";
                        Players1[i].money+=Players1[i].bet;
                        Players1[i].earnings+=Players1[i].bet;
                        Players1[i].handsWon++;
                    }
                }

            }
        }
        cout<<endl;
        cout<<"Enter anything to continue: ";
        cin>>stuff;
        system("cls");
        for(i=0;i<numPlayers;i++)
        {
            if(Players1[i].money==0)
            {
                cout<<Players1[i].user<<" has been eliminated due to lack of funds."<<endl;
                for(l=0;l<numberPlayers;i++)
                {
                    if(Players1[i].user==players[l].user)
                    {
                        players[l].earnings+=Players1[i].earnings;
                        players[l].handsWon+=Players1[i].handsWon;
                        break;
                    }
                }
                for(j=i;j<numPlayers;j++)
                {
                    Players1[j]=Players1[j+1];
                }
                numPlayers--;
                i--;
            }
        }
        for(i=0;i<numPlayers;i++)
        {
            cout<<Players1[i].user<<", if you want to quit, enter QUIT. Otherwise, enter anything else: ";
            cin>>stuff;
            if(stuff=="QUIT" || stuff=="quit")
            {
                for(l=0;l<numberPlayers;l++)
                {
                    if(Players1[i].user==players[l].user)
                    {
                        players[l].earnings+=Players1[i].earnings;
                        players[l].handsWon+=Players1[i].handsWon;
                        break;
                    }
                }
                for(j=i;j<numPlayers;j++)
                {
                    Players1[j]=Players1[j+1];
                }
                numPlayers--;
                i--;
            }
        }
        if(numPlayers<1) play=false;

    }
    system("cls");
    goto Menu;
    endGame:
    ofstream deckOut("deck.txt");
    ofstream dataOut("database.txt");
    database aux;
    for(i=0;i<numberPlayers;i++)
    {
        for(j=0;j<numberPlayers;j++)
        {
            if(players[i].earnings>players[j].earnings)
            {
                aux=players[i];
                players[i]=players[j];
                players[j]=aux;
            }
        }
    }
    dataOut<<numberPlayers<<endl;
    for(i=0;i<numberPlayers;i++)
        dataOut<<players[i].user<<"  "<<players[i].pass<<"  "<<players[i].earnings<<"  "<<players[i].handsWon<<endl;
    for(i=0;i<nr;i++)
        deckOut<<deck[i].numar<<"  "<<deck[i].simbol<<endl;
    for(i=0;i<NR_CARTI-nr;i++)
        deckOut<<deckShuffled[i].numar<<"  "<<deckShuffled[i].simbol<<endl;
    deckOut.close();
    dataOut.close();
    return 0;

}
