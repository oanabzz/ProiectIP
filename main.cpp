#include <iostream>
#include <stdlib.h>
#include<string.h>
#include<conio.h>
#define _WIN32_WINNT 0x0500
#include<windows.h>
#include<random>
#include <time.h>
#include<math.h>
#include <cwchar>
#include <fstream>


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


void select();
void bomb();
void createInfiniteMatrixButNotReally(int v[1000]);
void printMatrix();
bool verifyClearedRow();
void arrowsClassicMode();
void arrows();
void resetValues()
{
    seconds=0;
    keepGoing=1;
    firstMove=1;
    //pozi=pozj=1;
    correctness=0;
    for(int i=0;i<=100;i++)
        for(int j=0;j<=100;j++)
    {
        trueMap[i][j]=0;
        matAUX[i][j]=0;
    }
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
        cout<<"\t  Competitive";
    }
    if(index==2)
    {
        cout<<"\t   Classic   "<<endl;
        SetConsoleTextAttribute(hConsole, 11);
        cout<<"\t   Infinite   "<<endl;
        SetConsoleTextAttribute(hConsole, 15);
        cout<<"\t  Competitive";
    }
    if(index==3)
    {
        cout<<"\t   Classic   "<<endl;
        cout<<"\t   Infinite   "<<endl;
        SetConsoleTextAttribute(hConsole, 11);
        cout<<"\t  Competitive";
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
    }
    if(c==1)
    {
        system("cls");
        printMatrix();
        Sleep(200);
        system("cls");
        cout<<"You Win";
    }
    /*if(c==27)
        areYouSure();
    if(noOfBombs==0&&correctness)
        return 1;
    if(trueMap[selectPozi][selectPozj]==-1)
        return -1;
    return 0;*/

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
    //cout<<randomPos<<endl;
    while(countBombs<noOfBombs)
    {
        x=rand()%sizex+1;
        y=rand()%sizey+1;
        //cout<<x<<' '<<y<<endl<<endl;
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
    //generateMatrixFirst();

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
    cout<<endl<<endl<<endl;
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
                    //SetConsoleTextAttribute(hConsole, 15);
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
    cout<<endl<<endl<<endl;
    cout<<seconds<<' '<<verifyClearedRow();
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
    system("cls");
    cout<<"Infinite Loss";
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
                if(seconds%10==0&&seconds&&isItTime)
                {
                    if(verifyClearedRow()==0)
                    {
                        endInfiniteGame();
                        return;
                    }
                    isItTime=0;
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
                {//mat[pozi][pozj]=167;
                pozi--;
                //mat[pozi][pozj]=254;
                printInfiniteMatrix();}
            }
            break;
        case KEY_DOWN:
            {
                if(pozi<10+currentLine)
                {//mat[pozi][pozj]=167;
                pozi++;
                //mat[pozi][pozj]=254;
                printInfiniteMatrix();}
            }
            break;
        case KEY_LEFT:
            {
                if(pozj>1)
                {//mat[pozi][pozj]=167;
                pozj--;
                //mat[pozi][pozj]=254;
                printInfiniteMatrix();}
            }
            break;
        case KEY_RIGHT:
            {
                if(pozj<10)
                {//mat[pozi][pozj]=167;
                pozj++;
                //mat[pozi][pozj]=254;
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
        //cout<<"trolololo";
        endGame(0);
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
    //input=getch();
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
                {//mat[pozi][pozj]=167;
                pozi--;
                //mat[pozi][pozj]=254;
                printMatrix();}
            }
            break;
        case KEY_DOWN:
            {
                if(pozi<sizex)
                {//mat[pozi][pozj]=167;
                pozi++;
                //mat[pozi][pozj]=254;
                printMatrix();}
            }
            break;
        case KEY_LEFT:
            {
                if(pozj>1)
                {//mat[pozi][pozj]=167;
                pozj--;
                //mat[pozi][pozj]=254;
                printMatrix();}
            }
            break;
        case KEY_RIGHT:
            {
                if(pozj<sizey)
                {//mat[pozi][pozj]=167;
                pozj++;
                //mat[pozi][pozj]=254;
                printMatrix();}
            }
            break;
        case 27:
            {
                system("cls");
                areYouSure(1);
                //arrowsClassicMode();
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
    char c=0;
    //c=getch();
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
void arrowsClassicMode()
{
    classicMode(1);
    char c=0;
    //c=getch();
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
                    system("cls");
                    cout<<"Number of lines: "<<endl;
                    cin>>sizex;
                    cout<<"Number of columns: "<<endl;
                    cin>>sizey;
                    cout<<"Number of BOMBS: "<<endl;
                    cin>>noOfBombs;
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
    //beginGame();
    //arrows();
    //createMatrix();
    //printMatrix();
    //arrows();
    int pos1,pos2;
    //cin>>pos1>>pos2;
    //trueMap[2][3]=1;
    //generateMatrixFirst(2,3);

    //transformPrintingMat(1,1);
    //mat[1][1]=225;
    //printMatrix();
    //arrows();


    setConsoleSize(10,10);
    arrowsMenu();

    //sizex=20;
    //sizey=10;
    //noOfBombs=20;
    //createMatrix();
    //generateMatrixFirst(2,3);
    //generateTheAuxiliarMatrix();
    /*for(int i=1;i<=20;i++)
        {
            cout<<i<<": ";
            for(int j=1;j<=10;j++)
                cout<<trueMap[i][j]<<' ';
            cout<<endl;
        }
        cout<<endl;
    for(int i=1;i<=10;i++)
        {
            cout<<i<<": ";
            for(int j=1;j<=10;j++)
                cout<<AUXmatrix[i][j]<<' ';
            cout<<endl;
        }
    cout<<endl<<endl;
    copyMapMatrix();
    for(int i=1;i<=20;i++)
    {
        cout<<i<<": ";
        for(int j=1;j<=10;j++)
            cout<<trueMap[i][j]<<' ';
        cout<<endl;
    }*/
    //printInfiniteMatrix();
    //arrowsInfinite();
    return 0;
}
