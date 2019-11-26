#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> pi;

int n,m;
int a[505][505], col[505][505], piv, ret = 1e9;
int dx[4] = {0,1,0,-1}, dy[4] = {1,0,-1,0};

bool good(int x, int y){
    return x >= 0 && x < n && y >= 0 && y < m;
}

void bfs(int x, int y, int c){
    queue<int> qx, qy;
    qx.push(x);
    qy.push(y);
    col[x][y] = c;
    while (!qx.empty()) {
        x = qx.front();
        y = qy.front();
        qx.pop();
        qy.pop();
        for (int i=0; i<4; i++) {
            if(good(x + dx[i],y + dy[i]) && col[x+dx[i]][y+dy[i]] == 0 && a[x][y] == a[x+dx[i]][y+dy[i]]){
                qx.push(x+dx[i]);
                qy.push(y+dy[i]);
                col[x+dx[i]][y+dy[i]] = c;
            }
        }
    }
}

vector<int> graph[505];

bool vis[505], vis2[505];
int que[505], dep[505];

void f(int x){
    int fr = 0, sz = 0;
    que[sz] = x;
    dep[sz] = 0;
    sz++;
    memset(vis,0,sizeof(vis));
    vis[x] = 1;
    int maxp = 0;
    while (fr < sz) {
        x = que[fr];
        int df = dep[fr];
        fr++;
        maxp = df;
        if(df >= ret) return;
        for (int i=0; i<graph[x].size(); i++) {
            if(!vis[graph[x][i]]){
                que[sz] = graph[x][i];
                dep[sz] = df + 1;
                sz++;
                vis[graph[x][i]] = 1;
            }
        }
    }
    ret = maxp;
}

int main(){
    scanf("%d %d",&n,&m);
    for (int i=0; i<n; i++) {
        string s; cin >> s;
        for (int j=0; j<m; j++) {
            a[i][j] = (s[j] == '.' ? 1 : 0);
        }
    }
    for (int i=0; i<n; i++) {
        for (int j=0; j<m; j++) {
            if(!col[i][j]){
                bfs(i,j,++piv);
            }
        }
    }
    for (int i=0; i<n; i++) {
        for (int j=0; j<m; j++) {
            if(i+1 < n && col[i][j] != col[i+1][j]){
                int px = col[i][j];
                int py = col[i+1][j];
                graph[px].push_back(py);
                graph[py].push_back(px);
            }
            if(j+1 < m && col[i][j] != col[i][j+1]){
                int px = col[i][j];
                int py = col[i][j+1];
                graph[px].push_back(py);
                graph[py].push_back(px);
            }
        }
    }
    for(int i=1; i<=piv; i++) f(i);
    printf("%d",ret);
}
