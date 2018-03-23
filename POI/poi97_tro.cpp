#include <cstdio>
#include <cstring>

int cnt1[1005], cnt2[1005];
int adj[1005][1005];
int n, q;

int main(){
    scanf("%d",&n);
    scanf("%d",&q);
    while(q--){
        int s, e;
        scanf("%d %d",&s,&e);
        adj[s][e] = adj[e][s] = 1;
    }
    for (int i=1; i<n; i++) {
        for (int j=i+1; j<=n; j++) {
            if(adj[i][j]) cnt1[i]++, cnt1[j]++;
            else cnt2[i]++, cnt2[j]++;
        }
    }
    int r = n * (n-1) * (n-2) / 3;
    for (int i=1; i<=n; i++) {
        r -= cnt1[i] * cnt2[i];
    }
    printf("%d\n",r/2);
}