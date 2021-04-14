/*
 * Tetris Console
 * First Issue: 2021/02/04
 * Copyright: Ellias Kiri Stuart
 * Licence: MIT
 * GitHub: https://github.com/novaELLIAS/TetrisConsole
 */

#pragma GCC optimize ("Ofast", 3)
#pragma GCC target ("sse3","sse2","sse")
#pragma GCC target ("avx","sse4","sse4.1","sse4.2","ssse3")
#pragma GCC target ("f16c")

//#include <bits/stdc++.h>
#include <iostream>
#include <cstdio>
#include <cmath>
#include <vector>
#include <string>
#include <queue>
#include <ctime>
#include <fstream>
#include <algorithm>
#include <windows.h>
#include <conio.h>

using namespace std;

#define a1 0
#define a2 1

#define b1 2

#define c1 3
#define c2 4
#define c3 5
#define c4 6

#define n1 7
#define n2 8
#define n3 9
#define n4 10

#define d1 11
#define d2 12
#define d3 13
#define d4 14

#define e1 15
#define e2 16

#define f1 17
#define f2 18

#define g1 19

#define h1 20
#define h2 21
#define h3 22
#define h4 23

#define k1 24
#define k2 25

#define m1 26
#define m2 27

#define PRE 224
#define UP  72
#define LT  75
#define RT  77
#define DW  80
#define SP  32

#define MP(x,y) make_pair(x,y)

/*
const int dMapOrigin[24][9] = {
    {0, 0, 1, 0, 2, 0, 3, 0, 4}, {0, 0, 0, 1, 0, 2, 0, 3, 1},
    {0, 0, 1, 0, 0, 1, 1, 1, 2},
    {0, 0, 1, 0, 1, 1, 1, 2, 2}, {0, 1, 1, 1, 2, 0, 2, 1, 3}, {0, 0, 0, 1, 0, 2, 1, 2, 2}, {0, 0, 0, 1, 1, 0, 2, 0, 3},
    {1, 0, 1, 1, 1, 2, 0, 2, 2}, {0, 0, 0, 1, 1, 1, 2, 1, 3}, {0, 0, 0, 1, 0, 2, 1, 0, 2}, {0, 0, 1, 0, 2, 0, 2, 1, 3},
    {0, 0, 0, 1, 1, 1, 1, 2, 2}, {0, 1, 1, 0, 1, 1, 2, 0, 3},
    {0, 1, 0, 2, 1, 0, 1, 1, 2}, {0, 0, 1, 0, 1, 1, 2, 1, 3},
    {0, 0, 0, 0, 0, 0, 0, 0, 1},
    {0, 0, 0, 1, 1, 0, 0, 0, 2}, {0, 0, 0, 0, 1, 0, 1, 1, 2}, {0, 0, 0, 0, 1, 0, 1,-1, 2}, {0, 0, 0, 0, 0,-1, 1, 0, 2},
    {0, 0, 0, 0, 0, 1, 0, 2, 1}, {0, 0, 0, 0, 1, 0, 2, 0, 3},
    {0, 0, 0, 0, 1, 0, 1, 0, 2}, {0, 0, 0, 0, 0, 1, 0, 1, 1}
};
*/

int height[28] = {4, 1, 2, 2, 3, 2, 3, 2, 3, 2, 3, 2, 3, 2, 3, 2, 3, 2, 3, 1, 2, 2, 2, 2, 1, 3, 2, 1};

const vector <pair<int, int> > dMap[28] = {

    {MP(0, 0), MP(1, 0), MP(2, 0), MP(3, 0)},
    {MP(0, 0), MP(0, 1), MP(0, 2), MP(0, 3)},

    {MP(0, 0), MP(1, 0), MP(0, 1), MP(1, 1)},

    {MP(0, 0), MP(1, 0), MP(0, 1), MP(0, 2)},
    {MP(0, 0), MP(1, 0), MP(2, 0), MP(2, 1)},
    {MP(0, 2), MP(1, 0), MP(1, 1), MP(1, 2)},
    {MP(0, 0), MP(0, 1), MP(1, 1), MP(2, 1)},

    {MP(0, 0), MP(1, 0), MP(1, 1), MP(1, 2)},
    {MP(0, 1), MP(1, 1), MP(2, 0), MP(2, 1)},
    {MP(0, 0), MP(0, 1), MP(0, 2), MP(1, 2)},
    {MP(0, 0), MP(0, 1), MP(1, 0), MP(2, 0)},

    {MP(1, 0), MP(1, 1), MP(1, 2), MP(0, 1)},
    {MP(1, 0), MP(0, 1), MP(1, 1), MP(2, 1)},
    {MP(0, 0), MP(0, 1), MP(0, 2), MP(1, 1)},
    {MP(0, 0), MP(1, 0), MP(2, 0), MP(1, 1)},

    {MP(0, 0), MP(0, 1), MP(1, 1), MP(1, 2)},
    {MP(0, 1), MP(1, 0), MP(1, 1), MP(2, 0)},

    {MP(0, 1), MP(0, 2), MP(1, 0), MP(1, 1)},
    {MP(0, 0), MP(1, 0), MP(1, 1), MP(2, 1)},

    {MP(0, 0)},

    {MP(0, 0), MP(0, 1), MP(1, 0)},
    {MP(0, 0), MP(1, 0), MP(1, 1)},
    {MP(0, 0), MP(1, 0), MP(1,-1)},
    {MP(0, 0), MP(0,-1), MP(1, 0)},

    {MP(0, 0), MP(0, 1), MP(0, 2)},
    {MP(0, 0), MP(1, 0), MP(2, 0)},

    {MP(0, 0), MP(1, 0)},
    {MP(0, 0), MP(0, 1)}
};

