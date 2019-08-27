///////////////////////////
//
// KM
//
///////////////////////////

#include <cstdio>  
#include <cstring>  
#include <cstdlib>
using namespace std;  
const int maxn = 305;  
const int INF = 1000000000;
int g[maxn][maxn];  
int lx[maxn],ly[maxn];  
int match[maxn];  
bool visx[maxn],visy[maxn];  
int slack[maxn];  
int n;  
bool dfs(int cur){  
  visx[cur] = true;  
  for(int y=1;y<=n;y++){  
    if (visy[y])  continue;  
    int t=lx[cur]+ly[y]-g[cur][y];  
    if(t==0) {  
      visy[y] = true;  
      if(match[y]==-1||dfs(match[y])){  
          match[y] = cur;  
          return true;  
      }  
    } else if(slack[y]>t){  
      slack[y]=t;  
    }  
 }  
 return false;  
}  
int KM(){  
  memset(match, -1, sizeof(match));  
  memset(ly, 0, sizeof(ly));  
  for(int i=1; i<=n; i++){  
    lx[i]=-INF;  
    for(int j=1;j<=n;j++)  
      if(g[i][j]>lx[i]) lx[i]=g[i][j];  
  }  
  for (int x=1; x<=n; x++){  
    for (int i=1; i<=n; i++)
      slack[i]=INF;  
    while(true) {
      memset(visx,false,sizeof(visx));  
      memset(visy,false,sizeof(visy));  
      if(dfs(x))  break;  
      int d=INF;  
      for(int i=1;i<=n;i++){  
          if(!visy[i]&&d>slack[i])
          d=slack[i];  
      }  
      for(int i=1;i<=n;i++){  
        if(visx[i])
        lx[i]-=d;  
      }  
      for(int i=1;i<=n;i++){  
        if(visy[i])
          ly[i]+=d;  
        else
          slack[i]-=d;  
        }  
    }  
  }  
  int result = 0;  
  for(int i = 1; i <=n; i++)  
  if (match[i] > -1)
     result += g[match[i]][i];  
  return result;  
}  
int main(){  
  while(scanf("%d",&n)!=EOF){  
    int cost;  
    for(int i=1;i<=n;i++)  
      for(int j=1;j<=n;j++)  {  
        scanf("%d",&cost);  
        g[i][j]=cost;  
      }  
    printf("%d\n",KM());  
  }  
  return 0;  
}  
