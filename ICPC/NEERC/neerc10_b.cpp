#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
const int MAXN = 100005;

int nxt[10][10][60];
lint pwr[20];

int op(int x, int y, lint k){
    if(x == -1){
        if(k == 1) return y;
        return op(y, y, k-1);
    }
    for(int i=0; i<60; i++){
        if((k >> i) & 1) x = nxt[x][y][i];
    }
    return x;
}

int ans[22];

void solve(lint s, lint e, int d){
    lint sv = s / pwr[d];
    lint ev = e / pwr[d];
    if(sv / 10 == ev / 10){
        vector<int> v;
        int cur = -1;
        while(sv <= ev){
            lint st = sv * pwr[d];
            lint ed = (sv + 1) * pwr[d];
            st = max(st, s);
            ed = min(ed, e + 1);
            if(st < ed) cur = op(cur, sv % 10, ed - st);
            sv++;
        }
        ans[d] = cur;
        return;
    }
    int cur = -1;
    for(int i=0; i<10; i++){
        lint st = ((sv / 10) * 10 + i) * pwr[d];
        lint ed = ((sv / 10) * 10 + i + 1) * pwr[d];
        st = max(st, s);
        ed = min(ed, e + 1);
        if(st < ed) cur = op(cur, i, ed - st);
    }
    lint gap = ev/10 - sv/10 - 1;
    if(gap > 0){
        int nxt[60][10] = {};
        for(int i=0; i<10; i++){
            int cur = i;
            for(int j=0; j<10; j++){
                cur = op(cur, j, pwr[d]);
            }
            nxt[0][i] = cur;
        }
        for(int i=1; i<60; i++){
            for(int j=0; j<10; j++){
                nxt[i][j] = nxt[i-1][nxt[i-1][j]];
            }
        }
        for(int i=0; i<60; i++){
            if((gap >> i) & 1){
                cur = nxt[i][cur];
            }
        }
    }
    for(int i=0; i<10; i++){
        lint st = ((ev / 10) * 10 + i) * pwr[d];
        lint ed = ((ev / 10) * 10 + i + 1) * pwr[d];
        st = max(st, s);
        ed = min(ed, e + 1);
        if(st < ed) cur = op(cur, i, ed - st);
    }
    ans[d] = cur;
}

int main(){
    pwr[0] = 1;
    for(int i=1; i<=18; i++) pwr[i] = pwr[i-1] * 10;
    for(int i=0; i<10; i++){
        for(int j=0; j<10; j++){
            cin >> nxt[i][j][0];
        }
    }
    for(int i=1; i<60; i++){
        for(int j=0; j<10; j++){
            for(int k=0; k<10; k++){
                nxt[j][k][i] = nxt[nxt[j][k][i-1]][k][i-1];
            }
        }
    }
    lint s, e;
    cin >> s >> e;
    for(int i=18; i>=0; i--){
        if(e < pwr[i]) continue;
        solve(s, e, i);
    }
    int ok = 18;
    while(ok && !ans[ok]) ok--;
    for(int i=ok; i>=0; i--) printf("%d", ans[i]);
}
