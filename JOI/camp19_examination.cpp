#include <bits/stdc++.h>
using namespace std;
const int MAXN = 200005;
using lint = long long;
using pi = pair<int, int>;

struct pnt{
	int x, y, z, idx;
	bool operator<(const pnt &p)const{
		return make_tuple(x, y, z, idx) < make_tuple(p.x, p.y, p.z, p.idx);
	}
}a[MAXN];

struct foo{
	int x, y, idx;
	bool operator<(const foo &f)const{
		return pi(x, idx) < pi(f.x, f.idx);
	}
};

struct bit{
	int tree[MAXN];
	void add(int x, int v){
		while(x < MAXN){
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

int n, q, ret[MAXN];

void solve(int s, int e){
	if(s == e) return;
	int m = (s + e) / 2;
	solve(s, m); solve(m + 1, e);
	vector<foo> v; 
	for(int i=s; i<=m; i++){
		if(a[i].idx == -1) v.push_back({a[i].y, a[i].z, -1});
	}
	for(int i=m+1; i<=e; i++){
		if(a[i].idx != -1) v.push_back({a[i].y, a[i].z, a[i].idx});
	}
	sort(v.begin(), v.end());
	for(auto &i : v){
		if(i.idx == -1) bit.add(i.y, 1);
		else ret[i.idx] += bit.query(i.y);
	}
	for(auto &i : v){
		if(i.idx == -1) bit.add(i.y, -1);
	}
}

int main(){
	scanf("%d %d",&n,&q);
	for(int i=0; i<n; i++){
		int x, y; scanf("%d %d",&x,&y);
		a[i] = {-x, -y, -x-y, -1};
	}
	for(int i=0; i<q; i++){
		int x, y, z; scanf("%d %d %d",&x,&y,&z);
		a[i + n] = {-x, -y, -z, i};
	}
	vector<int> vx, vy, vz;
	for(int i=0; i<n; i++){
		vx.push_back(a[i].x); vy.push_back(a[i].y); vz.push_back(a[i].z);
	}
	vx.push_back(-2e9);
	vy.push_back(-2e9);
	vz.push_back(-2e9);
	sort(vx.begin(), vx.end());
	sort(vy.begin(), vy.end());
	sort(vz.begin(), vz.end());
	vx.resize(unique(vx.begin(), vx.end()) - vx.begin());
	vy.resize(unique(vy.begin(), vy.end()) - vy.begin());
	vz.resize(unique(vz.begin(), vz.end()) - vz.begin());
	for(int i=0; i<n; i++){
		a[i].x = lower_bound(vx.begin(), vx.end(), a[i].x) - vx.begin();
		a[i].y = lower_bound(vy.begin(), vy.end(), a[i].y) - vy.begin();
		a[i].z = lower_bound(vz.begin(), vz.end(), a[i].z) - vz.begin();
	}
	for(int i=0; i<q; i++){
		a[i+n].x = upper_bound(vx.begin(), vx.end(), a[i+n].x) - vx.begin() - 1;
		a[i+n].y = upper_bound(vy.begin(), vy.end(), a[i+n].y) - vy.begin() - 1;
		a[i+n].z = upper_bound(vz.begin(), vz.end(), a[i+n].z) - vz.begin() - 1;
	}
	sort(a, a + n + q);
	solve(0, n + q - 1);
	for(int i=0; i<q; i++) printf("%d\n", ret[i]);
}
