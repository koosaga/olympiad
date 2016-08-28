#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;
 
int n;
long long res = 1e16, p[17];
 
void solve(int *bit, int sz, long long cb, int depth, int had_zero){
    if(cb >= res) return;
    if(sz == 1){
        int r = bit[0];
        if(r == 0){
            if(cb == 0 || had_zero) cb += p[depth];
        }
        else if(r == 1){
            cb += p[depth] * 10;
        }
        else{
            if(r&1){
                int minima = 1e9;
                for (int i=9; i; i--) {
                    if((r>>i)&1) minima = i;
                }
                for (int i=9; i; i--) {
                    if((r>>i)&1 && i != minima){
                        cb += p[depth] * i;
                        depth++;
                    }
                }
                depth++;
                cb += p[depth] * minima;
            }
            else{
                for (int i=9; i; i--) {
                    if((r>>i)&1){
                        cb += p[depth] * i;
                        depth++;
                    }
                }
            }
        }
        res = min(res,cb);
        return;
    }
    int* t = (int*) malloc(sizeof(int) * (sz/10 + 2));
    for (int i=0; i<10; i++) {
        int gz = 0;
        int nz = 0;
        int piv = i;
        t[nz] = 0;
        for (int j=0; j<sz; j++) {
            if(piv == 0 && (bit[j]&1)) gz = 1;
            t[nz] |= (bit[j] & (~(1<<piv)));
            piv++;
            if(piv == 10 && j != sz - 1){
                t[++nz] = 0;
                piv = 0;
            }
        }
        solve(t,nz+1,cb + p[depth] * i,depth+1,gz);
    }
}
 
int main(){
    int a[100005];
    scanf("%d",&n);
    p[0] = 1;
    for (int i=1; i<17; i++) {
        p[i] = p[i-1] * 10;
    }
    for (int i=0; i<n; i++) {
        int t;
        scanf("%d",&t);
        a[i] = 1<<t;
    }
    solve(a,n,0,0,0);
    printf("%lld",res);
}