#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int mod = 1e9 + 7;
const int dx[4] = {-1, 0, 1, 0};
const int dy[4] = {0, 1, 0, -1};
const int MAXN = 1005;
int n, m, vis[MAXN];
vector<int> v[MAXN];

int main(){
    scanf("%d %d",&n,&m);
    for(int i=0; i<n; i++){
        int x; scanf("%d",&x);
        v[i].resize(x);
        for(auto &j : v[i]) scanf("%d",&j), vis[j] = 1;
    }
    if(count(vis + 1, vis + m + 1, 0)){
        puts("NO");
        return 0;
    }
    puts("YES");
    for(int i=1; i<=n; i++) printf("%d ", i);
    puts("");
    memset(vis, 0, sizeof(vis));
    for(int i=n-1; i>=0; i--){
        for(auto &j : v[i]){
            if(!vis[j]){
                vis[j] = i + 1;
            }
        }
    }
    for(int i=1; i<=m; i++) printf("%d ", vis[i]);
}
