#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;

int n, m;
lint a[100005], b[100005];

bool gB();

bool gA(){
    if(n == 0) return 0;
    if(a[n-1] + a[n] < b[m]) return 0;
    if(b[m-1] + b[m] < a[n]) return 1;
    assert(a[n] != b[m]);
    bool ret = 0;
    if(a[n] > b[m]){
        m--;
        bool ret = 0;
        if(!gB()) ret = 1;
        m++;
        if(ret == 1) return 1;
    }
    a[n-1] += a[n];
    n--;
    if(!gB()) ret = 1;
    n++;
    a[n-1] -= a[n];
    return ret;
}

bool gB(){
    if(m == 0) return 0;
    if(a[n-1] + a[n] < b[m]) return 1;
    if(b[m-1] + b[m] < a[n]) return 0;
    assert(a[n] != b[m]);
    bool ret = 0;
    if(a[n] < b[m]){
        n--;
        bool ret = 0;
        if(!gA()) ret = 1;
        n++;
        if(ret == 1) return 1;
    }
    b[m-1] += b[m];
    m--;
    if(!gA()) ret = 1;
    m++;
    b[m-1] -= b[m];
    return ret;
}

int main(){
    int t = 0;
    while(~scanf("%d %d",&n,&m)){
        for(int i=0; i<n; i++){
            scanf("%lld",&a[i+1]);
        }
        for(int i=0; i<m; i++){
            scanf("%lld",&b[i+1]);
        }
        sort(a+1, a+n+1);
        sort(b+1, b+m+1);
        printf("Case %d: %s\n", ++t, (gA() ? "Takeover Incorporated" : "Buyout Limited"));
    }
}
        