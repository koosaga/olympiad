#include <cstdio>
#include <queue>
#include <algorithm>
using namespace std;
typedef pair<int,int> pi;

int n,m,k,a[1005][1005];
int dx[1005][1005];

int main(){
    scanf("%d %d %d",&n,&m,&k);
    for (int i=1; i<=n; i++) {
        for (int j=1; j<=m; j++) {
            scanf("%d",&a[i][j]);
        }
    }
    dx[1][1] = k-1;
    for (int i=2; i<=n+m; i++) {
        for (int j=max(i - n,1); j<=m && i - j >= 1; j++) {
            int xf = i - j;
            int yf = j;
            int low = dx[xf][yf] / 2;
            int right = dx[xf][yf] / 2;
            if(dx[xf][yf] & 1){
                if(a[xf][yf]) right++;
                else low++;
                a[xf][yf] ^= 1;
            }
            dx[xf][yf+1] += right;
            dx[xf+1][yf] += low;
        }
    }
    int px = 1, py = 1;
    while (px <= n && py <= m) {
        int dx = a[px][py];
        px += 1 - dx;
        py += dx;
    }
    printf("%d %d",px,py);
}