#include <iostream>
#include <stdlib.h>
#include<string.h>
#include<conio.h>
#include<windows.h>
#include<random>
#include <time.h>
#include<math.h>

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77


using namespace std;
int sizex,sizey;
int pozi=1, pozj=1;
int noOfBombs=10;
char mat[1000][1000];
int trueMap[1000][1000];
int dl[]={-1,0,1,0,-1,1,1,-1};
int dc[]={0,1,0,-1,1,1,-1,-1};
void beginGame()
{
    int option;
    cout<<"Hello"<<endl<<endl;
    cout<<"Choose your option:"<<endl;
    cout<<"1. New Game"<<endl;
    cout<<"Your option: ";
    cin>>option;
    system("cls");
}
void createMatrix()
{
    for(int i=1;i<=10;i++)
        for(int j=1;j<=10;j++)
            mat[i][j]=167;
    mat[1][1]=254;
}
void printMatrix()
{
    HANDLE  hConsole;

    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    //system("cls");
    SetConsoleTextAttribute(hConsole, 15);
    for(int i=1;i<=10;i++)
    {
        for(int j=1;j<=10;j++)
            if(i==pozi&&j==pozj)
            {
                SetConsoleTextAttribute(hConsole, 12);
                cout<<mat[i][j]<<' ';
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
    cout<<randomPos<<endl;
    while(countBombs<noOfBombs)
    {
        x=rand()%10+1;
        y=rand()%10+1;
        cout<<x<<' '<<y<<endl<<endl;
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
    if(trueMap[i][j]==0)
        mat[i][j]=0;
    else
        mat[i][j]='0'+trueMap[i][j];
    for(int k=0;k<8;k++)
        if(mat[i+dl[k]][j+dc[k]]>=0)
            transformPrintingMat(i+dl[k],j+dc[k]);
}
void arrows()
{

int c = 0;
    while(1)
    {
        c = 0;

        switch((c=getch())) {
        case KEY_UP:
            {
                if(pozi>1)
                {mat[pozi][pozj]=167;
                pozi--;
                mat[pozi][pozj]=254;
                printMatrix();}
            }
            break;
        case KEY_DOWN:
            {
                if(pozi<10)
                {mat[pozi][pozj]=167;
                pozi++;
                mat[pozi][pozj]=254;
                printMatrix();}
            }
            break;
        case KEY_LEFT:
            {
                if(pozj>1)
                {mat[pozi][pozj]=167;
                pozj--;
                mat[pozi][pozj]=254;
                printMatrix();}
            }
            break;
        case KEY_RIGHT:
            {
                if(pozj<10)
                {mat[pozi][pozj]=167;
                pozj++;
                mat[pozi][pozj]=254;
                printMatrix();}
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
    generateMatrixFirst(2,3);
    for(int i=1;i<=10;i++)
    {
        for(int j=1;j<=10;j++)
            {
                cout<<trueMap[i][j]<<' ';
                if(trueMap[i][j]>=0)
                    cout<<' ';
            }
        cout<<endl;
    }
    cout<<endl;
    printMatrix();
    //arrows();
    return 0;
}
