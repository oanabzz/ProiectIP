#include <iostream>
#include <stdlib.h>
#include <string.h>
#include<conio.h>
#define _WIN32_WINNT 0x0500
#include<windows.h>
#include<random>
#include <time.h>
#include<math.h>
#include <cwchar>
#include <fstream>
#include <string>


#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77


using namespace std;
int correctness;
int sizex,sizey;
int pozi=1, pozj=1;
int selectPozi,selectPozj;
int noOfBombs;
bool keepGoing=1;
bool firstMove=1;
char mat[1000][1000];
int trueMap[1000][1000];
int matAUX[1000][1000];
int dl[]={-1,0,1,0,-1,1,1,-1};
int dc[]={0,1,0,-1,1,1,-1,-1};
int seconds=0;
char secondMatrix[1000][1000];
int secondMap[1000][1000];
int AUXmatrix[1000][1000];
int currentLine=1;
bool infinity=0;
int levelSeconds[]={10,10,10,10,10,10,5,5,5,5,5,5,3,3,3,3,3,3,2,2,2,2,2,2,1};
int rowsCleared;
int level;


void select();
void bomb();
void createInfiniteMatrixButNotReally(int v[1000]);
void printMatrix();
bool verifyClearedRow();
void arrowsClassicMode();
void arrows();
void arrowsMenu();
void resetValues()
{
    seconds=0;
    keepGoing=1;
    firstMove=1;
    correctness=0;
    for(int i=0;i<=100;i++)
        for(int j=0;j<=100;j++)
    {
        trueMap[i][j]=0;
        matAUX[i][j]=0;
    }
    infinity=0;
    rowsCleared=0;
}
void setConsoleSize(int lines, int columns)
{
    HWND console = GetConsoleWindow();
    RECT r;
    GetWindowRect(console,&r);
    if(lines==1&&columns==1)
        MoveWindow(console,r.left,r.top,280,300,TRUE);
    else if(lines==10&&columns==10)
        MoveWindow(console,r.left,r.top,350,350,TRUE);
    else
        if(lines==16&&columns==16)
            MoveWindow(console,r.left,r.top,450,450,TRUE);
        else
            if(lines==16&&columns==30)
            MoveWindow(console,r.left,r.top,680,450,TRUE);
            else
                MoveWindow(console,r.left,r.top,columns*16.5+185,lines*16.5+185,TRUE);

}
void printFirstMessage(int index)
{
    setConsoleSize(1,1);


    HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 12);
    cout<<endl<<endl;
    cout<<"\t MINESWEEPER"<<endl<<endl<<endl;
    SetConsoleTextAttribute(hConsole, 15);
    cout<<"\t  Game Mode:   "<<endl;
    if(index==1)
    {
        SetConsoleTextAttribute(hConsole, 11);
        cout<<"\t   Classic   "<<endl;
        SetConsoleTextAttribute(hConsole, 15);
        cout<<"\t   Infinite   "<<endl;
        cout<<"\t     Exit";
    }
    if(index==2)
    {
        cout<<"\t   Classic   "<<endl;
        SetConsoleTextAttribute(hConsole, 11);
        cout<<"\t   Infinite   "<<endl;
        SetConsoleTextAttribute(hConsole, 15);
        cout<<"\t     Exit";
    }
    if(index==3)
    {
        cout<<"\t   Classic   "<<endl;
        cout<<"\t   Infinite   "<<endl;
        SetConsoleTextAttribute(hConsole, 11);
        cout<<"\t     Exit";
        SetConsoleTextAttribute(hConsole, 15);
    }
}



void areYouSure(int option)
{
    int answer;
    if(option==1)//classic mode
    {

        arrowsClassicMode();
    }
}

