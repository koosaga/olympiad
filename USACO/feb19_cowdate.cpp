#include <bits/stdc++.h>
using namespace std;
using llf = double;
using pi = pair<llf, llf>;
const int MAXN = 1000005;

struct cht{
	vector<pi> v;
	int ptr = 0;
	void clear(){ v.clear(); ptr = 0; }
	bool bad(pi a, pi b, pi c){
		return (a.first - b.first) * (c.second - b.second) <= (b.first - c.first) * (b.second - a.second);
	}
	void add(pi x){
		while(v.size() >= 2 && bad(v[v.size()-2], v.back(), x)) v.pop_back();
		v.push_back(x);
	}
	llf query(llf x){
		while(ptr + 1 < v.size() && v[ptr].first * x + v[ptr].second < v[ptr+1].first * x + v[ptr+1].second){
			ptr++;
		}
		return v[ptr].first * x + v[ptr].second;
	}
}cht;

int n, a[MAXN];

llf solve(int l, int r){
	if(l == r) return (llf) a[l] / 1000000;
	int m = (l+r)/2;
	llf ret = max(solve(l, m), solve(m + 1, r));
	cht.clear();
	llf sum = 0, mul = 1;
	vector<pi> v, w;
	for(int i=m; i>=l; i--){
		sum += (llf) a[i] / (1000000 - a[i]);
		mul *= (llf) (1000000 - a[i]) / 1000000;
		v.emplace_back(sum, mul);
	}
	sum = 0, mul = 1;
	for(int i=m+1; i<=r; i++){
		sum += (llf) a[i] / (1000000 - a[i]);
		mul *= (llf) (1000000 - a[i]) / 1000000;
		w.emplace_back(sum, mul);
	}
	reverse(w.begin(), w.end());
	for(auto &i : w){
		cht.add(pi(i.second, i.first * i.second));
	}
	for(auto &i : v){
		ret = max(ret, cht.query(i.first) * i.second);
	}
	return ret;
}

int main(){
	freopen("cowdate.in", "r", stdin);
	freopen("cowdate.out", "w", stdout);
	scanf("%d",&n);
	for(int i=1; i<=n; i++) scanf("%d",&a[i]);
	printf("%.0f\n", floor(1000000 * solve(1, n) + 0.000001));
}
