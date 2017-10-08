#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
const int mod = 1e9 + 7;
const int MAXN = 1005;

vector<pi> a, b;

lint dnc(int s, int e, int ps, int pe){
    if(s > e) return 0;
    int m = (s+e)/2;
    lint ans = -2e18;
    int opt = ps;
    for(int i=ps; i<=pe; i++){
        int dx = b[i].first - a[m].first;
        int dy = b[i].second - a[m].second;
        if((dx >= 0 || dy >= 0) && ans <= 1ll * dx * dy){
            ans = 1ll * dx * dy;
            opt = i;
        }
    }
    return max({ans, dnc(s, m-1, ps, opt), dnc(m+1, e, opt, pe)});
}

int main(){
    int n, m;
    scanf("%d %d",&n,&m);
    vector<pi> l(n), r(m);
    for(auto &i : l) scanf("%d %d",&i.first,&i.second);
    for(auto &j : r) scanf("%d %d",&j.first,&j.second);
    sort(l.begin(), l.end());
    sort(r.begin(), r.end());
    for(auto &i : l){
        if(!a.empty() && a.back().second <= i.second) continue;
        a.push_back(i);
    }
    for(auto &i : r){
        while(!b.empty() && b.back().second <= i.second) b.pop_back();
        b.push_back(i);
    }
    cout << max(0ll, dnc(0, a.size() - 1, 0, b.size() - 1));
}