class ID_generator {
private:

    const pair<int, int> ptnMap[8] = {
            MP(0, 2), MP(2, 1), MP(3, 4), MP(7, 4), MP(11, 4),
            MP(15, 2), MP(17, 2), MP(19, 9)
    };

    queue<int> idQue;

    struct node {
        int data, index;
        bool operator < (const node &b) const {
            return index < b.index;
        }
    } workQue[8];

    inline void addNewElement();

public:

    inline void init();
    inline int getNewID();

} idGenerator;

#define maxl 24
#define maxh 26

#define downinterval 50

unsigned int seed = 19260817;

inline int rotate (int);
#define setCursor(x,y); {COORD tmpSC;tmpSC.X=x,tmpSC.Y=y;SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),tmpSC);}
inline void isCursorDisplay(bool);
inline void setColor (int);

inline int realRand ();
inline int qpow (int, int);

inline void drawDataInt (int, int);
inline void drawScore ();
inline void drawChBase ();
inline void drawLogo();
inline void drawName ();

inline void readRankList ();
inline void writeRankList ();
inline void updateRankList ();
inline void drawRankList (int, int, int);

//#define drawCntDn(); {setColor(3); setCursor(30, 15); cout<<setw(16)<<setiosflags(ios::internal)<<cntDown;}
//#define drawScore(); {setColor(3); setCursor(30, 19); printf("%m16d", score);}
//#define drawInter(); {setColor(3); setCursor(30, 23); printf("%m16d", 301-interval);}
//#define drawCntDn(); {drawDataInt(cntDown, 15);}
//#define drawChBase(); {drawDataInt(chBase, 15);}
#define drawInter(); {drawDataInt(301-interval, 23);}
//#define drawData();  {drawScore(); drawInter(); drawCntDn();}
#define drawData();  {drawScore(); drawInter(); drawChBase();}
#define drawBlock() printf("■")
#define drawSpace() printf("  ")
inline void drawWelcome ();
inline void drawUI ();
//inline void drawGameOver();
//inline void drawYouWin();
inline void drawTetris (int, int, int, bool);
inline void drawPrediction (int, bool);
inline void drawLog (string);

#define fontColorReset() SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7)
#define placeLegal() ((~tmpx) && (tmpx<25) && (~tmpy) && (tmpy<13) && !vis[tmpx][tmpy])
inline bool placeJudge (int, int, int);

inline void endGame (bool);

bool vis[28][16];

int queHead, queTail, queSize;
#define queLen 20
#define maxNum 17
#define logStartX (27<<1)
#define logStartY 9

struct node {
    string str;
    int color;
} que[queLen];
queue<int> tmpQue;
clock_t startTime;
const string empStr="                                                               ";

string username;

int top = 25, nowx, nowy = 5, steins, kurisu, interval=300, cntDown=1;
long long score, chBase = 1ll;
int preName = -1, prex, prey;
char buff[1001];

