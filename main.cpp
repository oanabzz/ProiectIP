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



#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77


using namespace std;
int correctness;
int sizex,sizey;
int pozi=1, pozj=1;
int selectPozi,selectPozj;
int noOfBombs=10;
bool keepGoing=1;
bool firstMove=1;
char mat[1000][1000];
int trueMap[1000][1000];
int matAUX[1000][1000];
int dl[]={-1,0,1,0,-1,1,1,-1};
int dc[]={0,1,0,-1,1,1,-1,-1};

void printFirstMessage(int index)
{
    HWND console = GetConsoleWindow();
    RECT r;
    GetWindowRect(console,&r);
    MoveWindow(console,r.left,r.top,280,300,TRUE);


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



void areYouSure()
{
    //cout are u sure
}
void endGame(int c)
{
    keepGoing=0;
    system("cls");
    cout<<"wtf";
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
    for(int i=1;i<=10;i++)
        for(int j=1;j<=10;j++)
            mat[i][j]=254;
    mat[1][1]=254;
}
void printMatrix()
{
    HANDLE  hConsole;

    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    system("cls");
    SetConsoleTextAttribute(hConsole, 15);
    for(int i=1;i<=10;i++)
    {
        for(int j=1;j<=10;j++)
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

            else cout<<mat[i][j]<<' ';
        cout<<endl;
    }
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
        x=rand()%10+1;
        y=rand()%10+1;
        //cout<<x<<' '<<y<<endl<<endl;
        if(trueMap[x][y]==0&&(abs(x-i)>2||abs(y-j)>2))
            { trueMap[x][y]=-1; countBombs++;}
    }
    trueMap[i][j]=0;
    for(int l=1;l<=10;l++)
        for(int c=1;c<=10;c++)
            if(trueMap[l][c]==0)
            trueMap[l][c]=sum(l,c);

}
void transformPrintingMat(int i, int j)
{
    if(i>=1&&i<=10&&j>=1&&j<=10&&matAUX[i][j]==0)
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
            mat[pozi][pozj]=225;
            system("cls");
            printMatrix();
            noOfBombs--;
            if(trueMap[pozi][pozj]!=-1)
                correctness--;
        }
    else
        if(mat[pozi][pozj]==-31)//scoate bomba
        {
            mat[pozi][pozj]=254;
            system("cls");
            printMatrix();
            noOfBombs++;
            if(trueMap[pozi][pozj]==-1)
                correctness++;
        }

}
void arrows()
{
    char input;
    //input=getch();
char aux;
int c = 0;
    while(keepGoing)
    {
        c = 0;
        if(correctness==0&&noOfBombs==0)
        {
            cout<<"You Win";
            return;
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
                if(pozi<10)
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
                if(pozj<10)
                {//mat[pozi][pozj]=167;
                pozj++;
                //mat[pozi][pozj]=254;
                printMatrix();}
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
    c=getch();
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
                return;
            }
            break;




    }
}
}

void classicMode(int index)
{
    HWND console = GetConsoleWindow();
    RECT r;
    GetWindowRect(console,&r);
    MoveWindow(console,r.left,r.top,280,300,TRUE);


    HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 12);
    cout<<endl<<endl;
    cout<<"\t MINESWEEPER"<<endl<<endl<<endl;
    SetConsoleTextAttribute(hConsole, 15);
    cout<<"\t  Classic Mode   "<<endl;
    if(index==1)
    {
        SetConsoleTextAttribute(hConsole, 11);
        cout<<"\t   Small   "<<endl;
        SetConsoleTextAttribute(hConsole, 15);
        cout<<"\t   Medium   "<<endl;
        cout<<"\t  Large"<<endl;
        cout<<"\t Custom"<<endl;
    }
    if(index==2)
    {

        cout<<"\t   Small   "<<endl;
        SetConsoleTextAttribute(hConsole, 11);
        cout<<"\t   Medium   "<<endl;
        SetConsoleTextAttribute(hConsole, 15);
        cout<<"\t  Large"<<endl;
        cout<<"\t Custom"<<endl;
    }
    if(index==3)
    {
        cout<<"\t   Small   "<<endl;
        cout<<"\t   Medium   "<<endl;
        SetConsoleTextAttribute(hConsole, 11);
        cout<<"\t  Large"<<endl;
        SetConsoleTextAttribute(hConsole, 15);
        cout<<"\t Custom"<<endl;
    }
    if(index==4)
    {
        cout<<"\t   Small   "<<endl;
        cout<<"\t   Medium   "<<endl;
        cout<<"\t  Large"<<endl;
        SetConsoleTextAttribute(hConsole, 11);
        cout<<"\t Custom"<<endl;
        SetConsoleTextAttribute(hConsole, 15);
    }
}
void arrowsClassicMode()
{
    classicMode(1);
    char c=0;
    c=getch();
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
                    sizex=sizey=10;
                    noOfBombs=10;
                    printMatrix();
                    arrows();
                }
                if(index==2)
                {

                }
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
    createMatrix();
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
    HWND console = GetConsoleWindow();
    RECT r;
    GetWindowRect(console,&r);
    MoveWindow(console,r.left,r.top,280,300,TRUE);
    arrowsMenu();
    return 0;
}
