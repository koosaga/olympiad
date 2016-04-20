#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;
 
int n;
int a[3][105], sz[3], dp[105][105][105][3];
 
inline int cost(int p, int q, int ig){
    if(ig) return 0;
    int dist = abs(p-q);
    dist %= n;
    return min(n - dist,dist);
}
 
int f(int x, int y, int z, int eaten){
    if(x > sz[0]+1 || y > sz[1]+1 || z > sz[2]+1) return 1e9;
    if(x == sz[0]+1 && y == sz[1]+1 && z == sz[2]+1) return 0;
    if(dp[x][y][z][eaten]) return dp[x][y][z][eaten];
    int pos = 0;
    if(eaten == 0) pos = a[0][x-1];
    else if(eaten == 1) pos = a[1][y-1] + 2*n/3;
    else pos = a[2][z-1] + n/3;
    int ret1 = f(x+1,y,z,0) + cost(pos,a[0][x],0);
    int ret2 = f(x,y+1,z,1) + cost(pos,a[1][y] + 2*n/3,0);
    int ret3 = f(x,y,z+1,2) + cost(pos,a[2][z] + n/3,0);
    return dp[x][y][z][eaten] = min(ret1,min(ret2,ret3));
}
 
int main(){
    scanf("%d",&n);
    for (int i=0; i<3; i++) {
        scanf("%d",&sz[i]);
        for (int j=1; j<=sz[i]; j++) {
            scanf("%d",&a[i][j]);
            a[i][j]--;
        }
    }
    a[1][0] = n/3;
    a[2][0] = 2*n/3;
    int ret = f(1,1,1,0);
    printf("%d",ret);
}