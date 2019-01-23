#include <bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
using lint = long long;
using real_t = long double;
using pnt = complex<real_t>;
const int mod = 1e9 + 7;
const real_t eps = 1e-4;
const int MAXN = 105;

int n, h, w, r;
pnt x[MAXN];

void Try(double R){
    real_t sx = 1e10, sy = 1e10;
    real_t ex = -1e10, ey = -1e10;
    for(int i=0; i<n; i++){
        auto val = x[i] * pnt(cos(R), sin(R));
        sx = min(sx, val.real());
        ex = max(ex, val.real());
        sy = min(sy, val.imag());
        ey = max(ey, val.imag());
    }
    if(ex - sx <= h + eps && ey - sy <= w + eps){
        puts("Yes");
        exit(0);
    }
    if(ex - sx <= w + eps && ey - sy <= h + eps){
        puts("Yes");
        exit(0);
    }
}

bool solve(){
    if(n <= 1) return 1;
    double PI = acos(-1);
    for(int i=0; i<n; i++){
        for(int j=0; j<i; j++){
            double bl = 0;
            double br = PI * 0.5;
            double H = h;
            double W = w;
            double R = abs(x[i] - x[j]);
            if(H <= R){
                br = asin(H / R);
            }
            if(W <= R){
                bl = acos(W / R);
            }
            if(br - bl >= 0.5 * PI - eps){
                continue;
            }
            if(bl >= br) return 0;
            bl -= arg(x[i] - x[j]);
            br -= arg(x[i] - x[j]);
            Try(bl);
            Try(br);
            Try(PI - br);
            Try(PI - bl);
        }
    }
    Try(PI);
    return 0;
}

int main(){
    cin >> n >> h >> w >> r;
    h -= 2 * r;
    w -= 2 * r;
    if(h <= 0 || w <= 0){
        puts("No");
        return 0;
    }
    vector<pi> v;
    for(int i=0; i<n; i++){
        int x, y; cin >> x >> y;
        v.emplace_back(x, y);
    }
    sort(v.begin(), v.end());
    v.resize(unique(v.begin(), v.end()) - v.begin());
    n = v.size();
    for(int i=0; i<n; i++){
        x[i] = pnt(v[i].first, v[i].second);
    }
    if(solve()){
        puts("Yes");
        return 0;
    }
    else puts("No");
}

