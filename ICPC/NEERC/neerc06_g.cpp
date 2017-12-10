#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;

int n, m;
bool vis[1005][2005];
double dp[1005][2005];

double f(int x, int y){
    if(x == n) return 0;
    if(y == m) return 1e9;
    if(vis[x][y]) return dp[x][y];
    vis[x][y] = 1;
    return dp[x][y] = min(f(x+1, y+1) + fabs((10000.0 * x)/n - (10000.0 * y)/m), f(x, y+1));
}

int main(){
    cin >> n >> m;
    m += n;
    printf("%.4f", f(0, 0));
}
