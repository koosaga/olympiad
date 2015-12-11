#include <cstdio>
#include <algorithm>
using namespace std;
 
int n, m, q;
int r[100005];
 
int nxt[100005][30];
long long cost[100005][30];
 
int query(int x){
    int pos = max(x - m + n, 1);
    long long ans = x;
    int val = min(m - n + 1, x);
    for(int i=0; i<30; i++){
        if((val >> i) & 1){
            ans += cost[pos][i];
            pos = nxt[pos][i];
        }
    }
    return (int)ans;
}
 
int main(){
    scanf("%d %d %d",&m,&n,&q);
    for(int i=1; i<=n; i++){
        int t;
        scanf("%d",&t);
        r[t] = i;
    }
    for(int i=1; i<=n; i++){
        nxt[i][0] = r[i] + 1;
        cost[i][0] = r[i] - i;
    }
    nxt[n+1][0] = n+1;
    cost[n+1][0] = 0;
    for(int i=1; i<30; i++){
        for(int j=1; j<=n+1; j++){
            nxt[j][i] = nxt[nxt[j][i-1]][i-1];
            cost[j][i] = cost[nxt[j][i-1]][i-1] + cost[j][i-1];
        }
    }
    while(q--){
        int t;
        scanf("%d",&t);
        printf("%d\n",query(m + 1 - t));
    }
}