#include <bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
using lint = long long;
const int mod = 1e9 + 7;
const int MAXN = 10005;

int n;
vector<int> gph[MAXN];
int V[4], dist[4][MAXN];
int pos[105][105];

int D(int sx, int sy, int ex, int ey){ return abs(ex - sx) + abs(ey - sy); }

void bfs(int x){
    queue<int> que;
    dist[x][V[x]] = 0;
    que.push(V[x]);
    while(!que.empty()){
        int v = que.front();
        que.pop();
        for(auto &i : gph[v]){
            if(dist[x][i] > dist[x][v] + 1){
                dist[x][i] = dist[x][v] + 1;
                que.push(i);
            }
        }
    }
}

int main(){
    scanf("%d",&n);
    for(int i=0; i<2*n*n-2*n; i++){
        int x, y; scanf("%d %d",&x,&y);
        gph[x].push_back(y);
        gph[y].push_back(x);
    }
    memset(dist, 0x3f, sizeof(dist));
    for(int i=1; i<=n*n; i++){
        if(gph[i].size() == 2){
            V[0] = i;
            bfs(0);
            for(int j=1; j<=n*n; j++){
                if(dist[0][j] == 2 * n - 2){
                    assert(!V[3]);
                    V[3] = j;
                }
            }
            break;
        }
    }
    for(int i=1; i<=n*n; i++){
        if(gph[i].size() == 2 && i != V[0] && i != V[3]){
            if(!V[1]) V[1] = i;
            else V[2] = i;
        }
    }
    for(int i=1; i<4; i++) bfs(i);
    for(int i=1; i<=n*n; i++){
        for(int j=1; j<=n; j++){
            for(int k=1; k<=n; k++){
                if(D(1, 1, j, k) == dist[0][i] && D(1, n, j, k) == dist[1][i] && D(n, 1, j, k) == dist[2][i] && D(n, n, j, k) == dist[3][i]){
                    pos[j][k] = i;
                }
            }
        }
    }
    for(int i=1; i<=n; i++){
        for(int j=1; j<=n; j++){
            printf("%d ", pos[i][j]);
        }
        puts("");
    }
}
