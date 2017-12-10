#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pi;

int n, m;
char str[1555][1555];
int max_rad[1555][1555], a[1555][1555];
int apth[1555][1555], bpth[1555][1555];

int gs(int s, int e, int s2, int e2){
    return a[s2][e2] - a[s-1][e2] - a[s2][e-1] + a[s-1][e-1];
}

int geta(int x, int y){
    if(x < 0 || y < 0) return 0;
    return apth[x][y];
}

int nulbbya(int x, int y, int d){
    return geta(x, y) - geta(x - d, y) - geta(x, y - d) + geta(x - d, y - d);
}

int getb(int x, int y){
    if(x < 0 || y < 0) return 0;
    return bpth[x][y];
}

int nulbbyb(int x, int y, int d){
    return getb(x, y) - getb(x - d, y) - getb(x, y - d) + getb(x - d, y - d);
}

int solve(int x, int y){
    if(str[x][y] == '#') return 1e9;
    auto trial = [&](const int d){
        int p1 = nulbbya(x+1, y+1, d+2);
        int p2 = nulbbyb(x+1, y+1, d+2);
        return p1 > 0 && p2 > 0;
    };
    int s = 0, e = max_rad[x][y];
    while(s != e){
        int m = (s+e)/2;
        if(trial(m)) e = m;
        else s = m+1;
    }
    if(!trial(s)) return 1e9;
    return s;
}

void dfs(int t, int x, int y){
    if(str[x][y] != '#') return;
    queue<pi> que;
    que.push(pi(x, y));
    while(!que.empty()){
        auto p = que.front();
        que.pop();
        if(str[p.first][p.second] != '#') continue;
        if(t == 0){
            if(apth[p.first][p.second]) continue;
            apth[p.first][p.second] = 1;
        }
        else{
            if(bpth[p.first][p.second]) continue;
            bpth[p.first][p.second] = 1;
        }
        int x = p.first, y = p.second;
        for(int i=-1; i<=1; i++){
            for(int j=-1; j<=1; j++){
                if(i == 0 && j == 0) continue;
                if(x == 1 && y == 0 && x + i == 0 && y + j == 1) continue;
                if(x == 0 && y == 1 && x + i == 1 && y + j == 0) continue;
                if(x == n+1 && y == m && x + i == n && y + j == m+1) continue;
                if(x == n && y == m+1 && x + i == n+1 && y + j == m) continue;
                if(x + i < 0 || y + j < 0 || x + i > n+1 || y + j > m+1){
                    continue;
                }
                que.push(pi(x+i, y+j));
            }
        }
    }
}

int main(){
    scanf("%d %d",&m,&n);
    for(int i=1; i<=n; i++){
        scanf("%s", str[i] + 1);
        for(int j=1; j<=m; j++){
            if(str[i][j] == '.') a[i][j]++;
        }
    }
    for(int i=0; i<=n+1; i++){
        for(int j=0; j<=m+1; j++){
            if(i == 0 || i == n+1 || j == 0 || j == m+1){
                str[i][j] = '#';
            }
        }
    }
    str[0][0] = str[n+1][m+1] = '.';
    for(int i=1; i<=n; i++){
        for(int j=1; j<=m; j++){
            a[i][j] += a[i-1][j] + a[i][j-1] - a[i-1][j-1];
            if(str[i][j] == '#') continue;
            if(i == 1 && j == 1) continue;
            if(i == n && j == m) continue;
            int s = 1, e = min(i, j);
            if(i == j) e--;
            while(s != e){
                int m = (s+e+1)/2;
                if(gs(i - m + 1, j - m + 1, i, j) == m * m) s = m;
                else e = m-1;
            }
            max_rad[i][j] = s;
        }
    }
    dfs(1, 0, m+1);
    dfs(0, n+1, 0);
    for(int i=0; i<=n+1; i++){
        for(int j=0; j<=m+1; j++){
            apth[i][j] += (i ? apth[i-1][j] : 0) + (j ? apth[i][j-1] : 0) - (i && j ? apth[i-1][j-1] : 0);
            bpth[i][j] += (i ? bpth[i-1][j] : 0) + (j ? bpth[i][j-1] : 0) - (i && j ? bpth[i-1][j-1] : 0);
        }
    }

    int ret = 1e9;
    int px, py;
    for(int i=1; i<=n; i++){
        for(int j=1; j<=m; j++){
            if(i == 1 && j == 1) continue;
            if(i == n && j == m) continue;
            int w = solve(i, j);
            if(ret > w){
                ret = w;
                px = i, py = j;
            }
        }
    }
    if(ret > 1e6){
        cout << "Impossible";
        return 0;
    }
    else printf("%d %d %d", ret, py - ret + 1, px - ret + 1);
}

