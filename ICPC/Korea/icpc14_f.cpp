#include <cstdio>

int n,a[1005];
int vis[1005];

int get_comp(int x){
    int res = 0;
    while (!vis[x]) {
        vis[x] = 1;
        x = a[x];
        res++;
    }
    return res;
}

void solve(){
    scanf("%d",&n);
    for (int i=1; i<=n; i++) {
        vis[i] = 0;
        scanf("%d",&a[i]);
    }
    int res = 0;
    for (int i=1; i<=n; i++) {
        int r = get_comp(i);
        if(r) res++;
    }
    printf("%d\n",res);
}

int main(){
    int t;
    scanf("%d",&t);
    while (t--) {
        solve();
    }
}