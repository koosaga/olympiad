#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <limits.h>
#include <math.h>
#include <time.h>
#include <iostream>
#include <functional>
#include <numeric>
#include <algorithm>
#include <stack>
#include <queue>
#include <deque>
#include <vector>
#include <string>
#include <bitset>
#include <map>
#include <set>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;
const int dx[4] = {1, 0, 0, -1}, dy[4] = {0, 1, -1, 0};

struct node1{
    int x, y, dist;
};

struct node2{
    int x, y, dir, dist;
    bool operator>(const node2 &p)const{
        return dist > p.dist;
    }
};

int n, m;
char s[55][55];

int bfs(pi st, pi ed, pi b){
    int sx = st.first;
    int sy = st.second;
    int ex = ed.first;
    int ey = ed.second;
    int bx = b.first;
    int by = b.second;
    bool vis[55][55] = {};
    queue<node1> que;
    vis[sx][sy] = 1;
    que.push({sx, sy, 0});
    auto ok = [&](int x, int y){
        if(x < 0 || x >= n || y < 0 || y >= m) return 0;
        if(bx <= x && x <= bx + 1 && by <= y && y <= by+1) return 0;
        if(s[x][y] == '*' || vis[x][y]) return 0;
        return 1;
    };
    while(!que.empty()){
        auto f = que.front();
        if(f.x == ex && f.y == ey) return f.dist;
        que.pop();
        for(int i=0; i<4; i++){
            if(ok(f.x + dx[i], f.y + dy[i])){
                vis[f.x + dx[i]][f.y + dy[i]] = 1;
                que.push({f.x + dx[i], f.y + dy[i], f.dist + 1});
            }
        }
    }
    return 1e9;
}

int solve(int x, int y){
    if(x == 0 && y == 0) return 0;
    bool vis[55][55][4] = {};
    priority_queue<node2, vector<node2>, greater<node2> > pq;
    auto ok = [&](int x, int y){
        if(x < 0 || x >= n || y < 0 || y >= m) return 0;
        if(s[x][y] == '*') return 0;
        return 1;
    };
    vector<pi> hole;
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            if(s[i][j] == '.') hole.emplace_back(i, j);
        }
    }
    if(ok(x+2, y) && ok(x+2, y+1)){
        int ret = 1e9;
        for(int i=0; i<2; i++){
            reverse(hole.begin(), hole.end());
            ret = min(ret, bfs(pi(x+2, y), hole[0], pi(x, y)) + bfs(pi(x+2, y+1), hole[1], pi(x, y)));
        }
        if(ret < 1e8) pq.push({x, y, 0, ret});
    }
    if(ok(x, y+2) && ok(x+1, y+2)){
        int ret = 1e9;
        for(int i=0; i<2; i++){
            reverse(hole.begin(), hole.end());
            ret = min(ret, bfs(pi(x, y+2), hole[0], pi(x, y)) + bfs(pi(x+1, y+2), hole[1], pi(x, y)));
        }
        if(ret < 1e8) pq.push({x, y, 1, ret});
    }
    if(ok(x, y-1) && ok(x+1, y-1)){
        int ret = 1e9;
        for(int i=0; i<2; i++){
            reverse(hole.begin(), hole.end());
            ret = min(ret, bfs(pi(x, y-1), hole[0], pi(x, y)) + bfs(pi(x+1, y-1), hole[1], pi(x, y)));
        }
        if(ret < 1e8) pq.push({x, y, 2, ret});
    }
    if(ok(x-1, y) && ok(x-1, y+1)){
        int ret = 1e9;
        for(int i=0; i<2; i++){
            reverse(hole.begin(), hole.end());
            ret = min(ret, bfs(pi(x-1, y), hole[0], pi(x, y)) + bfs(pi(x-1, y+1), hole[1], pi(x, y)));
        }
        if(ret < 1e8) pq.push({x, y, 3, ret});
    }
    while(!pq.empty()){
        auto t = pq.top();
        pq.pop();
        if(vis[t.x][t.y][t.dir]) continue;
        if(t.x == 0 && t.y == 0) return t.dist;
        vis[t.x][t.y][t.dir] = 1;
        pq.push({t.x + dx[t.dir], t.y + dy[t.dir], 3 - t.dir, t.dist + 1});
        vector<pi> pnt[4];
        if(ok(t.x+2, t.y) && ok(t.x+2, t.y+1)){
            pnt[0].emplace_back(t.x+2, t.y);
            pnt[0].emplace_back(t.x+2, t.y+1);
        }
        if(ok(t.x, t.y+2) && ok(t.x+1, t.y+2)){
            pnt[1].emplace_back(t.x, t.y+2);
            pnt[1].emplace_back(t.x+1, t.y+2);
        }
        if(ok(t.x, t.y-1) && ok(t.x+1, t.y-1)){
            pnt[2].emplace_back(t.x, t.y-1);
            pnt[2].emplace_back(t.x+1, t.y-1);
        }
        if(ok(t.x-1, t.y) && ok(t.x-1, t.y+1)){
            pnt[3].emplace_back(t.x-1, t.y);
            pnt[3].emplace_back(t.x-1, t.y+1);
        }
        for(int i=0; i<4; i++){
            if(t.dir == i) continue;
            if(pnt[i].empty()) continue;
            int dist = 1e9;
            for(int j=0; j<2; j++){
                dist = min(dist, bfs(pnt[t.dir][j], pnt[i][0], pi(t.x, t.y)) + 
                    bfs(pnt[t.dir][j^1], pnt[i][1], pi(t.x, t.y)));
            }
            if(dist < 1e8) pq.push({t.x, t.y, i, dist + t.dist});
        }
    }
    return -1;
}

int main(){
    while(1){
        cin >> n >> m;
        if(n + m == 0) break;
        for(int i=0; i<n; i++){
            cin >> s[i];
        }
        int cpx = -1, cpy = -1;
        for(int i=0; i<n; i++){
            for(int j=0; j<m; j++){
                if(s[i][j] == 'X'){
                    cpx = i;
                    cpy = j;
                    break;
                }
            }
            if(~cpx) break;
        }
        cout << solve(cpx, cpy) << endl;
    }
}