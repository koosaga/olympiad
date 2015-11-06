#include <cstdio>
 
int n,m,adj[201][201];
 
int main(){
    scanf("%d %d",&n,&m);
    int x,y,res = 0;
    for (int i=0; i<m; i++) {
        scanf("%d %d",&x,&y);
        adj[x][y] = adj[y][x] = 1;
    }
    for (int i=1; i<=n; i++) {
        for (int j=i+1; j<=n; j++) {
            for (int k=j+1; k<=n; k++) {
                if(!adj[i][j] && !adj[i][k] && !adj[j][k]){
                    res++;
                }
            }
        }
    }
    printf("%d",res);
}