void endGame(int c)
{
    HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 15);
    keepGoing=0;
    system("cls");
    if(c==0)
    {
        cout<<endl<<endl<<endl;
    cout<<"\t";
    cout<<"sec: "<<seconds;
    if(seconds<10)
        cout<<' ';
    for(int i=1;i<=2*sizey-9;i++)
        cout<<' ';
    cout<<"*: "<<noOfBombs;
    cout<<endl;
    cout<<"\t"<<(char)201;
    for(int i=1;i<=sizey*2+1;i++)
        cout<<(char)205;
    cout<<(char)187;
    cout<<endl;
        for(int i=1;i<=sizex;i++)
            {
                cout<<"\t"<<(char)186<<' ';
                for(int j=1;j<=sizey;j++)
                {
                    if(trueMap[i][j]==-1&&mat[i][j]==-31)//bomba pusa corect
                    {
                        SetConsoleTextAttribute(hConsole, 11);
                        cout<<mat[i][j]<<' ';
                        SetConsoleTextAttribute(hConsole,15);
                    }
                    else if(trueMap[i][j]==-1&&mat[i][j]!=-31)//bomba nu a fost pusa
                    {
                        SetConsoleTextAttribute(hConsole,12);
                        cout<<(char)-31;
                        SetConsoleTextAttribute(hConsole,15);
                        cout<<' ';
                    }
                    else if(trueMap[i][j]!=-1&&mat[i][j]==-31)//bomba pusa gresit
                    {
                        SetConsoleTextAttribute(hConsole,207);
                        cout<<"X";
                        SetConsoleTextAttribute(hConsole,15);
                        cout<<' ';
                    }
                    else cout<<mat[i][j]<<' ';
                }
                cout<<(char)186;
                cout<<endl;
            }
            cout<<"\t"<<(char)200;
    for(int i=1;i<=sizey*2+1;i++)
        cout<<(char)205;
    cout<<(char)188;
    cout<<endl<<endl<<endl;
    Sleep(2000);
    system("cls");
    setConsoleSize(10,10);
    cout<<endl<<endl<<endl<<endl<<endl<<endl;
    cout<<"\t       You lost"<<endl;
    cout<<"         Press Esc to close or"<<endl;
    cout<<"     Enter to go to the Main Menu";
    char c;
    while(1)
    {
        c=getch();
        if(c==13)
        {
        system("cls");
        arrowsMenu();

        }
        if(c==27)
            return;
    }
    }
    if(c==1)
    {
        system("cls");
        printMatrix();
        Sleep(1500);
        system("cls");
        setConsoleSize(10,10);
        for(int i=1;i<=14;i++)
        {
            system("cls");
            SetConsoleTextAttribute(hConsole,i);
            cout<<endl<<endl<<endl<<endl<<endl<<endl;
            cout<<"              You Win";
            Sleep(200);
        }
        SetConsoleTextAttribute(hConsole,15);
        cout<<endl;

            cout<<"        Press Esc to Exit or "    <<endl;
            cout<<"    Enter to go to the Main Menu";
        char c;
        while(1)
        {
            c=getch();
            if(c==13)
            {
            system("cls");
            arrowsMenu();

            }
            if(c==27)
                return;
    }
    }

}
void createMatrix()
{
    for(int i=1;i<=sizex;i++)
        for(int j=1;j<=sizey;j++)
            mat[i][j]=254;
    mat[1][1]=254;
}
void printMatrix()
{
    HANDLE  hConsole;

    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    system("cls");
    SetConsoleTextAttribute(hConsole, 15);
    cout<<endl<<endl<<endl;
    cout<<"\t";
    cout<<"sec: "<<seconds;
    if(seconds<10)
        cout<<' ';
    for(int i=1;i<=2*sizey-9;i++)
        cout<<' ';
    cout<<"*: "<<noOfBombs;
    cout<<endl;
    cout<<"\t"<<(char)201;
    for(int i=1;i<=sizey*2+1;i++)
        cout<<(char)205;
    cout<<(char)187;
    cout<<endl;
    for(int i=1;i<=sizex;i++)
    {
        cout<<"\t"<<(char)186<<' ';
        for(int j=1;j<=sizey;j++)
            {if(mat[i][j]==-31)
                SetConsoleTextAttribute(hConsole,11);
            else
                SetConsoleTextAttribute(hConsole,15);
            if(i==pozi&&j==pozj)
                if(mat[i][j]!=0)
            {
                SetConsoleTextAttribute(hConsole, 12);
                cout<<mat[i][j]<<' ';
                SetConsoleTextAttribute(hConsole, 15);
            }
            else
            {
                char aux=248;
                SetConsoleTextAttribute(hConsole, 12);
                cout<<aux<<' ';
                SetConsoleTextAttribute(hConsole, 15);
            }
            else {

                    cout<<mat[i][j]<<' ';
            }
            }
        cout<<(char)186;
        cout<<endl;
    }
    cout<<"\t"<<(char)200;
    for(int i=1;i<=sizey*2+1;i++)
        cout<<(char)205;
    cout<<(char)188;
    cout<<endl<<endl<<endl;

}

