#pragma GCC optimize ("Ofast", 3)
#pragma GCC target ("sse3","sse2","sse")
#pragma GCC target ("avx","sse4","sse4.1","sse4.2","ssse3")
#pragma GCC target ("f16c")

#include <bits/stdc++.h>
#include <windows.h>
#include <conio.h>

using namespace std;

#define a1  0
#define a2  1

#define b 2

#define c1 3
#define c2 4
#define c3 5
#define c4 6

#define d1 7
#define d2 8
#define d3 9
#define d4 10

#define e1 11
#define e2 12

#define f1 13
#define f2 14

#define PRE 224
#define UP  72
#define LT  75
#define RT  77
#define DW  80

const int dMap[15][9] = {
        {0, 0, 1, 0, 2, 0, 3, 0, 4}, {0, 0, 0, 1, 0, 2, 0, 3, 1},
        {0, 0, 1, 0, 0, 1, 1, 1, 2},
        {0, 0, 1, 0, 1, 1, 1, 2, 2}, {0, 1, 1, 1, 2, 0, 2, 1, 3}, {0, 0, 0, 1, 0, 2, 1, 2, 2}, {0, 0, 0, 1, 1, 0, 2, 0, 3},
        {1, 0, 1, 1, 1, 2, 0, 2, 2}, {0, 0, 0, 1, 1, 1, 2, 1, 3}, {0, 0, 0, 1, 0, 2, 1, 0, 2}, {0, 0, 1, 0, 2, 0, 2, 1, 3},
        {0, 0, 0, 1, 1, 1, 1, 2, 2}, {0, 1, 1, 0, 1, 1, 2, 0, 3},
        {0, 1, 0, 2, 1, 0, 1, 1, 2}, {0, 0, 1, 0, 1, 1, 2, 1, 3}
};

//const int high[15] = {4, 1, 2, 2, 3, 2, 3, 2, 3, 2, 3, 2, 3, 2, 3};

#define maxl 24
#define maxh 26

unsigned int seed = 19260817;

inline int rotate (int);
#define setCursor(x,y); {COORD tmpSC; tmpSC.X=x, tmpSC.Y=y; SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), tmpSC);}
inline void setColor (int);

inline int realRand ();

#define drawScore(); {setColor(3); setCursor(31, 19); printf("Score:    %d", score);}
#define drawInter(); {setColor(3); setCursor(31, 21); printf("Interval: %d", interval);}
#define drawData();  {drawScore(); drawInter();}
#define drawBlock() printf("■")
#define drawSpace() printf("  ")
inline void drawWelcome ();
inline void drawUI ();
inline void drawTetris (int, int, int, bool);
inline void drawPrediction (int, bool);

#define placeLegal() ((~tmpx)&&(tmpx<25)&&(~tmpy)&&(tmpy<13)&&!vis[tmpx][tmpy])
inline bool placeJudge (int, int, int);

bool vis[28][16];

int score, top = 25, nowx, nowy = 5, steins, kurisu, interval=300;

signed main () {
    drawWelcome();
    drawUI();

    srand(time(NULL));
    steins = (rand() + 15) % 15;
    kurisu = (rand() + 15) % 15;

    drawTetris(kurisu, 5, 16, false);
    drawTetris(steins, nowx, nowy, false);
    drawPrediction(steins, false);

    register int timer = 0;

    while (true) {
        if (timer>=interval) {
            timer = 0; EVANGELION:
            if (placeJudge(steins, nowx + 1, nowy)) {
                drawTetris(steins, nowx ++, nowy, true);
                drawTetris(steins, nowx, nowy, false);
            } else {
                register int tmpx, tmpy;
                for (register int i = 0; i ^ 4; ++ i) {
                    tmpx = nowx + dMap[steins][i<<1];
                    tmpy = nowy + dMap[steins][i<<1|1];
                    setCursor((tmpy + 1) << 1, tmpx + 1);
                    setColor(0); drawBlock();
                    vis[tmpx][tmpy] = true;
                } top = top > nowx ? nowx : top;

                register bool flag = true;
                for (register int i = nowx; i < nowx + dMap[steins][8]; ++ i, flag = true) {
                    for (register int j=0; j^13; ++ j) {
                        if (!vis[i][j]) {flag = false; break;}
                    }
                    if (flag) {
                        for (register int j = i; j >= top; --j) {
                            for (register int k = 0; k ^ 13; ++k) {
                                vis[j][k] = vis[j - 1][k];
                                setCursor((k + 1) << 1, j + 1);
                                if (vis[j][k]) drawBlock();
                                else drawSpace();
                            }
                        } interval *= 0.8; score += (300-interval); drawData();
                    }
                }

                steins = kurisu; kurisu = (rand() + 15) % 15;
                drawTetris(steins, 5, 16, true);
                drawTetris(kurisu, 5, 16, false);
                nowx = 0, nowy = 5;
                drawPrediction(steins, false);
                drawTetris(steins, nowx, nowy, false);

                if (!placeJudge(steins, nowx, nowy)) {
                    system("cls");
                    puts("Game Over");
                    printf("Your score is: %d.\n", score);
                    break;
                }
            }
        }

        if(_kbhit() && !(_getch()^PRE)) {
            register int key = _getch();
            switch(key) {
                case UP:
                    if (placeJudge(rotate(steins), nowx, nowy)) {
                        drawTetris(steins, nowx, nowy, true);
                        steins = rotate(steins);
                        drawPrediction(steins, true);
                        drawTetris(steins, nowx, nowy, false);
                    } break;
                case LT:
                    if (placeJudge(steins, nowx, nowy-1)) {
                        drawTetris(steins, nowx, nowy --, true);
                        drawPrediction(steins, true);
                        drawTetris(steins, nowx, nowy, false);
                    } break;
                case RT:
                    if (placeJudge(steins, nowx, nowy+1)) {
                        drawTetris(steins, nowx, nowy ++, true);
                        drawPrediction(steins, true);
                        drawTetris(steins, nowx, nowy, false);
                    } break;
                case DW:
                    if (placeJudge(steins, nowx+1, nowy)) {
                        drawTetris(steins, nowx ++, nowy, true);
                        drawTetris(steins, nowx, nowy, false);
                        score ++; drawScore();
                        goto EVANGELION;
                    } break;
            }
        } Sleep(1); ++ timer;
    } system("pause"); return 0;
}