signed main () {
    //ios::sync_with_stdio(false);

    srand(time(NULL));

    SetConsoleTitle("TetrisConsole v3.21 World Vanquisher");
    system("mode con cols=123 lines=30");
    system("cls");
    isCursorDisplay(false);

    idGenerator.init();
    drawUI();
    drawLogo();
    drawWelcome();

    do steins = idGenerator.getNewID(); //(rand() + 24) % 24;
    while (steins>=15 && steins<=18);
    kurisu = idGenerator.getNewID(); //(rand() + 24) % 24;

    drawTetris(kurisu, 5, 16, false);
    drawTetris(steins, nowx, nowy, false);
    drawPrediction(steins, false);

    register int timer = 0;

    drawData();

    register string logStr;
    startTime = clock();
    drawLog("[sys] Game Start.");

    register bool lastDownOptionClear = false;
    register bool lastDownOption = false;
    register int  totalFreezeCounter = 2;

    while (true) {
        if (timer >= downinterval) lastDownOptionClear = false;
        if (timer >= interval) {
            timer = lastDownOptionClear = lastDownOption = 0;
            if (cntDown > 2) {
                sprintf(buff, "[dat] Score inc by %d because of decent acce bonus.", (int)log(cntDown));
                logStr.assign(buff); drawLog(logStr); score += (int)log(cntDown);
            } cntDown = 1; drawData(); DROPTEST:
            if (placeJudge(steins, nowx + 1, nowy)) {
                drawTetris(steins, nowx ++, nowy, true);
                drawTetris(steins, nowx, nowy, false);
                if (!placeJudge(steins, nowx + 1, nowy)) goto BLOCKFREEZE;
            } else {
                BLOCKFREEZE:
                if (cntDown > 2) {
                    sprintf(buff, "[dat] Score inc by %d because of decent acce bonus.", (int)log(cntDown));
                    logStr.assign(buff); drawLog(logStr); score += (int)log(cntDown);
                } cntDown = 1; timer = 0;
                lastDownOptionClear = lastDownOption;
                sprintf(buff, "[sys] Tetris %d frozen at (%d, %d).", steins, nowx, nowy);
                logStr.assign(buff); drawLog(logStr); register int tmpx, tmpy;
                sprintf(buff, "[dat] Score increased by %d.", (305-interval)*(int)log(++ totalFreezeCounter));
                logStr.assign(buff); drawLog(logStr); score += (305-interval)*(int)log(totalFreezeCounter);
                auto iter = dMap[steins].cbegin();
                for (; iter != dMap[steins].cend(); ++ iter) {
                    tmpx = nowx + iter->first;
                    tmpy = nowy + iter->second;
                    setCursor((tmpy + 1) << 1, tmpx + 1);
                    setColor(0); drawBlock();
                    vis[tmpx][tmpy] = true;
                } top = top > nowx ? nowx : top;

                register bool tflag = false, flag; register int clrCnt = 0;
                while (!tmpQue.empty()) tmpQue.pop();
                for (register int i=nowx; i < nowx+height[steins]; ++ i, flag=true) {
                    for (register int j=0; j^13; ++ j) {
                        if (!vis[i][j]) { flag = clrCnt = 0; break;}
                    } if (flag) {
                        clrCnt += (tflag = true), tmpQue.push(i);
                        for (register int j = i; j >= top; -- j) {
                            for (register int k = 0; k ^ 13; ++ k) {
                                vis[j][k] = vis[j - 1][k];
                                setCursor((k + 1) << 1, j + 1);
                                if (vis[j][k]) drawBlock();
                                else drawSpace();
                            }
                        }
                    }
                } if (tflag) {
                    if (!tmpQue.empty()) {
                        register string tmpStr = "";
                        sprintf(buff, "[sys] Level"); logStr.assign(buff);
                        while (!tmpQue.empty()) {
                            if (tmpQue.size() ^ 1) {
                                sprintf(buff, " %d,", tmpQue.front()); tmpQue.pop();
                            } else {sprintf(buff, " %d", tmpQue.front()); tmpQue.pop();}
                            tmpStr.assign(buff); logStr = logStr + tmpStr;
                        } logStr += " has been cleared."; drawLog(logStr);
                    }

                    sprintf(buff, "[dat] Interval decreased because of level clearing.");
                    logStr.assign(buff); drawLog(logStr); interval = (int)(interval * 0.85);

                    if (clrCnt) {
                        sprintf(buff, "[dat] Score inc by %d because of clearing %d levels.",\
                            ((300 - interval) << clrCnt)*(int)log(totalFreezeCounter), clrCnt);
                        logStr.assign(buff); drawLog(logStr);
                        score += ((300 - interval) << clrCnt)*(int)log(totalFreezeCounter);
                    } drawData(); drawLogo();
                }

                sprintf(buff, "[sys] New tetris %d generated.", kurisu);
                logStr.assign(buff); drawLog(logStr);

                steins = kurisu; kurisu = idGenerator.getNewID(); //(rand() + 24) % 24;
                drawTetris(steins, 5, 16, true);
                drawTetris(kurisu, 5, 16, false);
                nowx = 0, nowy = 5;
                drawPrediction(steins, false);
                drawTetris(steins, nowx, nowy, false);

                if (!placeJudge(steins, nowx, nowy)) endGame(false);
            }
        }

        register int key; KEYCHECK:
        if(_kbhit()) if((key=_getch()) ^ PRE) {
            lastDownOption = lastDownOptionClear = false;
            switch(key) {
                case 'r':
                    if (placeJudge(kurisu, nowx, nowy) && (steins ^ kurisu)) {
                        sprintf(buff, "[key] Key [R] triggered, change %d to %d.", steins, kurisu);
                        logStr.assign(buff); drawLog(logStr);
                        drawTetris(steins, nowx, nowy, true);
                        drawTetris(kurisu, 5, 16, true);
                        steins ^= kurisu ^= steins ^= kurisu;
                        drawPrediction(steins, true);
                        drawTetris(steins, nowx, nowy, false);
                        drawTetris(kurisu, 5, 16, false);
                        if (cntDown > 2) {
                            sprintf(buff, "[dat] Score inc by %d because of decent acce bonus.", (int) log(cntDown));
                            logStr.assign(buff); drawLog(logStr); score += (int) log(cntDown);
                        }
                        sprintf(buff, "[dat] Score dec by 2^%d because of using [R].", (int) log(chBase <<= 1));
                        logStr.assign(buff); drawLog(logStr); score -= chBase; cntDown = 1;
                        sprintf(buff, "[dat] Interval decreased because of using [R].");
                        logStr.assign(buff); drawLog(logStr); interval = (int) (interval * 0.99);drawData();
                    } goto KEYCHECK; break;

                case SP:
                    cntDown += (prex-nowx)<<1; drawTetris(steins, nowx, nowy, true); nowx=prex; goto BLOCKFREEZE;
                    goto KEYCHECK; break;
            }
        } else {
            key = _getch();
            switch(key) {
                case UP:
                    lastDownOption = lastDownOptionClear = false;
                    if (cntDown > 2) {
                        sprintf(buff, "[dat] Score inc by %d because of decent acce bonus.", (int)log(cntDown));
                        logStr.assign(buff); drawLog(logStr); score += (int)log(cntDown);
                    } cntDown = 1; drawData(); rotate(steins); if (placeJudge(rotate(steins), nowx, nowy)) {
                        sprintf(buff, "[key] Key [↑] triggered, change %d to %d.", steins, rotate(steins));
                        logStr.assign(buff); drawLog(logStr);
                        drawTetris(steins, nowx, nowy, true);
                        steins = rotate(steins);
                        drawPrediction(steins, true);
                        drawTetris(steins, nowx, nowy, false);
                        goto KEYCHECK;
                    } else {
                        drawLog("[key] Key [↑] triggered but unable to rotate.");
                    } break;
                case LT:
                    lastDownOption = lastDownOptionClear = false;
                    if (cntDown > 2) {
                        sprintf(buff, "[dat] Score inc by %d because of decent acce bonus.", (int)log(cntDown));
                        logStr.assign(buff); drawLog(logStr); score += (int)log(cntDown);
                    } cntDown = 1; drawData(); if (placeJudge(steins, nowx, nowy-1)) {
                        //sprintf(buff, "[key] Key [←] triggered, x changed from %d to %d.", nowy, nowy-1);
                        //logStr.assign(buff); drawLog(logStr);
                        drawTetris(steins, nowx, nowy --, true);
                        drawPrediction(steins, true);
                        drawTetris(steins, nowx, nowy, false);
                        goto KEYCHECK;
                    } else {
                        drawLog("[key] Key [←] triggered but unable to move.");
                    } break;
                case RT:
                    lastDownOption = lastDownOptionClear = false;
                    if (cntDown > 2) {
                        sprintf(buff, "[dat] Score inc by %d because of decent acce bonus.", (int)log(cntDown));
                        logStr.assign(buff); drawLog(logStr); score += (int)log(cntDown);
                    } cntDown = 1; drawData(); if (placeJudge(steins, nowx, nowy+1)) {
                        //sprintf(buff, "[key] Key [→] triggered, x changed from %d to %d.", nowy, nowy+1);
                        //logStr.assign(buff); drawLog(logStr);
                        drawTetris(steins, nowx, nowy ++, true);
                        drawPrediction(steins, true);
                        drawTetris(steins, nowx, nowy, false);
                        goto KEYCHECK;
                    } else {
                        drawLog("[key] Key [→] triggered but unable to move.");
                    } break;
                case DW:
                    if (!lastDownOptionClear) {
                        if (placeJudge(steins, nowx+1, nowy)) {
                            drawTetris(steins, nowx ++, nowy, true);
                            drawTetris(steins, nowx, nowy, false);
                            ++ cntDown; drawData(); lastDownOption = true;
                            goto DROPTEST;
                        } goto BLOCKFREEZE;
                    } break;
            }
        } Sleep(1); ++ timer; drawScore();
        if (clock()-startTime >= 9999990) endGame(true);
    } system("pause"); return 0;
}

