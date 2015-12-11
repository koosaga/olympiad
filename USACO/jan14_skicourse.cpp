#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;
 
int n, m;
char str[105][105];
 
bool span[105][105], rpan[105][105];
int pss[105][105], pse[105][105];
 
bool scan(int s, int e, int x){
    if(pss[s+x-1][e+x-1] - pss[s-1][e+x-1] - pss[s+x-1][e-1] + pss[s-1][e-1] == x * x) return 1;
    if(pse[s+x-1][e+x-1] - pse[s-1][e+x-1] - pse[s+x-1][e-1] + pse[s-1][e-1] == x * x) return 1;
    return 0;
}
 
void update_psum(){
    for(int i=1; i<=n; i++){
        for(int j=1; j<=m; j++){
            pss[i][j] = span[i][j] + pss[i-1][j] + pss[i][j-1] - pss[i-1][j-1];
            pse[i][j] = rpan[i][j] + pse[i-1][j] + pse[i][j-1] - pse[i-1][j-1];
        }
    }
}
 
bool vis[105][105];
int dx[4] = {1,0,-1,0}, dy[4] = {0,1,0,-1};
 
bool trial(int x){
    memset(vis,0,sizeof(vis));
    memset(span,0,sizeof(span));
    memset(rpan,0,sizeof(rpan));
    queue<int> qx, qy;
    for(int i=1; i<=n; i++){
        for(int j=1; j<=m; j++){
            if(str[i][j] == 'R') rpan[i][j] = 1;
            else span[i][j] = 1;
        }
    }
    update_psum();
 
    for(int i=1; i<=n; i++){
        for(int j=1; j<=m; j++){
            if(i >= x-1 && j >= x-1 && scan(i-x+1,j-x+1,x)){
                qx.push(i - x + 1);
                qy.push(j - x + 1);
                vis[i-x+1][j-x+1] = 1;
            }
        }
    }   
    int ret = 0;
    while(!qx.empty()){
        ret++;
        int xf = qx.front(), yf = qy.front();
        qx.pop(), qy.pop();
        for(int i=0; i<x; i++){
            for(int j=0; j<x; j++){
                rpan[i+xf][j+yf] = span[i+xf][j+yf] = 1;
            }
        }
        update_psum();
        for(int i=1; i<=n+1-x; i++){
            for(int j=1; j<=m+1-x; j++){
                if(!vis[i][j] && scan(i,j,x)){
                    vis[i][j] = 1;
                    qx.push(i), qy.push(j);
                }
            }
        }
    }
    return (ret == (n - x + 1) * (m - x + 1));
}
 
int main(){
    scanf("%d %d",&n,&m);
    for(int i=1; i<=n; i++){
        scanf("%s",str[i]+1);
    }
    int s = 1, e = min(n, m);
    while(s != e){
        int m = (s+e+1)/2;
        if(trial(m)) s = m;
        else e = m-1;
    }
    printf("%d",s);
}