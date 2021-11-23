#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using llf = long double;
using pi = pair<lint, lint>;

bool in(pi a, pi b){
	return a.first <= b.first && b.second <= a.second;
}

int solve(vector<pi> a){
	int n = sz(a);
//	for(auto &[x, y] : a) cout << x << ' ' << y << '\n';
	vector<int> dpa(n + 1), dpb(n + 1);
	vector<int> decf(n + 1), incf(n + 1), decs(n + 1), incs(n + 1);
	vector<int> dec(n + 1), inc(n + 1);
	vector<int> bitonic(n + 1);
	for(int i = n - 1; i >= 0; i--){
		decf[i] = incf[i] = decs[i] = incs[i] = i;
		if(i + 1 < n && a[i].first <= a[i + 1].first) incf[i] = incf[i + 1];
		if(i + 1 < n && a[i].first >= a[i + 1].first) decf[i] = decf[i + 1];
		if(i + 1 < n && a[i].second <= a[i + 1].second) incs[i] = incs[i + 1];
		if(i + 1 < n && a[i].second >= a[i + 1].second) decs[i] = decs[i + 1];
		dec[i] = min(incf[i], decs[i]);
		inc[i] = min(decf[i], incs[i]);
	}
	vector<int> upChain, dnChain;
	vector<int> stab1(n + 1);
	vector<int> stab2(n + 1);
	stab1[n] = stab2[n] = n - 1;
	for(int i = n - 1; i >= 0; i--){
		stab1[i] = stab1[i + 1];
		stab2[i] = stab2[i + 1];
		{
			int s = 0, e = sz(upChain);
			while(s != e){
				int m = (s + e) / 2;
				if(a[upChain[m]].first >= a[i].second) s = m + 1;
				else e = m;
			}
			if(s) stab1[i] = min(stab1[i], upChain[s - 1] - 1);
		}
		{
			int s = 0, e = sz(upChain);
			while(s != e){
				int m = (s + e) / 2;
				if(a[upChain[m]].first > a[i].second) s = m + 1;
				else e = m;
			}
			if(s) stab2[i] = min(stab2[i], upChain[s - 1] - 1);
		}
		{
			int s = 0, e = sz(dnChain);
			while(s != e){
				int m = (s + e) / 2;
				if(a[dnChain[m]].second <= a[i].first) s = m + 1;
				else e = m;
			}
			if(s) stab1[i] = min(stab1[i], dnChain[s - 1] - 1);
		}
		{
			int s = 0, e = sz(dnChain);
			while(s != e){
				int m = (s + e) / 2;
				if(a[dnChain[m]].second < a[i].first) s = m + 1;
				else e = m;
			}
			if(s) stab2[i] = min(stab2[i], dnChain[s - 1] - 1);
		}
		while(sz(upChain) && a[upChain.back()].first <= a[i].first) upChain.pop_back();
		upChain.push_back(i);
		while(sz(dnChain) && a[dnChain.back()].second >= a[i].second) dnChain.pop_back();
		dnChain.push_back(i);
	}
	for(int i = n - 1; i >= 0; i--){
		int i1 = decf[incf[i]];
		int i2 = incs[decs[i]];
		int i3 = stab2[i];
		bitonic[i] = min({i1, i2, i3});
	}
	for(int i = n - 1; i >= 0; i--){
		dpa[i] = min(dpa[stab1[i] + 1], dpb[inc[i] + 1]) + 1;
		int nidx = dec[i] + 1;
		if(nidx < n){
			nidx = stab1[nidx] + 1;
			dpb[i] = min(dpa[nidx], dpb[bitonic[i] + 1]) + 1;
		}
		else dpb[i] = 0;
	}
	return dpa[0];
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n; cin >> n;
	vector<pi> a(n);
	vector<int> vx, vy;
	for(auto &[x, y] : a){
		cin >> x >> y;
		vx.push_back(x);
		vy.push_back(y);
	}
	sort(all(vx)); vx.resize(unique(all(vx)) - vx.begin());
	sort(all(vy)); vy.resize(unique(all(vy)) - vy.begin());
	for(auto &[x, y] : a){
		x = lower_bound(all(vx), x) - vx.begin();
		y = lower_bound(all(vy), y) - vy.begin();
	}
	vector<pi> intervals(sz(vx) - 1, pi(1e9, -1e9));
	for(int i = 0; i < sz(a); i++){
		auto x = a[i];
		auto y = a[(i + 1) % sz(a)];
		if(x.first == y.first) continue;
		if(x > y) swap(x, y);
		assert(x.second == y.second);
		for(int j = x.first; j < y.first; j++){
			intervals[j].first = min(intervals[j].first, y.second);
			intervals[j].second = max(intervals[j].second, y.second);
		}
	}
	vector<pi> v;
	for(auto &i : intervals){
		if(!sz(v)){
			v.push_back(i);
			continue;
		}
		if(in(v.back(), i) || in(i, v.back())) v.push_back(i);
		else{
			pi j = i;
			j.first = max(j.first, v.back().first);
			j.second = min(j.second, v.back().second);
			v.push_back(j);
			v.push_back(i);
		}
	}
	cout << solve(v) << endl;
}
