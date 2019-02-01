#include <bits/stdc++.h>
using namespace std;
const int MAXN = 400005;
typedef long long lint;
typedef pair<int, int> pi;

int n, m;

struct elem{
	int x, y, c;
	int indp;
	bool operator<(const elem &e)const{
		return pi(x, y) < pi(e.x, e.y);
	}
};

struct seg{
	lint mxv[1050005];
	lint lzy[1050005];
	void lazydown(int p){
		mxv[2*p] += lzy[p];
		lzy[2*p] += lzy[p];
		mxv[2*p+1] += lzy[p];
		lzy[2*p+1] += lzy[p];
		mxv[2*p] = max(mxv[2*p], mxv[p]);
		mxv[2*p+1] = max(mxv[2*p+1], mxv[p]);
		lzy[p] = 0;
	}
	void add(int s, int e, int ps, int pe, int p, int v){
		if(e < ps || pe < s) return;
		if(s <= ps && pe <= e){
			lzy[p] += v;
			mxv[p] += v;
			return;
		}
		lazydown(p);
		int pm = (ps + pe) / 2;
		add(s, e, ps, pm, 2*p, v);
		add(s, e, pm+1, pe, 2*p+1, v);
	}
	void upd(int s, int e, int ps, int pe, int p, lint v){
		if(e < ps || pe < s) return;
		if(s <= ps && pe <= e){
			mxv[p] = max(mxv[p], v);
			return;
		}
		lazydown(p);
		int pm = (ps + pe) / 2;
		upd(s, e, ps, pm, 2*p, v);
		upd(s, e, pm+1, pe, 2*p+1, v);
	}
	lint query(int pos, int ps, int pe, int p){
		if(ps == pe) return mxv[p];
		int pm = (ps+pe)/2;
		lazydown(p);
		if(pos <= pm) return query(pos, ps, pm, 2*p);
		return query(pos, pm+1, pe, 2*p+1);
	}
}seg;

vector<elem> v;
vector<lint> vx, vy;
lint dp[MAXN];

lint solve(){
	for(int i=0; i<v.size(); ){
		int e = i;
		while(e < v.size() && v[i].x == v[e].x) e++;
		for(int j=i; j<e; j++){
			seg.add(0, v[j].y - 1, 0, vy.size() + 1, 1, v[j].c);
		}
		for(int j=i; j<e; j++){
			if(v[j].indp) dp[j] = seg.query(v[j].y, 0, vy.size() + 1, 1);
		}
		for(int j=i; j<e; j++){
			if(v[j].indp) seg.upd(0, v[j].y - 1, 0, vy.size() + 1, 1, dp[j]);
		}
		i = e;
	}
	return dp[v.size() - 1];
}

lint x[MAXN], y[MAXN], c[MAXN];

int main(){
	int aa, bb;
	scanf("%d %d %d %d",&n,&m,&aa,&bb);
	for(int i=0; i<n+m; i++){
		int ix, iy, ic;
		scanf("%d %d %d",&ix,&iy,&ic);
		x[i] = 1ll * aa * iy - 1ll * bb * ix;
		y[i] = 1ll * aa * iy + 1ll * bb * ix;
		c[i] = (i >= n ? -ic : ic);
	}
	for(int i=0; i<n+m; i++){
		vx.push_back(x[i]);
		vy.push_back(y[i]);
	}
	sort(vx.begin(), vx.end());
	sort(vy.begin(), vy.end());
	vx.resize(unique(vx.begin(), vx.end()) - vx.begin());
	vy.resize(unique(vy.begin(), vy.end()) - vy.begin());
	for(int i=0; i<n+m; i++){
		x[i] = lower_bound(vx.begin(), vx.end(), x[i]) - vx.begin() + 1;
		y[i] = lower_bound(vy.begin(), vy.end(), y[i]) - vy.begin() + 1;
		v.push_back({x[i], y[i], c[i], i >= n});
	}
	v.push_back({0, vy.size() + 1, 0, 1});
	v.push_back({vx.size() + 1, 0, 0, 1});
	sort(v.begin(), v.end());
	cout << solve() << endl;
}

