#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using pi = pair<int, int>;

int bktk(vector<pi> &v, int k){
	if(sz(v) == 0) return 0;
	if(k == 0) return 1e9;
	sort(all(v));
	int T = v[0].first;
	sort(all(v), [&](const pi &a, const pi &b){
		return 30 + (a.first - T) * a.second < 30 + (b.first - T) * b.second;
	});
	int ret = 1e9;
	vector<pi> w;
	for(int i=sz(v)-1; i>=0; i--){
		ret = min(ret, bktk(w, k - 1) + 30 + (v[i].first - T) * v[i].second);
		w.push_back(v[i]);
	}
	return ret;
}

int main(){
	int n, k;
	cin >> n >> k;
	vector<pi> a(n);
	for(int i=0; i<n; i++){
		cin >> a[i].second >> a[i].first;
	}
	sort(all(a));
	vector<pi> v;
	set<int> s;
	for(int i=n-1; i>=0; i--){
		if(!s.count(a[i].second)) v.push_back(a[i]);
		s.insert(a[i].second);
	}
	for(auto &i : v) swap(i.first, i.second);
	cout << bktk(v, k) << endl;
}
