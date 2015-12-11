#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
 
char a[10][10];
int cc;
 
char dp[1<<9][1<<3][3][3];
int cnts[3][3];
 
int f(int row, int ccol, int skx, int sky){
    if(skx == 3) return (row == 0 ? 0 : 100);
    if(sky == 3){
        if(ccol) return 100;
        else return f(row,(cc>>(3*skx+3))&7,skx+1,0);
    }
    if(~dp[row][ccol][skx][sky]) return dp[row][ccol][skx][sky];
    int res = 100;
    for (int i=0; i<512; i++) {
        int nrow = row;
        int ncol = ccol;
        int cnt = 0;
        for (int j=0; j<9; j++) {
            if((i>>j)&1){
                nrow ^= (1<<(sky * 3 + (j/3)));
                ncol ^= (1<<(j%3));
                cnt++;
            }
        }
        if((cnt + cnts[skx][sky])&1) continue;
        res = min(res,f(nrow,ncol,skx,sky+1) + cnt);
    }
    return dp[row][ccol][skx][sky] = res;
}
 
int main(){
    int cr = 0;
    memset(dp,-1,sizeof(dp));
    for (int i=0; i<9; i++) {
        scanf("%s",a[i]);
        for (int j=0; j<9; j++) {
            a[i][j] -= '0';
            cr ^= (a[i][j] << j);
            cc ^= (a[i][j] << i);
            cnts[i/3][j/3] ^= a[i][j];
        }
    }
    printf("%d",f(cr,cc&7,0,0));
}