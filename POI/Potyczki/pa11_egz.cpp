#include <bits/stdc++.h>
const int MAXN = 100005;
using namespace std;
typedef pair<int, int> pi;

int n, a, b, x[MAXN], y[MAXN], r[MAXN], ret[MAXN];

struct pnt{
	int x, y, r;
	bool operator<(const pnt &p)const{
		return pi(x, y) < pi(p.x, p.y);
	}
};

struct bit{
	int tree[MAXN];
	void add(int x, int v){
		x++;
		while(x < MAXN){
			tree[x] += v;
			x += x & -x;
		}
	}
	int query(int x){
		int ret = 0;
		x++;
		while(x){
			ret += tree[x];
			x -= x & -x;
		}
		return ret;
	}
	void clear(int n){
	n += 3;
		memset(tree, 0, sizeof(int) * n);
	}
}bit;

#define y1 fuck_gcc


void Do(vector<pnt> a, vector<pnt> b, int x1, int x2, int y1, int y2){
	vector<int> vy;
	for(int i=0; i<a.size(); i++){
		vy.push_back(a[i].y);
	}
	sort(vy.begin(), vy.end());
	vy.resize(unique(vy.begin(), vy.end()) - vy.begin());
	for(int i=0; i<a.size(); i++){
		a[i].y = lower_bound(vy.begin(), vy.end(), a[i].y) - vy.begin();
		a[i].y++;
	}
	bit.clear(vy.size());
	int p = 0, q = 0;
	for(auto &i : b){
		while(q < a.size() && a[q].x <= i.x + x2 - 1){
			bit.add(a[q++].y, 1);
		}
		while(p < a.size() && a[p].x <= i.x - x1){
			bit.add(a[p++].y, -1);
		}
		auto pl = upper_bound(vy.begin(), vy.end(), i.y - y1);
		auto pr = lower_bound(vy.begin(), vy.end(), i.y + y2);
		if(bit.query(pr - vy.begin()) != bit.query(pl - vy.begin())){
			ret[i.r] = 1;
		}	
	}
}

void solve(int s, int e){
	if(s == e) return;
	int m = (s+e)/2;
	solve(s, m);
	solve(m+1, e);
	vector<pnt> a1, a2, b1, b2;
	for(int i=s; i<=m; i++){
		if(r[i] == 0) a1.push_back({x[i], y[i], i});
		else a2.push_back({x[i], y[i], i});
	}
	for(int i=m+1; i<=e; i++){
		if(r[i] == 0) b1.push_back({x[i], y[i], i});
		else b2.push_back({x[i], y[i], i});
	}
	sort(a1.begin(), a1.end());
	sort(a2.begin(), a2.end());
	sort(b1.begin(), b1.end());
	sort(b2.begin(), b2.end());
	Do(a1, b1, a, a, b, b);
	Do(a1, b2, a, b, b, a);
	Do(a2, b1, b, a, a, b);
	Do(a2, b2, b, b, a, a);
}

int main(){
	scanf("%d %d %d",&n,&a,&b);
	swap(a, b);
	for(int i=n-1; i>=0; i--) scanf("%d %d %d",&x[i],&y[i],&r[i]);
	solve(0, n-1);
	cout << count(ret, ret + n, 0) << endl;
	for(int i=n-1; i>=0; i--) if(!ret[i]) printf("%d ", n-i);
}