int sum (int i, int j)
{
    int suma=0;
    for(int k=0;k<8;k++)
        if(trueMap[i+dl[k]][j+dc[k]]<0)
            suma++;
    return suma;
}
void generateMatrixFirst (int i, int j)
{
    trueMap[i][j]=1;
    srand(time(NULL));
    int countBombs=0;
    int x,y;
    int randomPos=(rand()%10)/2;
    while(countBombs<noOfBombs)
    {
        x=rand()%sizex+1;
        y=rand()%sizey+1;
        if(trueMap[x][y]==0&&(abs(x-i)>2||abs(y-j)>2))
            { trueMap[x][y]=-1; countBombs++;}
    }
    trueMap[i][j]=0;
    for(int l=1;l<=sizex;l++)
        for(int c=1;c<=sizey;c++)
            if(trueMap[l][c]==0)
            trueMap[l][c]=sum(l,c);

}
void transformPrintingMat(int i, int j)
{
    if(i>=1&&i<=sizex&&j>=1&&j<=sizey&&matAUX[i][j]==0)
    {
        if(trueMap[i][j]==0)
        {
            mat[i][j]=0;
            matAUX[i][j]=1;
            for(int k=0;k<8;k++)
        if(trueMap[i+dl[k]][j+dc[k]]>=0)
            transformPrintingMat(i+dl[k],j+dc[k]);
        }
    else
        {
            mat[i][j]='0'+trueMap[i][j];
            matAUX[i][j]=1;
        }

    }
}

