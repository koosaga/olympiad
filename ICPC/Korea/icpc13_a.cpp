#include <cstdio>

int a[101][101],n,m;

void solve(){
    scanf("%d %d",&m,&n);
    for (int i=0; i<m; i++) {
        for (int j=0; j<n; j++) {
            scanf("%d",&a[i][j]);
        }
    }
    int res = 0;
    for (int i=0; i<n; i++) {
        int cnt = 0;
        for (int j=m-1; j>=0; j--) {
            if(a[j][i]){
                res += (m-1-j) - cnt;
                cnt++;
            }
        }
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