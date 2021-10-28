#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using llf = long double;
using pi = pair<int, int>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXN = 2005;
const int mod = 1e9 + 7;

int n, a[MAXN];
double trial2(double m){
    double the = 0;
    for(int j = 0; j < n-1; j++) the += 2 * asin(a[j] / (2.0 * m));
    the -= 2 * asin(a[n-1] / (2.0 * m));
    return the;
}
double trial1(double m){
    double the = 0;
        for(int j = 0; j < n; j++) the += 2 * asin(a[j] / (2.0 * m));
        return the;
}

int main(){
    cin >> n;
    for(int i = 0; i < n; i++) cin >> a[i];
    sort(a, a + n);
    double s = 0, e = 1e9;
    s = a[n-1] / 2.0;
    for(int i = 0; i < 69; i++){
        double m = (s + e) / 2;
        if(trial1(m) >= 2 * acos(-1)) s = m;
        else e = m;
    }
    if(fabs(trial1(s) - 2 * acos(-1)) < 1e-8){
        printf("%.10f\n", s);
        return 0;
    }
    s = 0, e = 1e9;
    for(int i = 0; i < 69; i++){
        double m = (s + e) / 2;
        if(trial2(m) >= 0) e = m;
        else s = m;
    }
        printf("%.10f\n", s);
}
