#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
const int mod = 1e9 + 7;
typedef pair<int, int> pi;

int n, t;
int d[1005], s[1005];

double trial(double x){
    double ret = 0;
    for(int i=0; i<n; i++) ret += d[i] / (s[i] + x);
    return ret;
}

int main(){
    cin >> n >> t;
    for(int i=0; i<n; i++) cin >> d[i] >> s[i];
    double st = -1e10, ed = 1e10;
    for(int i=0; i<n; i++){
        st = max(st, -s[i] + 1e-9);
    }
    for(int i=0; i<100; i++){
        double m = (st+ed)/2;
        if(trial(m) <= t) ed = m;
        else st = m;
    }
    printf("%.10f\n", st);
}
