#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;

int n, m, st, ed, f, s[1005], e[1005], a[1005], b[1005], d[1005];

int dist[205][105][105];

int bs = -1, be = -1, fa, fb, fd;
int main(){
    for(int i=1; i<205; i++)for(int j=0; j<105; j++)for(int k=0; k<105; k++) dist[i][j][k] = 3e8;
    scanf("%d %d %d %d %d",&n,&m,&st,&ed,&f);
    for(int i=0; i<m; i++){
        scanf("%d %d %d %d %d",&s[i],&e[i],&a[i],&b[i],&d[i]);
        if(a[i] < b[i]){
            bs = s[i], be = e[i];
            fa = a[i], fb = b[i], fd = d[i];
        }
    }
    for(int t=0; t<=f; t++){
        for(int i=0; i<n; i++) dist[t][i][i] = 0;
        for(int i=0; i<m; i++){
            int cost = min(t, d[i]) * a[i] + max(t - d[i], 0) * b[i];
            if(a[i] >= b[i]) dist[t][s[i]][e[i]] = min(dist[t][s[i]][e[i]], cost);
        }
        for(int i=0; i<n; i++){
            for(int j=0; j<n; j++){
                for(int k=0; k<n; k++){
                    dist[t][j][k] = min(dist[t][j][k], dist[t][j][i] + dist[t][i][k]);
                }
            }
        }
    }
    int ret = 1e9;
    if(bs == -1){
        ret = dist[f][st][ed];
    }
    else{
        for(int i=0; i<n; i++){
            for(int j=0; j<n; j++){
                for(int k=0; k<=f; k++){
                    int cost = dist[f][st][i] + dist[f-k][i][j] + dist[f][j][ed] + dist[k][i][bs] + dist[k][be][j];
                    cost += min(k, fd) * fa + max(k - fd, 0) * fb;
                    ret = min(ret, cost);
                }
            }
        }
    }
    if(ret > 1e8){
        puts("Impossible");
        return 0;
    }
    printf("%d",ret);
}