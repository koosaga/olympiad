#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pi;
typedef long long lint;
const int MAXN = 205;
const double eps = 1e-3;

int n, bino[10][10];
long double a[10];

bool ok(int x){
    long double prv[10];
    memcpy(prv, a, sizeof(prv));
    if(x == n+2){
        for(int j=n; j>=0; j--){
            for(int k=0; k<=j; k++){
                a[k] = a[k+1] - a[k];
            }
        }
        bool dap = 0;
        if(fabs(a[0]) < eps) dap = 1;
        memcpy(a, prv, sizeof(a));
        return dap;
    }
    long double ret = 0;
    int ncf = 0;
    for(int i=0; i<n+2; i++){
        int coeff = bino[n+1][i] * ((n + 1 - i) % 2 ? 1 : -1);
        ret += a[i] * coeff;
        if(i == x) ncf = coeff;
    }
    a[x] -= ret / ncf;
    for(int j=n; j>=0; j--){
        for(int k=0; k<=j+1; k++){
            a[k] = a[k+1] - a[k];
        }
    }
    bool dap = fabs(a[0]) < eps && fabs(a[1]) < eps;
    memcpy(a, prv, sizeof(a));
    return dap;
}

int main(){
    for(int i=0; i<10; i++){
        bino[i][0] = 1;
        for(int j=1; j<=i; j++){
            bino[i][j] = (bino[i-1][j] + bino[i-1][j-1]);
        }
    }
    while(true){
        cin >> n;
        if(n == 0) break;
        for(int i=0; i<n+3; i++) cin >> a[i];
        for(int i=0; i<n+3; i++){
            if(ok(i)){
                printf("%d\n", i);
                break;
            }
        }
    }
}