struct rankElement {
    string name;
    long long score;
} rankList[20];

fstream file;

inline void readRankList () {

    file.open("tetrisRanking.dat", ios::in);
    for (register int i=0; i^10; ++ i) {
        if (file >> rankList[i].name) file >> rankList[i].score;
        else break;
    } file.close();

//    freopen("tetrisRanking.dat", "r", stdin);
//    for (register int i=0; i^10; ++ i) {
//        if (std::cin >> rankList[i].name) std::cin >> rankList[i].score;
//        else break;
//    } fclose (stdin);
}

inline void writeRankList () {

    file.open("tetrisRanking.dat", ios::out|ios::trunc);
    for (register int i=0; i^10; ++ i) {
        if (rankList[i].name == "") break;
        file << rankList[i].name << " " << rankList[i].score << endl;
    } file.close();

//    freopen("tetrisRanking.dat", "w", stdout);
//    for (register int i=0; i^10; ++ i) {
//        if (rankList[i].name == "") break;
//        std::cout << rankList[i].name << " " << rankList[i].score << endl;
//    } fclose (stdout);
}

inline bool cmp (rankElement a, rankElement b) {
    return (a.score^b.score)? (a.score>b.score):(a.name>b.name);
}

inline void updateRankList () {
    register int listLen = 0, pos = -1;
    while (true) {
        if (rankList[listLen].name == username) pos = listLen;
        if (rankList[listLen].name == "") break; ++ listLen;
    } if (pos == -1) pos = listLen; else -- listLen;
    rankList[pos] = (rankElement){username, max(rankList[pos].score, score)};
    std::sort(rankList+0, rankList+listLen+1, cmp);
}