inline bool placeJudge (int name, int x, int y) {
    register int tmpx, tmpy;
    for (register int i=0; i^4; ++ i) {
        tmpx = x + dMap[name][i<<1];
        tmpy = y + dMap[name][i<<1|1];
        if(!placeLegal()) return false;
    } return true;
}

int preName = -1, prex, prey;

inline void drawPrediction (int name, bool isClr) {
    register int tmpx, tmpy;
    if (isClr) for (register int i=0; i^4; ++ i) {
        tmpx = prex + dMap[preName][i<<1];
        tmpy = prey + dMap[preName][i<<1|1];
        setCursor((tmpy+1)<<1, tmpx+1);
        drawSpace();
    }

    register int x = nowx, y = nowy;
    while (placeJudge(name, ++ x, y)); x --;

    for (register int i=0; i^4; ++ i) {
        tmpx = x + dMap[name][i<<1];
        tmpy = y + dMap[name][i<<1|1];
        setCursor((tmpy+1)<<1, tmpx+1);
        setColor(i+1); printf("□");
    } prex = x, prey = y, preName = name;
}

inline void drawTetris (int name, int x, int y, bool re) {
    register int tmpx, tmpy;
    for (register int i=0; i^4; ++ i) {
        tmpx = x + dMap[name][i<<1];
        tmpy = y + dMap[name][i<<1|1];
        setCursor((tmpy+1)<<1, tmpx+1);
        if (re) drawSpace();
        else {setColor(i+1); drawBlock();}
    }
}

inline void drawWelcome () {
    system("cls");
    puts("Welcome to tetris!");
    puts("Code By Ellias Kiri Stuart @ 2021/03/24");
    //puts("Press any key to start...");
    system("pause");
    system("cls");
}

inline void drawUI () {
    setColor(3);
    for (register int i=0; i^maxl; ++ i) {
        setCursor(i<<1, 0); printf("##"); //drawBlock();
        setCursor(i<<1, maxh); printf("##"); //drawBlock();
    } for (register int i=0; i^maxh; ++ i) {
        setCursor(0, i);       printf("##"); //drawBlock();
        setCursor(maxl+4, i);  printf("##"); //drawBlock();
        setCursor(maxl+22, i); printf("##"); //drawBlock();
    }

    drawScore(); drawInter();
    setColor(3); setCursor(32, 2);  printf("Next: ");
}

inline int rotate (int name) {
    switch (name) {
        case a1: return a2;
        case a2: return a1;

        case b: return b;

        case c1: return c2;
        case c2: return c3;
        case c3: return c4;
        case c4: return c1;

        case d1: return d2;
        case d2: return d3;
        case d3: return d4;
        case d4: return d1;

        case e1: return e2;
        case e2: return e1;

        case f1: return f2;
        case f2: return f1;
    } return -1;
}

inline void setColor (int color) {
    switch (color) {
        case 0: color = 0x08; break;
        case 1: color = 0x0C; break;
        case 2: color = 0x0D; break;
        case 3: color = 0x0E; break;
        case 4: color = 0x0A; break;
    } SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

inline int realRand () {
    seed^=seed<<17, seed^=seed>>5, seed^=seed<<23;
    return seed;
}