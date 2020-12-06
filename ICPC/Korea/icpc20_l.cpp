#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;

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
	int n; scanf("%d",&n);
	vector<pi> l, r;
	for(int i=0; i<n; i++){
		int x; scanf("%d",&x);
		r.emplace_back(i, x);
		l.emplace_back(i, -x);
	}
    for(auto &i : l){
        if(!a.empty() && a.back().second <= i.second) continue;
        a.push_back(i);
    }
    for(auto &i : r){
        while(!b.empty() && b.back().second <= i.second) b.pop_back();
        b.push_back(i);
    }
    cout << max(0ll, dnc(0, a.size() - 1, 0, b.size() - 1)) << endl;
}