inline void drawRankList (int X, int Y, int num) {
    fontColorReset();
    for (register int i=0; i^num; ++ i) {
        if (rankList[i].name == "") break;
        if (rankList[i].name == username) setColor(3);
        else fontColorReset();
        setCursor(X, Y+i); printf("#%02d ", i+1); std::cout << rankList[i].name;
        setCursor(X+11, Y+i); printf("%23lld", rankList[i].score);
    }
}

inline bool placeJudge (int name, int x, int y) {
    register int tmpx, tmpy;
    auto iter = dMap[name].begin();
    for (; iter != dMap[name].end(); ++ iter) {
        tmpx = x + iter->first;
        tmpy = y + iter->second;
        if(!placeLegal()) return false;
    } return true;
}

inline void drawDataInt (int num, int y) {
    setCursor(30, y);
    for (register int i=0; i^16; ++ i) putchar(' ');
    register int cnt = 0, a = num;
    setColor(3); setCursor(30, y);
    while (a /= 10) ++ cnt;
    cnt = (16-cnt) >> 1;
    while (cnt --) putchar(' ');
    printf("%d", num);
}

inline void drawChBase () {
    setCursor(30, 15);
    printf("                ");
    static char cMap[4] = {' ', 'K', 'M', 'G'};
    register int cnt = 0, cPos = 0;
    register long long a = chBase;
    setColor(3); setCursor(30, 15);
    while (a /= 10ll) ++ cnt; a = chBase;
    if (cnt>=16) endGame(false);//drawGameOver();
    while (cnt>8) {
        cnt -= 2, a /= 1000, ++ cPos;
        if (cPos > 3) endGame(false);//drawGameOver();
    } cnt = (16-cnt) >> 1;
    while (cnt --) putchar(' '); printf("%lld", a);
    /*fontColorReset();*/ setColor(1); putchar(cMap[cPos]);
}

inline void drawScore () {
    static char cMap[5] = {' ', 'K', 'M', 'G', 'T'};
    register int cnt = 0, cPos = 0, winFlag = 0;
    register long long a = score;
    register bool minusFlag = false;
    if (a<0ll) a = -a, minusFlag = true, ++ cnt;

    while (a /= 10ll) ++ cnt; a = score;
    if (cnt>=16) winFlag = a>0? 2:1;
    while (cnt>8) {cnt -= 2, a /= 1000, ++ cPos;}
    cnt = (16-cnt) >> 1;
    setCursor(30, 19); printf("                ");
    setColor(3); setCursor(30, 19);
    while (cnt --) putchar(' '); printf("%lld", a);
    /*fontColorReset();*/ setColor(1); putchar(cMap[cPos]);
    if (winFlag) endGame(winFlag^1); //(winFlag^1)? drawYouWin():drawGameOver();
}

inline void drawName () {
    register int cnt = (16 - username.length()) >> 1;
    setCursor(30, 11); fontColorReset();
    while (cnt --) putchar(' ');
    std::cout << username; return;
}

