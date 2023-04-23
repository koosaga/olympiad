#include <cstdio>
#include <algorithm>
using namespace std;

int n, k, m;
int arr[2505][2505];
int nxt[2505][2505];

struct bit{
    int tree[270000], lim;
    void init(int n){
        for(lim = 1; lim <= n; lim <<= 1);
    }
    void add(int x, int v){
        x += lim;
        tree[x] += v;
        while(x > 1){
            x >>= 1;
            tree[x] = tree[2*x] + tree[2*x+1];
        }
    }
    int q(int s, int e){
        s += lim;
        e += lim;
        int ret = 0;
        while(s < e){
            if(s%2 == 1) ret += tree[s++];
            if(e%2 == 0) ret += tree[e--];
            s >>= 1;
            e >>= 1;
        }
        if(s == e) ret += tree[s];
        return ret;
    }
}bit;

int find(int x, int y){
    return nxt[x][y] = (nxt[x][y] == y ? y : find(x, nxt[x][y]));
}
int main(){
    scanf("%d %d %d",&n,&k,&m);
    for(int i=0; i<m; i++){
        int q, x[4], y[4];
        scanf("%d",&q);
        for(int j=0; j<q; j++){
            scanf("%d %d",&x[j],&y[j]);
        }
        for(int j=1; j<(1<<q); j++){
            int popcnt = 0;
            int sx = 1, ex = n-k+1, sy = 1, ey = n-k+1;
            for(int l=0; l<q; l++){
                if((j >> l) & 1){
                    popcnt++;
                    sx = max(sx, x[l] - k + 1);
                    ex = min(ex, x[l]);
                    sy = max(sy, y[l] - k + 1);
                    ey = min(ey, y[l]);
                }
            }
            if(sx > ex || sy > ey) continue;
            if(popcnt & 1){
                arr[sx][sy]++;
                arr[sx][ey+1]--;
                arr[ex+1][sy]--;
                arr[ex+1][ey+1]++;
            }
            else{
                arr[sx][sy]--;
                arr[sx][ey+1]++;
                arr[ex+1][sy]++;
                arr[ex+1][ey+1]--;
            }
        }
    }
    bit.init(m);
    for(int i=1; i<=n-k+1; i++){
        for(int j=1; j<=n-k+1; j++){
            arr[i][j] += arr[i][j-1];
        }
    }
    for(int i=1; i<=n-k+1; i++){
        for(int j=1; j<=n-k+1; j++){
            arr[i][j] += arr[i-1][j];
            bit.add(arr[i][j], 1);
            nxt[i][j] = j;
        }
        nxt[i][n-k+2] = n-k+2;
    }
    int q;
    scanf("%d",&q);
    while(q--){
        int typ;
        scanf("%d",&typ);
        if(typ == 1){
            int x, y;
            scanf("%d %d",&x,&y);
            for(int i=max(x - k + 1, 1); i<=min(x, n - k + 1); i++){
                int pos = find(i, max(y - k + 1, 1));
                int end = min(y, n - k + 1);
                while(pos <= end){
                    pos = find(i, pos);
                    bit.add(arr[i][pos], -1);
                    arr[i][pos] = 0;
                    nxt[i][pos] = find(i, pos + 1);
                    pos = nxt[i][pos];
                }
            }
        }
        else{
            int t;
            scanf("%d",&t);
            printf("%.5lf\n",bit.q(t, m) / (1.0 * (n - k + 1) * (n - k + 1)));
        }
    }
}