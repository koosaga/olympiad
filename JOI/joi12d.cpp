#include <cstdio>
#include <algorithm>
using namespace std;
  
short cd[5005][5005];
short dd[5005][5005];
int n;
  
int main(){
    int m,a,b,x;
    scanf("%d %d",&n,&m);
    for (int i=0; i<m; i++) {
        scanf("%d %d %d",&a,&b,&x);
        dd[a][b]++;
        dd[a+x+2][b]--;
        cd[a][b]--;
        cd[a+x+2][b+x+2]++;
    }
    for (int i=1; i<=n+1; i++) {
        for (int j=1; j<=n+1; j++) {
            dd[i][j] += dd[i-1][j];
            cd[i][j] += cd[i-1][j-1];
        }
    }
    int res = 0;
    for (int i=1; i<=n+1; i++) {
        int piv = 0;
        for (int j=1; j<=n+1; j++) {
            piv += dd[i][j] + cd[i][j];
            if(piv>0) res++;
        }
    }
    printf("%d",res);
}