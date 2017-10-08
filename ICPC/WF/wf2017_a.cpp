#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
const int mod = 1e9 + 7;
typedef pair<int, int> pi;

int n;
pi a[205];

lint ccw(pi a, pi b, pi c){
    int dx1 = b.first - a.first;
    int dy1 = b.second - a.second;
    int dx2 = c.first - a.first;
    int dy2 = c.second - a.second;
    return 1ll * dx1 * dy2 - 1ll * dy1 * dx2;
}

double solve(int i, int j){
    auto crs = [&](int k){
        double p = a[j].first - a[i].first;
        double q = a[j].second - a[i].second;
        double x1 = a[k].first - a[i].first;
        double y1 = a[k].second - a[i].second;
        double x2 = a[k+1].first - a[i].first;
        double y2 = a[k+1].second - a[i].second;
        return (x1 * y2 - y1 * x2) / (p * y2 + q * x1 - p * y1 - q * x2);
    };
    vector<double> v;
    for(int k=0; k<n; k++){
        if(ccw(a[i], a[j], a[k]) < 0 && ccw(a[i], a[j], a[k+1]) > 0) v.push_back(crs(k));
        else if(ccw(a[i], a[j], a[k]) > 0 && ccw(a[i], a[j], a[k+1]) < 0) v.push_back(crs(k));
        else if(ccw(a[i], a[j], a[k+1]) == 0){
            // Only point lies
            if(ccw(a[i], a[j], a[k+2]) > 0 && ccw(a[i], a[j], a[k]) < 0) v.push_back(crs(k));
            if(ccw(a[i], a[j], a[k+2]) < 0 && ccw(a[i], a[j], a[k]) > 0) v.push_back(crs(k));
            // Now line lies here
            if(ccw(a[i], a[j], a[k]) == 0){
                if(a[k] < a[k+1] && ccw(a[i], a[j], a[k+2]) > 0){
                    v.push_back(crs(k+1));
                }
                if(a[k] > a[k+1] && ccw(a[i], a[j], a[k+2]) < 0){
                    v.push_back(crs(k+1));
                }
            }
            if(ccw(a[i], a[j], a[k+2]) == 0){
                if(a[k+1] < a[k+2] && ccw(a[i], a[j], a[k]) > 0){
                    v.push_back(crs(k));
                }
                if(a[k+1] > a[k+2] && ccw(a[i], a[j], a[k]) < 0){
                    v.push_back(crs(k));
                }
            }
        }
    }
    assert(v.size() % 2 == 0);
    double ret = 0;
    sort(v.begin(), v.end());
    for(int i=0; i<v.size(); i+=2){
        ret = max(ret, v[i+1] - v[i]);
    }
    ret *= hypot(a[j].first - a[i].first, a[j].second - a[i].second);
    return ret;
}


int main(){
    cin >> n;
    for(int i=0; i<n; i++){
        cin >> a[i].first >> a[i].second;
    }
    a[n] = a[0];
    a[n+1] = a[1];
    double ret = 0;
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(a[i] < a[j]) ret = max(ret, solve(i, j));
        }
    }
    printf("%.10f", ret);
}

