#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
 
int adj[251][251],n;
int shortest[251],v[251],pa[251];
 
int dijk(){
    memset(shortest,0x3f,sizeof(shortest));
    memset(v,0,sizeof(v));
    shortest[1] = 0;
    for (int i=2; i<=n; i++) {
        shortest[i] = adj[1][i];
        pa[i] = 1;
    }
    int min, s = 1;
    for (int i=0; i<n; i++) {
        min = 1e9;
        for (int j=1; j<=n; j++) {
            if(!v[j] && min > shortest[j]){
                min = shortest[s = j];
            }
        }
        v[s] = 1;
        for (int j=1; j<=n; j++) {
            if(shortest[j] > shortest[s] + adj[s][j]){
                shortest[j] = shortest[s] + adj[s][j];
                pa[j] = s;
            }
        }
    }
    return shortest[n];
}
int main(){
    int m,p,q,r,qa[251];
    scanf("%d %d",&n,&m);
    memset(adj,0x3f,sizeof(adj));
    for (int i=0; i<m; i++) {
        scanf("%d %d %d",&p,&q,&r);
        adj[p][q] = adj[q][p] = r;
    }
    int s = n, c = dijk(), res = 0;
    memcpy(qa,pa,sizeof(pa));
    while (s != 1) {
        adj[qa[s]][s]*=2;
        adj[s][qa[s]]*=2;
        res = max(res,dijk()-c);
        adj[qa[s]][s]/=2;
        adj[s][qa[s]]/=2;
        s = qa[s];
    }
    printf("%d",res);
}