void generateTheAuxiliarMatrix()
{
    for(int i=1;i<=10;i++)
        for(int j=1;j<=10;j++)
        AUXmatrix[i][j]=0;
    srand(time(NULL));
    int countBombs=0;
    int x,y;
    while(countBombs<10)
    {
        x=rand()%9+2;//fara primul rand
        y=rand()%10+1;
        if(AUXmatrix[x][y]==0)
            {
                AUXmatrix[x][y]=-1;
                countBombs++;
            }
    }
    for(int j=1;j<=10;j++)
        {
            if(trueMap[20][j-1]==-1) AUXmatrix[1][j]++;
            if(trueMap[20][j]==-1)  AUXmatrix[1][j]++;
            if(trueMap[20][j+1]==-1) AUXmatrix[1][j]++;
            if(AUXmatrix[2][j-1]==-1) AUXmatrix[1][j]++;
            if(AUXmatrix[2][j]==-1) AUXmatrix[1][j]++;
            if(AUXmatrix[2][j+1]==-1) AUXmatrix[1][j]++;
        }
    for(int l=1;l<=10;l++)
        for(int c=1;c<=10;c++)
            if(AUXmatrix[l][c]==0)
            {
                if(AUXmatrix[l-1][c-1]==-1) AUXmatrix[l][c]++;
                if(AUXmatrix[l-1][c]==-1) AUXmatrix[l][c]++;
                if(AUXmatrix[l-1][c+1]==-1) AUXmatrix[l][c]++;
                if(AUXmatrix[l][c-1]==-1) AUXmatrix[l][c]++;
                if(AUXmatrix[l][c+1]==-1) AUXmatrix[l][c]++;
                if(AUXmatrix[l+1][c-1]==-1) AUXmatrix[l][c]++;
                if(AUXmatrix[l+1][c]==-1) AUXmatrix[l][c]++;
                if(AUXmatrix[l+1][c+1]==-1) AUXmatrix[l][c]++;
            }
}
void copyMapMatrix()
{
    for(int i=1;i<=10;i++)
        for(int j=1;j<=10;j++)
        trueMap[i][j]=trueMap[i+10][j];
    for(int i=11;i<=20;i++)
        for(int j=1;j<=10;j++)
        trueMap[i][j]=AUXmatrix[i-10][j];
}
void createInfiniteMatrixButNotReally()
{
    //i m gonna leave this here cause it s funny
    //it's not really funny
    //i'm not really funny
    //but everything iz oke
    //i'm fien :)
    sizex=10;
    sizey=20;
    createMatrix();

}
void transformInfiniteMatrix()
{
    for(int i=1;i<=10;i++)
        for(int j=1;j<=10;j++)
        mat[i][j]=mat[i+10][j];
    for(int i=11;i<=20;i++)
        for(int j=1;j<=10;j++)
        mat[i][j]=254;
}
void printInfiniteMatrix()
{
    setConsoleSize(10,10);
    HANDLE  hConsole;

    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    system("cls");
    SetConsoleTextAttribute(hConsole, 15);
    cout<<endl;
    cout<<"\t Time: "<<seconds<<"      Level: "<<level+1<<endl;
    cout<<"\t     Sec/Level: ";
    if(level<24)
        cout<<levelSeconds[level];
    else cout<<"1";
    cout<<endl;
    cout<<"\t"<<(char)201;
    for(int i=1;i<=21;i++)
        cout<<(char)205;
    cout<<(char)187;
    cout<<endl;
    for(int i=currentLine;i<=currentLine+10;i++)
    {
        cout<<"\t"<<(char)186<<' ';
        for(int j=1;j<=10;j++)
            {if(mat[i][j]==-31)
                SetConsoleTextAttribute(hConsole,11);
            else
                SetConsoleTextAttribute(hConsole,15);
            if(i==pozi&&j==pozj)
                if(mat[i][j]!=0)
            {
                SetConsoleTextAttribute(hConsole, 12);
                cout<<mat[i][j]<<' ';
                SetConsoleTextAttribute(hConsole, 15);
            }
            else
            {
                char aux=248;
                SetConsoleTextAttribute(hConsole, 12);
                cout<<aux<<' ';
                SetConsoleTextAttribute(hConsole, 15);
            }
            else {
                    cout<<mat[i][j]<<' ';
            }
            }
        cout<<(char)186;
        cout<<endl;
    }
    cout<<"\t"<<(char)200;
    for(int i=1;i<=21;i++)
        cout<<(char)205;
    cout<<(char)188;
    cout<<endl<<endl;
}


