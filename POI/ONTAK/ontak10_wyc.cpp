#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, lint> pi;

lint l[100005];
lint w[100005];
lint dp[100005];
int n, d;

struct cht{
	vector<pi> v;
	vector<pi> b;
	void clear(){
		v.clear();
		b.clear();
	}
	llf crs(pi a, pi b){
		return (llf)(b.second - a.second) / (a.first - b.first);
	}
	void add_line(int x, lint y){
		b.insert(lower_bound(b.begin(), b.end(), pi(x, y)), pi(x, y));
		if(b.size() >= 200){
			vector<pi> nxt;
			int p = 0, q = 0;
			while(p < v.size() || q < b.size()){
				pi ins;
				if(q == b.size()) ins = v[p++];
				else if(p == v.size()) ins = b[q++];
				else if(v[p] < b[q]) ins = v[p++];
				else ins = b[q++];
				if(!nxt.empty() && nxt.back().first == ins.first) continue;
				while(nxt.size() >= 2 && crs(nxt[nxt.size()-2], nxt.back()) < crs(nxt.back(),ins)){
					nxt.pop_back();
				}
				nxt.push_back(ins);
			}
			b.clear();
			v = nxt;
		}
	}
	lint query(lint x){
		lint ret = 1e18;
		if(!v.empty()){
			int s = 0, e = v.size()-1;
			while(s != e){
				int m = (s+e)/2;
				if(v[m].first * x + v[m].second < v[m+1].first * x + v[m+1].second) e = m;
				else s = m+1;
			}
			ret = min(ret, v[s].first * x + v[s].second);
		}
		for(int i=0; i<b.size(); i++){
			ret = min(ret, b[i].first * x + b[i].second);
		}
		return ret;
	}
}cht;

void solve(int s, int e){
	if(s == e) return;
	int m = (s+e)/2;
	solve(s, m);
	int pnt = m;
	cht.clear();
	for(int i=e; i>m; i--){
		while(pnt >= s && l[i] - l[pnt] <= d){
			cht.add_line(w[pnt], w[pnt] * w[pnt] + dp[pnt]);
			pnt--;
		}
		dp[i] = min(dp[i], cht.query(-2*w[i]) + w[i] * w[i]);
	}
	solve(m+1, e);
}

int main(){
	scanf("%d %d",&n,&d);
	for(int i=1; i<=n; i++){
		scanf("%lld %lld",&l[i],&w[i]);
		l[i] += l[i-1];
		w[i] += w[i-1];
	}
	memset(dp, 0x3f, sizeof(dp));
	dp[0] = 0;
	solve(0, n);
	printf("%lld",dp[n]);
}
