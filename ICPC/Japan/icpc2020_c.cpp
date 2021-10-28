#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using llf = long double;
using pi = pair<int, int>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXN = 100005;
const int mod = 1e9 + 7;
const int dx[4] = {1, 0, -1, 0};
const int dy[4] = {0, 1, 0, -1};

struct instr{
    int type;
    int l;
};

int n, m, sx, sy;
char str[12][12];
vector<instr> v, cur;

bool ok(int x, int y){
    return x >= 0 && x < n && y >= 0 && y < m && str[x][y] != '#';
}

bool vis[12][12][4][10];

bool good(){
    memset(vis, 0, sizeof(vis));
    int x = sx, y = sy, d = 0, pc = 0;
    while(!vis[x][y][d][pc]){
        vis[x][y][d][pc] = 1;
        if(str[x][y] == 'G') return 1;
        switch (cur[pc].type) {
            case 0:
            {
                pc = cur[pc].l - 1;
                break;
            }
            case 1:
            {
                if(ok(x + dx[d], y + dy[d])){
                    pc = cur[pc].l - 1;
                }
                else{
                    pc = (pc + 1) % sz(cur);
                }
                break;
            }
            case 2:
            {
                if(ok(x + dx[d], y + dy[d])){
                    x += dx[d];
                    y += dy[d];
                }
                pc = (pc + 1) % sz(cur);
                break;
            }
            case 3:
            {
                d = (d + 1) % 4;
                pc = (pc + 1) % sz(cur);
                break;
            }
            case 4:
            {
                d = (d + 3) % 4;
                pc = (pc + 1) % sz(cur);
                break;
            }
            default:
            {
                assert(0);
            }
        };
    }
    return 0;
}

void bktk(int pos, int tot){
    if(pos == tot){
        if(good()){
            cout << sz(cur) << endl;
            for(auto &i : cur){
                if(i.type == 0) printf("GOTO %d\n", i.l);
                if(i.type == 1) printf("IF-OPEN %d\n", i.l);
                if(i.type == 2) printf("FORWARD\n");
                if(i.type == 3) printf("LEFT\n");
                if(i.type == 4) printf("RIGHT\n");
            }
            exit(0);
        }
        return;
    }
    for(auto &j : v){
        cur.push_back(j);
        bktk(pos + 1, tot);
        cur.pop_back();
    }
}

int main(){
    cin >> n >> m;
    for(int i = 0; i < n; i++){
        cin >> str[i];
        for(int j = 0; j < m; j++){
            if(str[i][j] == 'S') sx = i, sy = j;
        }
    }
    for(int i = 1; ; i++){
        v.clear();
        for(int j = 1; j <= i; j++){
            v.push_back({0, j});
            v.push_back({1, j});
        }
        v.push_back({2, 0});
        v.push_back({3, 0});
        v.push_back({4, 0});
        bktk(0, i);
    }
}
