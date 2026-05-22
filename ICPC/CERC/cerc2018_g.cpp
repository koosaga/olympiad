#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1005;
using lint = long long;

struct disj{
    int pa[5000005];
    void init(int n){
        iota(pa, pa + n + 1, 0);
    }
    int find(int x){
        return pa[x] = (pa[x] == x ? x : find(pa[x]));
    }
    bool uni(int p, int q){
        p = find(p);
        q = find(q);
        if(p == q) return 0;
        pa[q] = p; return 1;
    }
}disj;

int nxt[55][100005];
int chk[5000005];

int find_nxt(int r, int x){
    return nxt[r][x] = (nxt[r][x] == x ? x : find_nxt(r, nxt[r][x]));
}

int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};
bool ok(int x, int y){
    return x >= 0 && x < 50 && y >= 0 && y < 100000;
}

int get(int x, int y){ return x * 100000 + y; }

void activate(int x, int y){
    chk[get(x, y)] = 1;
    for(int i=0; i<4; i++){
        if(ok(x + dx[i], y + dy[i])){
            int p = get(x + dx[i], y + dy[i]);
            if(chk[p]) disj.uni(get(x, y), p);
        }
    }
}

int main(){
    disj.init(5000000);
    for(int i=0; i<50; i++){
        for(int j=0; j<=100000; j++) nxt[i][j] = j;
    }
    int q; scanf("%d",&q);
    while(q--){
        int t; scanf("%d",&t);
        int sx, sy; scanf("%d %d",&sx,&sy);
        int ex, ey; scanf("%d %d",&ex,&ey);
        sx--, sy--; ex--; ey--;
        if(t == 0){
            if(sx > ex) swap(sx, ex);
            if(sy > ey) swap(sy, ey);
            for(int i=sx; i<=ex; i++){
                int l = find_nxt(i, sy);
                while(l <= ey){
                    activate(i, l);
                    nxt[i][l] = find_nxt(i, l + 1);
                    l = find_nxt(i, l);
                }
            }
        }
        if(t == 1){
            int l = get(sx, sy);
            int r = get(ex, ey);
            if(chk[l] && chk[r] && disj.find(l) == disj.find(r)) puts("1");
            else puts("0");
        }
    }
}