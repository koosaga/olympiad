#include <cstdio>
#include <cmath>
#include <queue>
int n,k,x[1005],y[1005];
int d(int p, int q){return (int)(9.9999+sqrt((y[q]-y[p])*(y[q]-y[p])+(x[q]-x[p])*(x[q]-x[p])))/10;}
 
int isTravellable(int lim){
    int visited[1005]={},pos,cd;
    std::queue<int> q,dist;
    q.push(0);
    dist.push(0);
    visited[0]=1;
    while (!q.empty()) {
        pos=q.front();
        cd=dist.front();
        if(cd>k+1) return 0;
        if(pos==n+1) return 1;
        for (int j=0; j<n+2; j++) {
            if(!visited[j] && d(pos,j)<=lim){
                q.push(j);
                visited[j]=1;
                dist.push(cd+1);
            }
        }
        q.pop();
        dist.pop();
    }
    return 0;
}
 
int searchDist(int s, int e){
    if(s==e) return s;
    if(isTravellable((s+e)/2)) return searchDist(s,(s+e)/2);
    else return searchDist((s+e)/2+1,e);
}
 
int main(){
    scanf("%d %d",&n,&k);
    x[0]=y[0]=0;
    for (int i=1; i<=n; i++) {
        scanf("%d %d",&x[i],&y[i]);
    }
    x[n+1]=y[n+1]=10000;
    printf("%d",searchDist(1415/(k+2),1415));
}