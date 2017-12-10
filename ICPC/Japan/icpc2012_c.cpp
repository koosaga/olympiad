#include <bits/stdc++.h>
typedef long long lint;
using namespace std;

struct matrix{
    lint a[55][55];
}E, A;

int n, mod, va, vb, vc, t;

matrix mul(matrix a, matrix b){
    matrix ret;
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            ret.a[i][j] = 0;
            for(int k=0; k<n; k++){
                ret.a[i][j] += 1ll * a.a[i][k] * b.a[k][j] % mod;
            }
            ret.a[i][j] %= mod;
        }
    }
    return ret;
}

void solve(){
    scanf("%d %d %d %d %d %d",&n,&mod,&va,&vb,&vc,&t);
    if(mod == 0) exit(0);
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            E.a[i][j] = (i == j);
            A.a[i][j] = 0;
            if(j - i == 1) A.a[i][j] = va;
            if(j - i == 0) A.a[i][j] = vb;
            if(j - i == -1) A.a[i][j] = vc;
        }
    }
    while(t){
        if(t & 1) E = mul(E, A);
        A = mul(A, A);
        t >>= 1;
    }
    int arr[55];
    for(int i=0; i<n; i++) scanf("%d",&arr[i]);
    for(int i=0; i<n; i++){
        lint ret = 0;
        for(int j=0; j<n; j++){
            ret += arr[j] * E.a[j][i] % mod;
        }
        printf("%lld ", ret % mod);
    }
    puts("");
}

int main(){
    while(true) solve();
}
