#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using llf = long double;
using pi = pair<lint, lint>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXN = 696;
const int mod = 998244353; // cringe prime

int n, m;
bool vis[MAXN][MAXN];

pi a[MAXN];
bool f(int x, int y){
    if(x > n || y > m) return 0;
    if(x == n && y == m) return 1;
    if(vis[x][y]) return 0;
    vis[x][y] = 1;
    if(~a[x+y+1].first && a[x+y+1].first != x) return 0;
    if(~a[x+y+1].second && a[x+y+1].second != y) return 0;
    if(~a[x+y+1].first) return f(x+1, y);
    if(~a[x+y+1].second) return f(x, y+1);
    if(f(x+1, y)){
        a[x+y+1].first = x;
        return 1;
    }
    if(f(x, y + 1)){
    a[x+y+1].second = y;
    return 1;
    }
    return 0;
}

int main(){
    cin >> n >> m;
    fill(a, a + n + m + 2, pi(-1, -1));
    for(int i = 0; i < n; i++){
        int x; cin >> x;
        if(x) a[x].first = i;
    }
    for(int i = 0; i < m; i++){
        int x; cin >> x;
        if(x) a[x].second = i;
    }
    assert(f(0, 0));
    for(int i = 0; i < n; i++){
        for(int j = 1; j <= n+m; j++){
            if(a[j].first == i) printf("%d ", j);
        }
    }
    puts("");
    for(int i = 0; i < m; i++){
        for(int j = 1; j <= n+m; j++){
            if(a[j].second == i) printf("%d ", j);
        }
    }
    puts("");
}
