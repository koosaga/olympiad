// shirley smokes weed
#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXN = 100005;

int n;
vector<pi> a;

int count(int v, int l, int r){
	return upper_bound(all(a), pi(v, r)) - lower_bound(all(a), pi(v, l));
}

int main(){
	scanf("%d",&n);
	for(int i=0; i<n; i++){
		int v; scanf("%d",&v);
		a.emplace_back(v, i);
	}
	sort(all(a));
	vector<pi> grp;
	for(int i=0; i<sz(a); ){
		int e = i;
		while(e < sz(a) && a[e].first == a[i].first) e++;
		grp.emplace_back(i, e - 1);
		i = e;
	}
	int ret = 0;
	for(int i=0; i<sz(grp); i++){
		ret = max(ret, grp[i].second - grp[i].first + 1);
		if(i > 0){
			for(int j = grp[i].first; j <= grp[i].second; j++){
				int pval = a[grp[i-1].second].first;
				int cnt = count(pval, 0, a[j].second - 1);
				ret = max(ret, grp[i].second + 1 - j + cnt);
			}
		}
	}
	for(int i=0; i<sz(grp); ){
		int e = i;
		while(e + 1 < sz(grp) && a[grp[e].second].second < a[grp[e + 1].first].second) e++;
		int gs = 0;
		for(int j = i; j <= e; j++){
			gs += grp[j].second - grp[j].first + 1;
		}
		if(i > 0) gs += count(a[grp[i-1].second].first, 0, a[grp[i].first].second);
		if(e + 1 < sz(grp)) gs += count(a[grp[e+1].second].first, a[grp[e].second].second, n);
		ret = max(ret, gs);
		i = e + 1;
	}
	cout << n - ret << endl;
}
