#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;
 
int n, d, a[255][255];
 
int getsum(int sx, int ex, int sy, int ey){
    sx = max(sx, 1);
    ex = min(ex, n);
    sy = max(sy, 1);
    ey = min(ey, n);
    if(sx <= ex && sy <= ey){
        return a[ex][ey] - a[sx-1][ey] - a[ex][sy-1] + a[sx-1][sy-1];
    }
    return 0;
}
 
int main(){
    cin >> n >> d;
    for(int i=1; i<=n; i++){
        for(int j=1; j<=n; j++){
            cin >> a[i][j];
            a[i][j] += a[i-1][j] + a[i][j-1] - a[i-1][j-1];
        }
    }
    for(int i=1; i<=n; i++){
        for(int j=1; j<=n; j++){
            printf("%d ", getsum(i-d, i+d, j-d, j+d));
        }
        puts("");
    }
}