#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;
typedef long long lint;
const int mod = 1000007;

int main(){
    int n, a[10005], pmax[10005];
    int d[10005];
    cin >> n;
    for(int i=0; i<n; i++) cin >> a[i], pmax[i] = max(a[i], i ? pmax[i-1] : 0);
    fill(d, d+n+1, 1);
    int ret = 1;
    for(int i=n-1; i>=0; i--){
        for(int j=1; j<a[i]; j++) ret += d[max(i ? pmax[i-1] : 0, j)], ret %= mod;
        for(int j=1; j<i; j++) d[j] = (1ll * j * d[j] + d[j+1]) % mod;
    }
    cout << ret;
}