#include <cstdio>
#include <queue>
using namespace std;
   
int k, q;
int vis[1005][1005];
   
queue<int> qx, qy;
   
int main(){
    scanf("%d %d",&k,&q);
    qx.push(0);
    qy.push(0);
    vis[0][0] = 1;
    while(!qx.empty()){
        int xf = qx.front();
        int yf = qy.front();
        qx.pop(), qy.pop();
        if(yf + 1 <= k && !vis[xf][yf+1]){
            int p = k - yf;
            // xf should add these
            if(xf + p < yf + 1) continue;
            vis[xf][yf+1] = 1;
            qx.push(xf);
            qy.push(yf+1);
        }
        if(xf +1 <= k && !vis[xf+1][yf]){
            int p = k - xf;
            if(yf + p + 1 < xf + 1) continue;
            qx.push(xf+1);
            qy.push(yf);
            vis[xf+1][yf] = 1;
        }
        if(xf+1<=k && yf+1<=k && !vis[xf+1][yf+1]){
            qx.push(xf+1);
            qy.push(yf+1);
            vis[xf+1][yf+1] = 1;
        }
    }
    while(q--){
        int a, b;
        scanf("%d %d",&a,&b);
        printf("%d\n",vis[a][b]);
    }
}