bool verifyClearedRow()
{
    for(int j=1;j<=10;j++)
        if(trueMap[currentLine][j]==0&&mat[currentLine][j]!=0)
            return 0;
        else if(trueMap[currentLine][j]>0&&mat[currentLine][j]!='0'+trueMap[currentLine][j])
            return 0;
    return 1;
}
void endInfiniteGame()
{
    keepGoing=0;
    system("cls");
    setConsoleSize(10,10);
    HANDLE  hConsole;

    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    system("cls");
    SetConsoleTextAttribute(hConsole, 15);
    cout<<endl<<endl<<endl;
    cout<<"\t"<<(char)201;
    for(int i=1;i<=21;i++)
        cout<<(char)205;
    cout<<(char)187;
    cout<<endl;
    int aux=0;
    if(verifyClearedRow()==0)
        {
            aux++;
            cout<<"\t"<<(char)186<<' ';
            SetConsoleTextAttribute(hConsole,207);
            for(int j=1;j<=10;j++)
                if(trueMap[currentLine][j]==-1)
                    cout<<(char)-31<<' ';
            else
                if(trueMap[currentLine][j]==0)
                cout<<"  ";
            else
                cout<<trueMap[currentLine][j]<<' ';
            SetConsoleTextAttribute(hConsole,15);
            cout<<(char)186;
            cout<<endl;
        }
    for(int i=currentLine+aux;i<=currentLine+10;i++)
    {
        cout<<"\t"<<(char)186<<' ';
        for(int j=1;j<=10;j++)
                {
                    if(trueMap[i][j]==-1&&mat[i][j]==-31)//bomba pusa corect
                    {
                        SetConsoleTextAttribute(hConsole, 11);
                        cout<<mat[i][j]<<' ';
                        SetConsoleTextAttribute(hConsole,15);
                    }
                    else if(trueMap[i][j]==-1&&mat[i][j]!=-31)//bomba nu a fost pusa
                    {
                        SetConsoleTextAttribute(hConsole,12);
                        cout<<(char)-31;
                        SetConsoleTextAttribute(hConsole,15);
                        cout<<' ';
                    }
                    else if(trueMap[i][j]!=-1&&mat[i][j]==-31)//bomba pusa gresit
                    {
                        SetConsoleTextAttribute(hConsole,207);
                        cout<<"X";
                        SetConsoleTextAttribute(hConsole,15);
                        cout<<' ';
                    }
                    else cout<<mat[i][j]<<' ';
                }
        cout<<(char)186;
        cout<<endl;
    }
    cout<<"\t"<<(char)200;
    for(int i=1;i<=21;i++)
        cout<<(char)205;
    cout<<(char)188;
    cout<<endl<<endl;
    cout<<"      You couldn't reach infinity"<<endl;
    cout<<"              Shame on you";
    Sleep(2000);
    system("cls");
    cout<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl;

    cout<<"\t That means you lost";
      cout<<endl<<endl<<endl<<endl<<endl<<endl<<endl;
    Sleep(2000);
    system("cls");
    cout<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl;

    cout<<"\t That means you lost"<<endl;
    cout<<"    Press Esc to close and cry or"<<endl;
    cout<<"   Enter to go to the Main Menu and"<<endl;
    cout<<"              try again";
    char c;
    c=getch();
    if(c==13)
    {
        system("cls");
        arrowsMenu();
    }
    if(c==27)
        return;
}




void arrowsInfinite()
{
    char aux;
    bool isItTime=0;
    int c = 0;
    clock_t start = clock();
    while(keepGoing)
    {
        c = 0;
        if(correctness==0&&noOfBombs==0)
        {
            endGame(1);
            return;
        }
        while(! _kbhit())
            {
                if(((clock()-start)/CLOCKS_PER_SEC)!=seconds)
            {
                isItTime=1;
                seconds++;
                printInfiniteMatrix();
            }
            int noOfSeconds;
            if(level>=24)
                noOfSeconds=1;
            else noOfSeconds=levelSeconds[level];
                if(seconds%noOfSeconds==0&&seconds&&isItTime)
                {
                    if(verifyClearedRow()==0)
                    {
                        endInfiniteGame();
                        return;
                    }
                    isItTime=0;
                    level++;
                    if(currentLine==10)
                    {
                        generateTheAuxiliarMatrix();
                        copyMapMatrix();
                        transformInfiniteMatrix();
                        currentLine=1;
                        printInfiniteMatrix();
                    }
                    else currentLine++;
                }
            }
        switch((c=getch())) {
        case KEY_UP:
            {
                if(pozi>1+currentLine-1)
                {
                pozi--;
                printInfiniteMatrix();}
            }
            break;
        case KEY_DOWN:
            {
                if(pozi<10+currentLine)
                {
                pozi++;
                printInfiniteMatrix();}
            }
            break;
        case KEY_LEFT:
            {
                if(pozj>1)
                {
                pozj--;
                printInfiniteMatrix();}
            }
            break;
        case KEY_RIGHT:
            {
                if(pozj<10)
                {
                pozj++;
                printInfiniteMatrix();}
            }
            break;
        case 27:
            {
                endGame(0);
                return;
            }
            break;
        case 99:
            {

                select();
                if(keepGoing)
                    printInfiniteMatrix();
            }
            break;
        case 98:
            {
                bomb();
            }
            break;
        }

    }
}