inline void drawPrediction (int name, bool isClr) {
    register int tmpx, tmpy;
    auto iter = dMap[preName].begin();
    if (isClr) for (; iter != dMap[preName].end(); ++ iter) {
        tmpx = prex + iter->first;
        tmpy = prey + iter->second;
        setCursor((tmpy+1)<<1, tmpx+1);
        drawSpace();
    }

    register int x = nowx - 1, y = nowy, cnt = 0;
    while (placeJudge(name, ++ x, y)); x --;

    iter = dMap[name].begin();
    for (; iter != dMap[name].end(); ++ iter, ++ cnt) {
        tmpx = x + iter->first;
        tmpy = y + iter->second;
        setCursor((tmpy+1)<<1, tmpx+1);
        setColor(cnt + 1); printf("□");
    } prex = x, prey = y, preName = name;
}

inline void drawTetris (int name, int x, int y, bool re) {
    register int tmpx, tmpy, cnt = 0;
    auto iter = dMap[name].begin();
    for (; iter != dMap[name].end(); ++ iter, ++ cnt) {
        tmpx = x + iter->first;
        tmpy = y + iter->second;
        setCursor((tmpy+1)<<1, tmpx+1);
        if (re) drawSpace();
        else {setColor(cnt + 1); drawBlock();}
    }
}

inline void drawLog (string s) {
    register double nowTime = (double) (clock()-startTime) / 1000.0;
    sprintf(buff, "[%07.2f]", nowTime);
    register string timeStr; timeStr.assign(buff);

    while (queSize >= maxNum) queHead = (queHead + 1) % queLen, -- queSize;
    switch(s[1]) {
        case 's': que[queTail].color = 7; break;
        case 'e': que[queTail].color = FOREGROUND_RED; break;
        case 'd': que[queTail].color = FOREGROUND_GREEN; break;
        case 'k': que[queTail].color = FOREGROUND_BLUE; break;
    } que[queTail].str = timeStr + s, queTail = (queTail + 1) % queLen, ++ queSize;

    for (register int i=queHead, cnt=0; i^queTail; i=(i+1)%queLen, ++cnt) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), que[i].color);
        setCursor(logStartX, logStartY + cnt); cout << empStr;
        setCursor(logStartX, logStartY + cnt); cout << que[i].str;
    }
}

inline void endGame (bool isWin) {
    updateRankList(); writeRankList();

    for (register int i=0; i^17; ++ i) {setCursor(logStartX, logStartY + i); std::cout << empStr;}

    fontColorReset(); setCursor(logStartX, logStartY);printf(isWin? "Congratulations!! You win.":"Game Over!");
    setCursor(logStartX, logStartY+2); printf("Your score is: ");
    setColor(3); printf("%lld", score); fontColorReset();
    setCursor(logStartX, logStartY+4); printf("Ranking: ");
    drawRankList(logStartX+9, logStartY+5, 10); fontColorReset();

    setCursor(logStartX, logStartY+16) printf("Please press [Q] to quit.");
    drawUI(); while (!_kbhit()||(_getch()^'q')) Sleep(100);
    fontColorReset(); system("cls"); exit(0);
}

//inline void drawYouWin () {
////    sprintf(buff, "[sys] Congratulations!! You Win!");
////    register string tmpStr; tmpStr.assign(buff); drawLog(tmpStr);
////    sprintf(buff, "[dat] Your score is: %lld.", score); tmpStr.assign(buff); drawLog(tmpStr);
////    sprintf(buff, "[sys] Please press [Q] to quit.", score); tmpStr.assign(buff); drawLog(tmpStr);
////    while (!_kbhit() || (_getch()^'q')) Sleep(100);
////    isCursorDisplay(true); fontColorReset(); system("cls"); exit(0);
//}

//inline void drawGameOver () {
//    updateRankList(); //writeRankList();
//
//    for (register int i=0; i^17; ++ i) {setCursor(logStartX, logStartY + i); std::cout << empStr;}
//
//    fontColorReset(); setCursor(logStartX, logStartY); printf("Game Over!");
//    setCursor(logStartX, logStartY+2); printf("Your score is: %lld", score);
//
//    setCursor(logStartX, logStartY+4); printf("Ranking: ");
//    readRankList(); drawRankList(logStartX+9, logStartY+4, 10); fontColorReset();
//
//    setCursor(logStartX, logStartY+16) printf("Please press [Q] to quit.");
//    drawUI(); while (!_kbhit()||(_getch()^'q')) Sleep(100);
//    fontColorReset(); system("cls"); exit(0);
//
////    sprintf(buff, "[sys] Game Over!", score);
////    register string tmpStr; tmpStr.assign(buff); drawLog(tmpStr);
////    sprintf(buff, "[dat] Your score is: %lld.", score); tmpStr.assign(buff); drawLog(tmpStr);
////    sprintf(buff, "[sys] Please press [Q] to quit."); tmpStr.assign(buff); drawLog(tmpStr);
////    drawUI(); while (!_kbhit()||(_getch()^'q')) Sleep(100);
////    fontColorReset(); system("cls"); exit(0);
//}

