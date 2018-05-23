#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;
const int dx[4] = {1, 0, -1, 0}, dy[4] = {0, 1, 0, -1};

int d1[301][301];
int d2[301][301];
int idx[301][301];
vector<pi> v[45001];

int n;
char str[301][301];

bool ok(int x, int y){
    return x >= 0 && x < n && y >= 0 && y < n && str[x][y] != '#';
}

bool fa(int sx, int sy, int idx);
bool fb(int sx, int sy, int idx);

char dp1[301][301][601];
char dp2[301][301][601];

bool fa(int sx, int sy, int idx){
    int ex = v[d1[sx][sy]][idx].first;
    int ey = v[d1[sx][sy]][idx].second;
    if(str[ex][ey] == 'A') return 0;
    char &ret = dp1[sx][sy][idx];
    if(~ret) return ret;
    ret = 0;
    for(int i=0; i<4; i++){
        if(!ok(sx + dx[i], sy + dy[i]) || d1[sx + dx[i]][sy + dy[i]] <= d1[sx][sy]){
            continue;
        }
        if(sx + dx[i] == ex && sy + dy[i] == ey){
            for(int j=0; j<4; j++){
                if(ok(ex + dx[j], ey + dy[j]) && d1[ex][ey] > d2[ex + dx[j]][ey + dy[j]]){
                    ret = 1;
                }
            }
        }
        if(!fb(sx + dx[i], sy + dy[i], idx)){
            ret = 1;
            break;
        }
    }
    return dp1[sx][sy][idx] = ret;
}

bool fb(int sx, int sy, int idx){
    int ex = v[d1[sx][sy]-1][idx].first;
    int ey = v[d1[sx][sy]-1][idx].second;
    if(str[sx][sy] == 'B') return 0;
    char &ret = dp2[sx][sy][idx];
    if(~ret) return ret;
    ret = 0;
    for(int i=0; i<4; i++){
        if(!ok(ex + dx[i], ey + dy[i]) || d2[ex + dx[i]][ey + dy[i]] <= d2[ex][ey]){
            continue;
        }
        if(ex + dx[i] == sx && ey + dy[i] == sy){
            for(int j=0; j<4; j++){
                if(ok(sx + dx[j], sy + dy[j]) && d2[sx][sy] > d1[sx + dx[j]][sy + dy[j]]){
                    ret = 1;
                }
            }
        }
        else{
            int rvp = ::idx[ex + dx[i]][ey + dy[i]];
            if(!fa(sx, sy, rvp)){
                ret = 1;
                break;
            }
        }
    }
    return ret;
}

int main(){
    int t;
    scanf("%d",&t);
    while(t--){
        cin >> n;
        for(int i=0; i<n; i++) cin >> str[i];
        memset(dp1, -1, sizeof(dp1));
        memset(dp2, -1, sizeof(dp2));
        memset(d1, 0x3f, sizeof(d1));
        memset(d2, 0x3f, sizeof(d2));
        memset(idx, 0, sizeof(idx));
        int sx = -1, sy = -1, ex = -1, ey = -1;
        queue<pi> que;
        for(int i=0; i<n; i++){
            for(int j=0; j<n; j++){
                if(str[i][j] == 'A'){
                    sx = i, sy = j;
                    d1[i][j] = 0;
                    que.push(pi(i, j));
                    while(!que.empty()){
                        pi t = que.front();
                        que.pop();
                        int x = t.first, y = t.second;
                        for(int i=0; i<4; i++){
                            if(ok(x + dx[i], y + dy[i]) && d1[x + dx[i]][y + dy[i]] > d1[x][y] + 1){
                                que.push(pi(x + dx[i], y + dy[i]));
                                d1[x + dx[i]][y + dy[i]] = d1[x][y] + 1;
                            }
                        }
                    }
                }
                if(str[i][j] == 'B'){
                    ex = i, ey = j;
                    d2[i][j] = 0;
                    que.push(pi(i, j));
                    while(!que.empty()){
                        pi t = que.front();
                        que.pop();
                        int x = t.first, y = t.second;
                        for(int i=0; i<4; i++){
                            if(ok(x + dx[i], y + dy[i]) && d2[x + dx[i]][y + dy[i]] > d2[x][y] + 1){
                                que.push(pi(x + dx[i], y + dy[i]));
                                d2[x + dx[i]][y + dy[i]] = d2[x][y] + 1;
                            }
                        }
                    }
                }
            }
        }
        for(int i=0; i<45000; i++) v[i].clear();
        for(int i=0; i<n; i++){
            for(int j=0; j<n; j++){
                if(d2[i][j] < 45000) v[d2[i][j]].push_back(pi(i, j));
            }
        }
        for(int i=0; i<45000; i++){
            for(int j=0; j<v[i].size(); j++){
                idx[v[i][j].first][v[i][j].second] = j;
            }
        }
        puts(fa(sx, sy, idx[ex][ey]) ? "A" : "B");
    }
}