void infiniteMode()
{
    infinity=1;
    sizex=20;
    sizey=10;
    noOfBombs=20;
    createMatrix();
    arrowsInfinite();
}

void select()
{
    if(firstMove)
    {
        firstMove=0;
        generateMatrixFirst(pozi,pozj);
        transformPrintingMat(pozi,pozj);
    }
    if(trueMap[pozi][pozj]==-1)//square
       {
           if(infinity)
                endInfiniteGame();
           else endGame(0);
       }

    if(trueMap[pozi][pozj]>=0&&mat[pozi][pozj]!=225)//bomb
        transformPrintingMat(pozi,pozj);
}
void bomb()
{
    if(mat[pozi][pozj]==-2)//pune bomba
        {
            int aux;
            if(trueMap[pozi][pozj]!=-1)
                aux=1;
            else aux=0;
            mat[pozi][pozj]=225;
            system("cls");
            if(infinity)
                printInfiniteMatrix();
            else
                printMatrix();
            noOfBombs--;
            if(trueMap[pozi][pozj]!=-1&&aux)
                correctness--;
        }
    else
        if(mat[pozi][pozj]==-31)//scoate bomba
        {
            int aux;
            if(trueMap[pozi][pozj]!=-1)
                aux=1;
            else aux=0;
            mat[pozi][pozj]=254;
            system("cls");
            if(infinity)
                printInfiniteMatrix();
            else
                printMatrix();
            noOfBombs++;
            if(trueMap[pozi][pozj]!=-1&&aux)

                correctness++;
        }

}
void arrows()
{
    char input;
char aux;
int c = 0;
clock_t start = clock();
    while(keepGoing)
    {
        c = 0;
        if(correctness==0&&noOfBombs==0)
        {
            endGame(1);
            return;
        }
        while(! _kbhit())
            if(((clock()-start)/CLOCKS_PER_SEC)!=seconds)
            {
                seconds++;
                printMatrix();
            }
        switch((c=getch())) {
        case KEY_UP:
            {
                if(pozi>1)
                {
                pozi--;
                printMatrix();}
            }
            break;
        case KEY_DOWN:
            {
                if(pozi<sizex)
                {
                pozi++;
                printMatrix();}
            }
            break;
        case KEY_LEFT:
            {
                if(pozj>1)
                {
                pozj--;
                printMatrix();}
            }
            break;
        case KEY_RIGHT:
            {
                if(pozj<sizey)
                {
                pozj++;
                printMatrix();}
            }
            break;
        case 27:cout<<"\t That means you lost"<<endl;
    cout<<"    Press Esc to close and cry or"<<endl;
    cout<<"   Enter to go to the Main Menu and"<<endl;
    cout<<"              try again";
    char c;
    c=getch();
    if(c==13)
    {
        system("cls");
        arrowsMenu();
    }
    if(c==27)
        return;
            {
                system("cls");
                areYouSure(1);
                return;
            }
            break;
        case 99:
            {

                select();
                if(keepGoing)
                    printMatrix();
            }
            break;
        case 98:
            {
                bomb();
            }
            break;
        }

    }
}


void classicMode(int index);
void arrowsClassicMode();
void arrowsMenu()
{
    printFirstMessage(1);
    resetValues();
    char c=0;
    int index=1;
    while(1)
    {

        switch((c=getch())) {
        case KEY_UP:
            {
                if(index==1)
                    index=4;
                system("cls");
                index--;
                printFirstMessage(index);
            }
            break;
        case KEY_DOWN:
            {
                if(index==3)
                    index=0;
                system("cls");
                index++;
                printFirstMessage(index);
            }
            break;
        case 13:
            {
                if(index==1)
                {
                    system("cls");
                    arrowsClassicMode();
                }
                if(index==2)
                {
                    system("cls");
                    infiniteMode();
                }
                if(index==3)
                    return;
                return;
            }
            break;




    }
}
}

