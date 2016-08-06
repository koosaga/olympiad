#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<lint, lint> pi;

int a[1005], n, seat[1005];
bool vis[1005];

bool Do(int x){
    for(int i=2; i<=n; i++){
        if(i <= x) seat[i] = i-1;
        else seat[i] = i;
    }
    memset(vis, 0, sizeof(vis));
    vis[a[1]] = 1;
    for(int i=2; i<=n; i++){
        if(!vis[seat[i]] && seat[i] != a[i]){
            return 0;
        }
        vis[a[i]] = 1;
    }
    return 1;
}

void solve(){
    scanf("%d",&n);
    for(int i=1; i<=n; i++){
        scanf("%d",&a[i]);
    }
    int cnt = 0, pos = -1;
    for(int i=1; i<=n; i++){
        if(Do(i)){
            pos = i;
            cnt++;
        }
    }
    if(cnt == 1) printf("%d\n", pos);
    else puts("0");
}

int main(){
    int t;
    cin >> t;
    while(t--){
        solve();
    }
}