inline void drawWelcome () {
    fontColorReset();
    setCursor(logStartX, logStartY+1);  printf("Welcome to TetrisConsole!");
    setCursor(logStartX, logStartY+3);  printf("use [↑] to rotate.");
    setCursor(logStartX, logStartY+4);  printf("use [←] and [→] to move left or right.");
    setCursor(logStartX, logStartY+5);  printf("use [↓] to accelerate the decent while [SPACE] to set.");
    setCursor(logStartX, logStartY+6);  printf("use [R] to swap now and next.");
    setCursor(logStartX, logStartY+8);  printf("Please input your name(less than 10): ");
    INPUTNAME: isCursorDisplay(true); std::cin >> username;
    if (username.length()>=10) {
        setCursor(logStartX, logStartY+8); std::cout << empStr;
        setCursor(logStartX, logStartY+8); printf("Name too long. Try again(less than 10): ");
        goto INPUTNAME;
    } setCursor(logStartX, logStartY+10); printf("Ranking: ");
    readRankList(); updateRankList(); drawRankList(logStartX+9, logStartY+10, 5); fontColorReset();

    setCursor(logStartX, logStartY+16); printf("Press [E] to start. Enjoy Yourself!");
    isCursorDisplay(false); drawName ();

    while (!_kbhit() || (_getch()^'e')) Sleep(100);

    for (register int i=0; i^17; ++ i) {setCursor(logStartX, logStartY+i); cout << empStr;};
}

//inline void drawYouWin () {
//    system("cls");
//    isCursorDisplay(true);
//    puts("YouWin!");
//    printf("Your score is: %d.\n", score);
//    exit(0);
//}
//
//inline void drawGameOver () {
//    system("cls");
//    isCursorDisplay(true);
//    puts("Game Over");
//    printf("Your score is: %d.\n", score);
//    exit(0);
//}
//
//inline void drawWelcome () {
//    system("cls");
//    puts("Welcome to tetris!");
//    puts("Code By Ellias Kiri Stuart @ 2021/03/24");
//    //puts("Press any key to start...");
//    system("pause");
//    system("cls");
//}

inline void drawUI () {
    setColor(3);
    for (register int i=0; i^15; ++ i) {
        setCursor(i<<1, 0); printf("##"); //drawBlock();
        setCursor(i<<1, maxh); printf("##"); //drawBlock();
    } for (register int i=15; i^23; ++ i) {
        setCursor(i<<1, 0); printf("=");
        setCursor(i<<1, maxh); printf("=");
    } for (register int i=0; i^maxh; ++ i) {
        setCursor(0, i);       printf("##"); //drawBlock();
        setCursor(maxl+4, i);  printf("##"); //drawBlock();
        //setCursor(maxl+22, i); printf("##"); //drawBlock();
        setCursor(maxl+22, i); printf("￤");
    }

    setCursor(0, 0); printf("□");
    setCursor(0, maxh); printf("□");
    setCursor(14<<1, 0); printf("□≡≡");
    setCursor(14<<1, maxh); printf("□≡≡");
    setCursor((23<<1)-2, 0); putchar('-');
    setCursor((23<<1)-2, maxh); putchar('-');
    setCursor(23<<1, 0); printf("◇");
    setCursor(23<<1, maxh); printf("◇");

    //drawScore(); drawInter();
    fontColorReset();
    /*setColor(3);*/ setCursor(36, 2);  printf("NEXT");
    /*setColor(3);*/ setCursor(36, 13); printf("Base");
    /*setColor(3);*/ setCursor(35, 17); printf("nScore");
    /*setColor(3);*/ setCursor(35, 21); printf("nSpeed");
    setCursor(0, 27); printf("Copyright (c) 2021 Ellias Kiri Stuart");
    setCursor(0, 28); printf("GitHub Issue: TetrisConsole");
}