void classicMode(int index)
{
    setConsoleSize(1,1);


    HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 12);
    cout<<endl<<endl;
    cout<<"\t MINESWEEPER"<<endl<<endl<<endl;
    SetConsoleTextAttribute(hConsole, 15);
    cout<<"\t Classic Mode   "<<endl;
    if(index==1)
    {
        cout<<endl;
        SetConsoleTextAttribute(hConsole, 11);
        cout<<"\t    Small   "<<endl;
        SetConsoleTextAttribute(hConsole, 15);
        cout<<"\t    Medium   "<<endl;
        cout<<"\t    Large    "<<endl;
        cout<<"\t    Custom"<<endl;
    }
    if(index==2)
    {
        cout<<endl;
        cout<<"\t    Small   "<<endl;
        SetConsoleTextAttribute(hConsole, 11);
        cout<<"\t    Medium   "<<endl;
        SetConsoleTextAttribute(hConsole, 15);
        cout<<"\t    Large    "<<endl;
        cout<<"\t    Custom"<<endl;
    }
    if(index==3)
    {
        cout<<endl;
        cout<<"\t    Small   "<<endl;
        cout<<"\t    Medium   "<<endl;
        SetConsoleTextAttribute(hConsole, 11);
        cout<<"\t    Large    "<<endl;
        SetConsoleTextAttribute(hConsole, 15);
        cout<<"\t    Custom"<<endl;
    }
    if(index==4)
    {
        cout<<endl;
        cout<<"\t    Small   "<<endl;
        cout<<"\t    Medium   "<<endl;
        cout<<"\t    Large    "<<endl;
        SetConsoleTextAttribute(hConsole, 11);
        cout<<"\t    Custom"<<endl;
        SetConsoleTextAttribute(hConsole, 15);
    }
}
bool verifyInput(char input[100])
{
    for(int i=0;i<strlen(input);i++)
        if(input[i]<'0'||input[i]>'9')
            return false;
    return true;
}
int stringToInt(char input[100])
{
    int rez=0;
    for(int i=0;i<strlen(input);i++)
        rez=input[i]-'0' + rez*10;
    return rez;
}
void arrowsClassicMode()
{
    classicMode(1);
    char c=0;
    int index=1;
    while(1)
    {

        switch((c=getch())) {
        case KEY_UP:
            {
                if(index==1)
                    index=5;
                system("cls");
                index--;
                classicMode(index);
            }
            break;
        case KEY_DOWN:
            {
                if(index==4)
                    index=0;
                system("cls");
                index++;
                classicMode(index);
            }
            break;
        case 27:
            {
                system("cls");
                arrowsMenu();
            }
        case 13:
            {
                if(index==1)
                {
                    sizex=10;
                    sizey=10;
                    noOfBombs=10;
                    resetValues();
                    setConsoleSize(10,10);
                }
                if(index==2)
                {
                    sizex=16;
                    sizey=16;
                    noOfBombs=40;
                    resetValues();
                    setConsoleSize(16,16);
                }
                if(index==3)
                {
                    sizex=16;
                    sizey=30;
                    noOfBombs=99;
                    resetValues();
                    setConsoleSize(16,30);
                }
                if(index==4)
                {
                    char input[100];
                    system("cls");
                    cout<<"Number of lines: ";
                    cin>>input;
                    while(verifyInput(input)==0)
                    {
                        system("cls");
                        cout<<"Number of lines: ";
                        cin>>input;
                    }
                    sizex=stringToInt(input);
                    cout<<"Number of columns: "<<endl;
                    cin>>input;
                    while(verifyInput(input)==0)
                    {
                        system("cls");
                        cout<<"Number of columns: ";
                        cin>>input;
                    }
                    sizey=stringToInt(input);
                    cout<<"Number of BOMBS: "<<endl;
                    cin>>noOfBombs;
                    while(verifyInput(input)==0)
                    {
                        system("cls");
                        cout<<"Number of columns: ";
                        cin>>input;
                    }
                    noOfBombs=stringToInt(input);
                    resetValues();
                    setConsoleSize(sizex,sizey);
                }
                createMatrix();
                printMatrix();
                arrows();
                return;
            }
            break;
}
    }
}
int main()
{

    setConsoleSize(10,10);
    arrowsMenu();


    return 0;
}
