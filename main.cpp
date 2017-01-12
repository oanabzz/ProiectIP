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

void createInfiniteMatrixButNotReally(int v[1000]);
void printMatrix();
void setConsoleSize(int lines, int columns)
{
    HWND console = GetConsoleWindow();
    RECT r;
    GetWindowRect(console,&r);
    if(lines==10&&columns==10)
        MoveWindow(console,r.left,r.top,280,300,TRUE);
    else
        if(lines==16&&columns==16)
            MoveWindow(console,r.left,r.top,400,400,TRUE);
        else
            if(lines==30&&columns==16)
            MoveWindow(console,r.left,r.top,400,600,TRUE);
            else
                MoveWindow(console,r.left,r.top,lines*30,columns*30,TRUE);

}
void printFirstMessage(int index)
{
    setConsoleSize(10,10);


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
    HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 15);
    keepGoing=0;
    system("cls");
    if(c==0)
    {
        for(int i=1;i<=sizex;i++)
            {
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
                        SetConsoleTextAttribute(hConsole,21);
                        cout<<(char)-31;
                        SetConsoleTextAttribute(hConsole,15);
                        cout<<' ';
                    }
                    else if(trueMap[i][j]!=-1&&mat[i][j]==-31)//bomba pusa gresit
                    {
                        SetConsoleTextAttribute(hConsole,22);
                        cout<<(char)-31;
                        SetConsoleTextAttribute(hConsole,15);
                        cout<<' ';
                    }
                    else cout<<mat[i][j]<<' ';
                }
                cout<<endl;
            }

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
    for(int i=1;i<=sizex;i++)
    {
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
                    //SetConsoleTextAttribute(hConsole, 15);
                    cout<<mat[i][j]<<' ';
            }
            }

        cout<<endl;
    }
    cout<<endl<<endl;
    cout<<seconds;
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
            if(mat[20][j-1]==-1) AUXmatrix[1][j]++;
            if(mat[20][j]==-1)  AUXmatrix[1][j]++;
            if(mat[20][j+1]==-1) AUXmatrix[1][j]++;
            if(AUXmatrix[2][j-1]==-1) AUXmatrix[1][j]++;
            if(AUXmatrix[2][j]==-1) AUXmatrix[1][j]++;
            if(AUXmatrix[2][j+1]==-1) AUXmatrix[1][j]++;
        }
    for(int l=1;l<=2;l++)
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
void copyMatrix()
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
    sizex=10;
    sizey=20;
    createMatrix();
    //generateMatrixFirst();

}
void infiniteMode()
{

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
                return;
            }
            break;




    }
}
}

void classicMode(int index)
{
    setConsoleSize(10,10);


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
                    setConsoleSize(10,10);
                }
                if(index==2)
                {
                    sizex=16;
                    sizey=16;
                    noOfBombs=40;
                    setConsoleSize(16,16);
                }
                if(index==3)
                {
                    sizex=30;
                    sizey=16;
                    noOfBombs=99;
                    setConsoleSize(30,16);
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
    return 0;
}
