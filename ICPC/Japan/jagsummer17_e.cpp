#include <bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
using lint = long long;
using real_t = double;
const int mod = 1e9 + 7;
const int MAXN = 55;
const lint inf = 2e15;

int n, m;
char str[MAXN][MAXN];
lint dp[MAXN][MAXN][MAXN][MAXN];
lint L[MAXN][MAXN];
lint LB[MAXN][MAXN];
lint R[MAXN][MAXN];
lint RB[MAXN][MAXN];
lint D[MAXN][MAXN];

lint gob(lint x, lint y){
    if(x < 0 || y < 0) return -3;
    if(1.0 * x * y > 1e16) return inf;
    return min(inf, x * y);
}


lint f(int sx, int sy, int ex, int ey){
    if(sx > ex || sy > ey) return -1e9;
    if(~dp[sx][sy][ex][ey]) return dp[sx][sy][ex][ey];
    if(pi(sx, sy) == pi(ex, ey)) return 1;
    if(ex - sx + ey - sy == 2){
        int ret = 0;
        for(int i=sx; i<=ex; i++){
            for(int j=sy; j<=ey; j++){
                if(isdigit(str[i][j])) ret = max(ret, (int)str[i][j] - '0');
            }
        }
        return dp[sx][sy][ex][ey] = ret;
    }
    lint ret = -1e9;
    if(sx < ex-1 && str[ex-2][ey] == '*'){
        ret = max(ret, gob( f(sx, sy, ex-2, ey) , (str[ex-1][ey] - '0')));
    }
    if(sx < ex && sy < ey && str[ex-1][ey-1] == '*'){
        ret = max(ret, gob( f(sx, sy, ex-1, ey-1) , (str[ex-1][ey] - '0')));
        ret = max(ret, gob( f(sx, sy, ex-1, ey-1) , (str[ex][ey-1] - '0')));
    }
    if(sy < ey-1 && str[ex][ey-2] == '*'){
        ret = max(ret, gob( f(sx, sy, ex, ey-2) , (str[ex][ey-1] - '0')));
    }
    return dp[sx][sy][ex][ey] = ret;
}

int main(){
    cin >> n >> m;
    for(int i=0; i<n; i++) cin >> str[i];
    if(n + m == 2){
        cout << str[0] << endl;
        return 0;
    }
    memset(dp, -1, sizeof(dp));
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            L[i][j] = LB[i][j] = -1e9;
            if(i % 2 != j % 2){
                if(i) L[i][j] = max(L[i][j], L[i-1][j]);
                if(j) L[i][j] = max(L[i][j], L[i][j-1]);
                LB[i][j] = L[i][j];
                if(str[i][j] == '+') L[i][j] = -1e9;
            }
            else{
                if(i) L[i][j] = max(L[i][j], L[i-1][j]);
                if(j) L[i][j] = max(L[i][j], L[i][j-1]);
                if(i == 0 && j == 0) L[i][j] = 1;
                L[i][j] = gob(L[i][j], str[i][j] - '0');
                LB[i][j] = L[i][j];
            }
        }
    }
    for(int i=n-1; i>=0; i--){
        for(int j=m-1; j>=0; j--){
            R[i][j] = RB[i][j] = -1e9;
            if(i % 2 != j % 2){
                if(i+1<n) R[i][j] = max(R[i][j], R[i+1][j]);
                if(j+1<m) R[i][j] = max(R[i][j], R[i][j+1]);
                RB[i][j] = R[i][j];
                if(str[i][j] == '+') R[i][j] = -1e9;
            }
            else{
                if(i+1<n) R[i][j] = max(R[i][j], R[i+1][j]);
                if(j+1<m) R[i][j] = max(R[i][j], R[i][j+1]);
                if(pi(i, j) == pi(n-1, m-1)) R[i][j] = 1;
                R[i][j] = gob(R[i][j], str[i][j] - '0');
                RB[i][j] = R[i][j];
            }
        }
    }
    lint ret = L[n-1][m-1];
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            //printf("(%d, %d) = %lld %lld %lld %lld\n",i, j, L[i][j], LB[i][j], R[i][j], RB[i][j]);
            if(str[i][j] != '+') continue;
            D[i][j] = LB[i][j];
            for(int k=0; k<=i; k++){
                for(int l=0; l<=j; l++){
                    if(pi(k, l) == pi(i, j)) continue;
                    if(str[k][l] != '+') continue;
                    D[i][j] = max(D[i][j], D[k][l] + f(k, l, i, j));
                }
            }
            D[i][j] = min(D[i][j], inf);
            ret = max(ret, D[i][j] + RB[i][j]);
        }
    }
    if(ret < 0) assert(0);
    if(ret > 1ll * 100000 * 100000 * 100000){
        ret = -1;
    }
    cout << ret << endl;
}