/*
inline int rotate (int name) {
    switch (name) {
        case a1: return a2;
        case a2: return a1;

        case b1: return b1;

        case c1: return c2;
        case c2: return c3;
        case c3: return c4;
        case c4: return c1;

        case n1: return n2;
        case n2: return n3;
        case n3: return n4;
        case n4: return n1;

        case d1: return d2;
        case d2: return d3;
        case d3: return d4;
        case d4: return d1;

        case e1: return e2;
        case e2: return e1;

        case f1: return f2;
        case f2: return f1;

        case g1: return g1;

        case h1: return h2;
        case h2: return h3;
        case h3: return h4;
        case h4: return h1;

        case k1: return k2;
        case k2: return k1;

        case m1: return m2;
        case m2: return m1;
    } return -1;
}
*/

inline int rotate (int name) {

    register int nameRet;

    switch (name) {
        case a1: nameRet = a2; break;
        case a2: nameRet = a1; break;

        case b1: nameRet = b1; break;

        case c1: nameRet = c2; break;
        case c2: nameRet = c3; break;
        case c3: nameRet = c4; break;
        case c4: nameRet = c1; break;

        case n1: nameRet = n2; break;
        case n2: nameRet = n3; break;
        case n3: nameRet = n4; break;
        case n4: nameRet = n1; break;

        case d1: nameRet = d2; break;
        case d2: nameRet = d3; break;
        case d3: nameRet = d4; break;
        case d4: nameRet = d1; break;

        case e1: nameRet = e2; break;
        case e2: nameRet = e1; break;

        case f1: nameRet = f2; break;
        case f2: nameRet = f1; break;

        case g1: nameRet = g1; break;

        case h1: nameRet = h2; break;
        case h2: nameRet = h3; break;
        case h3: nameRet = h4; break;
        case h4: nameRet = h1; break;

        case k1: nameRet = k2; break;
        case k2: nameRet = k1; break;

        case m1: nameRet = m2; break;
        case m2: nameRet = m1; break;
    }

    static const pair<int, int> ddp[8] = {MP(0, 1), MP(0, -1), MP(-1, 0),\
		MP(-1, 1), MP(-1, -1), MP(0, -2), MP(0, -3), MP(0, -4)};

    register int tmpx, tmpy;

    if (!placeJudge(nameRet, nowx, nowy)) {
        for (register int i=0; i^7; ++ i) {
            tmpx = nowx + ddp[i].first,\
			tmpy = nowy + ddp[i].second;
            if (placeJudge(nameRet, tmpx, tmpy)) {
                drawTetris(steins, nowx, nowy, true);
                nowx = tmpx, nowy = tmpy; break;
            }
        }
    } return nameRet;
}

inline void setColor (int color) {
    switch (color % 5) {
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

inline void isCursorDisplay(bool flag) {
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO CursorInfo;
    GetConsoleCursorInfo(handle, &CursorInfo);
    CursorInfo.bVisible = flag;
    SetConsoleCursorInfo(handle, &CursorInfo);
}

inline int qpow (int a, int t) {
    register int base = a, ret = 1;
    while (t) {
        if (t&1) ret = ret * base;
        base = base * base, t >>= 1;
    } return ret;
}

const vector<int> logoMap[5] = {
        {0, 17, 18, 20},
        {1, 2, 5, 11, 14, 17, 19, 21},
        {1, 2, 5, 6, 7, 11, 14, 15, 16, 19, 21, 22, 23, 24},
        {1, 2, 5, 11, 14, 16, 19, 24},
        {0, 0, 1, 3, 4, 9, 10, 12, 13, 15, 16, 18}
};

#define logoStartX (28<<1)
#define logoStartY 3

inline void drawLogo () {
    register int colorOffset = rand();
    for (register int i=0; i^5; ++ i) {
        auto iter = logoMap[i].begin();
        register bool flag = *iter;
        if (!flag) {
            setCursor(logoStartX, logoStartY+i);
            for (register int j=0; j^25; ++ j) {
                setColor(i+j+colorOffset); printf(rand()%3? "□":"■");
            }
        } for (++ iter; iter != logoMap[i].end(); ++ iter) {
            setCursor(logoStartX+(*iter<<1), logoStartY+i);
            setColor(i+((*iter)<<1)+colorOffset);
            printf(flag? (rand()%3? "□":"■"):"  ");
        }
    }
}

inline void ID_generator::addNewElement() {
    for (register int i=0; i^8; ++ i) workQue[i] = (node){i, rand()};
    sort (workQue, workQue + 8);
    for (register int i=0; i^8; ++ i) idQue.push(workQue[i].data);
}

inline void ID_generator::init() {
    while (!idQue.empty()) idQue.pop();
    srand(time(NULL)); addNewElement();
}

inline int ID_generator::getNewID () {
    register int id = idQue.front(); idQue.pop();
    if (idQue.size() <= 8) addNewElement();
    return ptnMap[id].first + (rand() % ptnMap[id].second + ptnMap[id].second) % ptnMap[id].second;
}