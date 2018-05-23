#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
using pi = pair<int, int>;
const int mod = 1e9 + 9;
const int MAXN = 505;

int n;
pi s[MAXN], e[MAXN], p;

bool in(pi s, pi x, pi e){
	return s.first <= x.first && x.first <= e.first && s.second <= x.second && x.second <= e.second;
}

bool cross(int idx, pi x, pi y){
	return max(x.first, s[idx].first) <= min(y.first, e[idx].first) &&
		max(x.second, s[idx].second) <= min(y.second, e[idx].second);
}

bool trial(int x){
	int lx = -x+1, ly = -x+1;
	int rx = x-1, ry = x-1;
	bool vis[MAXN] = {};
	while(!in(pi(lx, ly), p, pi(rx, ry))){
		bool disc = false;
		for(int j=0; j<n; j++){
			if(!vis[j] && cross(j, pi(lx, ly), pi(rx, ry))){
				disc = true;
				vis[j] = 1;
				lx = min(lx, s[j].first);
				rx = max(rx, e[j].first);
				ly = min(ly, s[j].second);
				ry = max(ry, e[j].second);
			}
		}
		if(!disc) return true;
	}
	return false;
}

int main(){
	cin >> p.first >> p.second >> n;
	for(int i=0; i<n; i++){
		cin >> s[i].first >> s[i].second;
		cin >> e[i].first >> e[i].second;
		if(s[i] > e[i]) swap(s[i], e[i]);
	}
	int s = 0, e = 1e6;
	while(s != e){
		int m = (s+e+1)/2;
		if(trial(m)) s = m;
		else e = m-1;
	}
	cout << s << endl;
}
