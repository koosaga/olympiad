#include "coprobber.h"
#include <cstdio>
#include <queue>
#include <algorithm>
#include <cstring>
using namespace std;
int indeg[500][500][2];
 
queue<int> qx, qy, qd;
bool vis[500][500][2];
int nxt[500][500];
int pos;
 
int start(int N, bool A[MAX_N][MAX_N])
{
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            if (i == j) continue;
            indeg[i][j][1] = count(A[j], A[j] + N, 1);
            indeg[i][j][0] = 1;
        }
    }
    for (int i = 0; i < N; i++){
        for (int k = 0; k < 2; k++){
            qx.push(i);
            qy.push(i);
            qd.push(k);
            vis[i][i][k] = 1;
        }
    }
    while (!qx.empty()){
        int xf = qx.front();
        int yf = qy.front();
        int df = qd.front();
        qx.pop(), qy.pop(), qd.pop();
        if (df == 1){
            for (int i = 0; i < N; i++){
                if ((xf == i || A[xf][i]) && !vis[i][yf][0]){
                    indeg[i][yf][0]--;
                    if (indeg[i][yf][0] == 0){
                        qx.push(i);
                        qy.push(yf);
                        qd.push(0);
                        nxt[i][yf] = xf;
                        vis[i][yf][0] = 1;
                    }
                }
            }
        }
        else{
            for (int i = 0; i < N; i++){
                if (A[yf][i] &&!vis[xf][i][1]){
                    indeg[xf][i][1]--;
                    if (indeg[xf][i][1] == 0){
                        qx.push(xf);
                        qy.push(i);
                        qd.push(1);
                        vis[xf][i][1] = 1;
                    }
                }
            }
        }
    }
    for (int i = 0; i < N; i++){
        int fnd = 0;
        for (int j = 0; j < N; j++){
            if (!vis[i][j][0]){
                fnd = 1;
                break;
            }
        }
        if (!fnd) return pos = i;
    }
    return -1;
}
 
int nextMove(int R)
{
    return pos = nxt[pos][R];
}