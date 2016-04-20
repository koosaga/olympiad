#include <cstdio>

int n, ban[3005][3005];
int cnt[3005];
int conn[3005];
int main(){
    int m,p,q,r,s;
    scanf("%d %d",&n,&m);
    for (int i=0; i<m; i++) {
        scanf("%d %d %d %d",&p,&q,&r,&s);
        ban[p][r]++;
        ban[p][s+1]--;
        ban[q+1][r]--;
        ban[q+1][s+1]++;
    }
    for (int i=0; i<=n+1; i++) {
        int piv = 0;
        for (int j=0; j<=n+1; j++) {
            piv += ban[i][j];
            ban[i][j] = piv;
        }
    }
    for (int i=0; i<=n+1; i++) {
        int piv = 0;
        for (int j=0; j<=n+1; j++) {
            piv += ban[j][i];
            ban[j][i] = piv;
        }
    }
    for (int i=1; i<=n; i++) {
        for (int j=1; j<=n; j++) {
            if(ban[i][j] == 0) cnt[i]++;
        }
    }
    for (int i=1; i<=n; i++) {
        int cs = 0;
        for (int j=1; j<=n; j++) {
            if(cnt[j] == 1){ cs = j; break; }
        }
        for (int j=1; j<=n; j++) {
            if(ban[cs][j] == 0){
                conn[cs] = j;
                break;
            }
        }
        for (int j=1; j<=n; j++) {
            if(ban[j][conn[cs]] == 0){
                cnt[j] --;
                ban[j][conn[cs]] = 1;
            }
        }
    }
    for (int i=1; i<=n; i++) {
        printf("%d\n",conn[i]);
    }
}