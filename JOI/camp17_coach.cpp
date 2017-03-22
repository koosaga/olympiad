#include <bits/stdc++.h>
typedef long long lint;
typedef long double llf;
using namespace std;
typedef pair<lint, lint> pi;

lint x, n, m, w, t;
lint s[200005], dp[200005], ps[200005];
pi a[200005];
int nxt[200005];

lint get(lint e, lint x){
	return (e - x + t) / t;
}

vector<pi> v;
vector<pi> stk;

llf crs(pi x, pi y){
	return (llf)(y.second - x.second) / (x.first - y.first);
}

void add_line(lint x, lint y){
	stk.insert(lower_bound(stk.begin(), stk.end(), pi(x, y)), pi(x, y));
	if(stk.size() >= 500){
		vector<pi> nxt(v.size() + stk.size());
		merge(v.begin(), v.end(), stk.begin(), stk.end(), nxt.begin());
		v.clear();
		stk.clear();
		for(auto &i : nxt){
			if(!v.empty() && v.back().first == i.first) continue;
			while(v.size() >= 2 && crs(v[v.size()-2], v.back()) < crs(v.back(), i)){
				v.pop_back();
			}
			v.push_back(i);
		}
	}
}

lint query(int x){
	lint ans = 4e18;
	for(auto &i : stk) ans = min(ans, i.first * x + i.second);
	if(!v.empty()){
		int s = 0, e = v.size() - 1;
		while(s != e){
			int m = (s+e)/2;
			if(v[m].first * x + v[m].second < v[m+1].first * x + v[m+1].second) e = m;
			else s = m+1;
		}
		ans = min(ans, v[s].first * x + v[s].second);
	}
	return ans;
}

int main(){
	cin >> x >> n >> m >> w >> t;
	for(int i=0; i<n; i++){
		scanf("%lld",&s[i]);
	}
	s[n] = x;
	n++;
	sort(s, s+n, [&](const lint &a, const lint &b){
		return a%t < b%t;
	});
	for(int i=0; i<m; i++){
		scanf("%lld %lld",&a[i].first,&a[i].second);
	}
	sort(a, a+m);
	for(int i=m-1; i>=0; i--){
		ps[i] = ps[i+1] + a[i].second;
	}
	int p = m;
	for(int i=n-1; i>=0; i--){
		while(p > 0 && a[p-1].first > s[i] % t){
			p--;
		}
		nxt[i] = p;
	}
	lint aux = 0;
	p = n;
	for(int i=m-1; i>=0; i--){
		while(p > 0 && nxt[p-1] == i+1){
			p--;
			dp[p] = aux - ps[i+1];
			add_line((s[p] / t) * w, dp[p] + (s[p] / t) * w * nxt[p]);
		}
		aux += get(x, a[i].first) * w;
		aux = min(aux, query(-i) + ps[i]);
	}
	cout << aux + get(x, 0) * w;
}
