#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<lint, lint> pi;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXN = 250005;

struct point{
	lint x, y;
}a[MAXN];

lint dist(point x, point y){ return abs(x.x - y.x) + abs(x.y - y.y); }

int n, f[MAXN];
lint d[MAXN];

bool trial(lint X){
	vector<pair<int, int>> rng(n);
	for(int i=0; i<n; i++) rng[i] = make_pair(i + 1, n);
	{
		int ptr = 0;
		for(int i=0; i<n; i++){
			while(ptr < n && d[ptr] - d[i] <= X) ptr++;
			f[i] = ptr;
		}
	}
	if(f[0] == n) return 1;
	{
		deque<pi> dq;
		int ptr = 0;
		int fptr = 0;
		for(int i=0; i<n; i++){
			fptr = max(fptr, i);
			while(sz(dq) && dq[0].second < i) dq.pop_front();
			while(ptr < n){
				lint tot_tour = d[ptr] - d[i] + dist(a[i], a[ptr]);
				while(fptr < n && f[fptr] <= ptr && (!sz(dq) || dq[0].first >= tot_tour - X)){
					auto ins = pi(d[f[fptr]] - d[fptr], fptr);
					while(sz(dq) && dq.back().first >= ins.first) dq.pop_back();
					dq.push_back(ins);
					fptr++;
				}
				if(sz(dq) && dq[0].first < tot_tour - X) break;
				ptr++;
			}
			rng[i].second = min(rng[i].second, ptr);
		}
	}
	{
		int pos = upper_bound(d, d + n, X) - d;
		int r = 0;
		for(int i=0; i<n; i++){
			r = max(r, i);
			while(r < n && d[i] + dist(a[i], a[r]) + d[n - 1] - d[r] > X) r++;
			rng[i].first = max(rng[i].first, r);
		}
		r = n - 1;
		for(int i=0; i<pos; i++){
			while(r > pos && d[i] + dist(a[i], a[r]) + d[r] - d[pos] > X) r--;
			rng[i].second = min(rng[i].second, r + 1);
		}
	}
	int qos = lower_bound(d, d + n, d[n-1] - X) - d - 1;
	auto f = [&](int l, int r){
		if(l < qos && qos < r && d[n-1] - d[r] + dist(a[l], a[r]) + d[qos] - d[l] > X) return 0;
		return 1;
	};
	for(int i=0; i<n; i++){
		if(rng[i].first >= rng[i].second) continue;
		if(f(i, rng[i].first)) return 1;
		if(f(i, rng[i].second - 1)) return 1;
	}
	return 0;
}

lint shortcut(int _n, vector<lint> X, vector<lint> Y){
	n = _n;
	for(int i=0; i<n; i++) a[i] = {X[i], Y[i]};
	for(int i=1; i<n; i++) d[i] = d[i-1] + dist(a[i-1], a[i]);
	lint s = 0, e = 1e15;
	while(s != e){
		lint m = (s+e)/2;
		if(trial(m)) e = m;
		else s = m + 1;
	}
	return s;
}


