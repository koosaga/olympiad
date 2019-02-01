#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<lint, lint> pi;
const int mod = 1e9 + 7;

struct tp{ 
	int r[4]; 
	bool operator<(const tp &a)const{
		return r[0] < a.r[0];
	}
}a[100005];

int n, k;

struct bit{
	int tree[100005];
	void add(int x, int v){
		while(x <= n){
			tree[x] += v;
			x += x & -x;
		}
	}
	int query(int x){
		int ret = 0;
		while(x){
			ret += tree[x];
			x -= x & -x;
		}
		return ret;
	}
}bit;

lint solve1(vector<int> v){
	lint ret = 0;
	for(int i=0; i<n; i++){
		ret += bit.query(v[i]);
		bit.add(v[i], 1);
	}
	for(int i=0; i<n; i++) bit.add(v[i], -1);
	return ret;
}

lint dnc(int s, int e, vector<pi> &v){
	if(s == e) return 0;
	int m = (s+e)/2;
	lint ret = dnc(s, m, v) + dnc(m+1, e, v);
	vector<pi> l, r;
	for(int i=s; i<=m; i++){
		l.push_back(v[i]);
	}
	for(int i=m+1; i<=e; i++){
		r.push_back(v[i]);
	}
	sort(l.begin(), l.end());
	sort(r.begin(), r.end());
	int pnt = 0;
	for(auto &i : r){
		while(pnt < l.size() && l[pnt].first < i.first){
			bit.add(l[pnt++].second, 1);
		}
		ret += bit.query(i.second);
	}
	for(int i=0; i<pnt; i++){
		bit.add(l[i].second, -1);
	}
	return ret;
}

lint solve2(vector<pi> v){
	return dnc(0, n-1, v);
}

int main(){
	scanf("%d %d",&n,&k);
	for(int i=0; i<k; i++){
		vector<int> v;
		for(int j=0; j<n; j++){
			scanf("%d",&a[j].r[i]);
			v.push_back(a[j].r[i]);
		}
		sort(v.begin(), v.end());
		for(int j=0; j<n; j++){
			a[j].r[i] = lower_bound(v.begin(), v.end(), a[j].r[i]) - v.begin() + 1;
		}
	}
	sort(a, a+n);
	if(k == 2){
		vector<int> v;
		for(int i=0; i<n; i++) v.push_back(a[i].r[1]);
		printf("%lld\n", solve1(v));
	}
	else if(k == 3){
		vector<pi> v;
		for(int i=0; i<n; i++) v.emplace_back(a[i].r[1], a[i].r[2]);
		printf("%lld\n", solve2(v));
	}
	else{
		vector<pi> v1, v2;
		vector<int> v3;
		for(int i=0; i<n; i++){
			v1.emplace_back(a[i].r[1], a[i].r[2]);
			v2.emplace_back(a[i].r[1], a[i].r[3]);
			v3.push_back(a[i].r[1]);
		}
		printf("%lld\n", solve2(v1) + solve2(v2) - solve1(v3));
	}
}
