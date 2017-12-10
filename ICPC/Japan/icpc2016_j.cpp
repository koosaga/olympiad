#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;
typedef pair<llf, llf> pj;
const double eps = 1e-11;

int N, x[12], y[12], r;

llf ccw(pj a, pj b){
    return a.first * b.second - b.first * a.second;
}

llf solve2(pj x, pj y){
    llf ang = atan2(y.second, y.first) - atan2(x.second, x.first) + 4 * M_PI;
    while(ang >= M_PI) ang -= 2 * M_PI;
    return 0.5 * min(ccw(x, y), ang * r * r);
}

llf solve(pj x, pj y){
    if(ccw(x, y) < 0) return -solve(y, x);
    llf dis = hypot(y.first - x.first, y.second - x.second);
    llf linepnt = ccw(x, y) / dis;
    if(linepnt >= r - eps) return solve2(x, y);
    llf cx = -linepnt * (x.second - y.second) / dis;
    llf cy = -linepnt * (y.first - x.first) / dis;
    llf up = sqrt(1.0 * r * r - linepnt * linepnt) / dis;
    pj c1(cx + up * (y.first - x.first), cy + up * (y.second - x.second));
    pj c2(cx - up * (y.first - x.first), cy - up * (y.second - x.second));
    if(ccw(c1, c2) < 0) swap(c1, c2);
    vector<pj> v;
    v.push_back(x);
    if(ccw(x, c1) > 0 && ccw(c1, y) > 0) v.push_back(c1);
    if(ccw(x, c2) > 0 && ccw(c2, y) > 0) v.push_back(c2);
    v.push_back(y);
    llf ret = 0;
    for(int i=0; i<v.size()-1; i++){
        ret += solve2(v[i], v[i+1]);
    }
    return ret;
}

double solve(double px, double py, double r){
    double ret = 0;
    for(int i=0; i<N; i++){
        auto p1 = pj(x[i] - px, y[i] - py);
        auto p2 = pj(x[i+1] - px, y[i+1] - py);
        ret += solve(p1, p2);
    }
    return ret;
}

int main()
{
    int R;
    scanf("%d%d", &N, &R);
    double xs = 0;
    double ys = 0;
    for(int i=0; i<N; ++i)
    {
        scanf("%d%d", x+i, y+i);
        xs += x[i];
        ys += y[i];
    }
    x[N] = x[0];
    y[N] = y[0];
    r = R;
    xs /= N;
    ys /= N;
    double jump = 0.2;
    const double temperature = 0.9999;
    double ans = 0;
    while(clock() < (int)(2.9*CLOCKS_PER_SEC))
    {
        jump *= temperature;
        double v1 = solve(xs+jump, ys, R);
        double v2 = solve(xs-jump, ys, R);
        double v3 = solve(xs, ys-jump, R);
        double v4 = solve(xs, ys+jump, R);
        if(v1 < 0 && v2 < 0 && v3 < 0 && v4 < 0) continue;
        if(v1 > v2 && v1 > v3 && v1 > v4)
            xs += jump;
        else if(v2 > v1 && v2 > v3 && v2 > v4)
            xs -= jump;
        else if(v3 > v1 && v3 > v2 && v3 > v4)
            ys -= jump;
        else
            ys += jump;
        ans = max({ans, v1, v2, v3, v4});
        //break;
    }
    printf("%.06f\n", ans);
}
