#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
const int mod = 1e9 + 7;
typedef pair<int, int> pi;

int n, m;
int w[255], t[255], d[255];
double disc[10005];
lint dp[10005];
vector<pi> v;

double solve(int x){
	if(v.empty()){
		return x == 0 ? 0 : -1e18;
	}
	double s = -1e9, e = 1e4;
	for(int i=0; i<100; i++){
		double m = (s+e)/2;
		double tmp = 0;
		for(auto &j : v){
			if(j.second == 0){
				if(j.first >= m){
					tmp = x + 100;
					break;
				}
			}
			else tmp += max(j.first - m, 0.0) / j.second;
		}
		if(tmp < x) e = m;
		else s = m;
	}
	double ans = 0;
	double tmp = 0;
	for(auto &j : v){
		if(j.second != 0){
			double w = max(j.first - s, 0.0) / j.second;
			tmp += w;
			ans += j.first * w - w * w * j.second / 2;
		}
	}
	ans += (x - tmp) * s;
	return ans;
}

struct cht{
	lint pa[10005], pb[10005];
	int sz = 0;
	void clear(){ sz = 0; }
	double cross(int x, int y){
		return 1.0 * (pb[y] - pb[x]) / (pa[x] - pa[y]);
	}
	void add(lint x, lint y){
		pa[sz] = x;
		pb[sz] = y;
		while(sz >= 2 && (llf)(pb[sz-2] - pb[sz-1]) * (pa[sz] - pa[sz-1]) >
				(llf)(pb[sz-1] - pb[sz]) * (pa[sz-1] - pa[sz-2])){
			pa[sz-1] = pa[sz];
			pb[sz-1] = pb[sz];
			sz--;
		}
		sz++;
	}
	lint query(int x){
		int s = 0, e = sz-1;
		while(s != e){
			int m = (s+e)/2;
			if(pa[m] * x + pb[m] > pa[m+1] * x + pb[m+1]) e = m;
			else s = m+1;
		}
		return pa[s] * x + pb[s];
	}
}cht;

int main(){
	int k;
	cin >> k >> m;
	while(k--){
		char buf[5];
		scanf("%s",buf);
		if(*buf == 'C'){
			int x, y;
			scanf("%d %d",&x,&y);
			v.push_back(pi(x, y));
		}
		else{
			n++;
			scanf("%d %d %d",&w[n],&t[n],&d[n]);
		}
	}
	for(int i=1; i<=m; i++){
		dp[i] = -1e18;
	}
	double ret = -1e18;
	for(int i=1; i<=n; i++){
		for(int j=0; j<=m && j<w[i]; j++){
			vector<lint> v;
			for(int k=j; k<=m; k+=w[i]){
				int idx = k / w[i];
				v.push_back(dp[k] - idx * t[i] - (1ll * idx * (idx + 1) / 2) * d[i]);
			}
			cht.clear();
			for(int k=j; k<=m; k+=w[i]){
				int idx = k / w[i];
				cht.add(idx, v[idx]);
				dp[k] = cht.query(idx * d[i]) + idx * t[i] - 1ll * (idx * (idx - 1) / 2) * d[i];
			}
		}
	}
	for(int i=0; i<=m; i++){
		ret = max(ret, solve(i) + dp[m-i]);
	}
	if(ret < -1e17) cout << "impossible";
	else printf("%.10f\n", ret);
}

