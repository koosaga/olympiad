#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<lint, lint>;
const int MAXN = 100005;
const int MAXT = 270000;

struct seg{
	int tree[MAXT], lim;
	void init(int n){
		for(lim = 1; lim <= n; lim <<= 1);
		fill(tree, tree + 2 * lim, -1e9);
	}
	void upd(int x, int v){
		x += lim;
		tree[x] = max(tree[x], v);
		while(x > 1){
			x >>= 1;
			tree[x] = max(tree[x], v);
		}
	}
	int query(int s, int e){
		s += lim;
		e += lim;
		int ret = -1e9;
		while(s < e){
			if(s%2 == 1) ret = max(ret, tree[s++]);
			if(e%2 == 0) ret = max(ret, tree[e--]);
			s >>= 1;
			e >>= 1;
		}
		if(s == e) ret = max(ret, tree[s]);
		return ret;
	}
}seg1, seg2;

struct seg2{
	int lim;
	pi tree[MAXT];
	set<pi> s[MAXN];
	void init(int n){
		for(lim = 1; lim <= n; lim <<= 1);
		fill(tree, tree + 2 * lim, pi(1e9, 1e9));
		for(int i=0; i<MAXN; i++) s[i].clear();
	}
	void insert(int pos, pi val){
		s[pos].insert(val);
		tree[pos + lim] = *s[pos].begin();
		pos += lim;
		while(pos > 1){
			pos >>= 1;
			tree[pos] = min(tree[2*pos], tree[2*pos+1]);
		}
	}
	void erase(int pos, pi val){
		s[pos].erase(val);
		tree[pos + lim] = (s[pos].empty() ? pi(1e9, 1e9) : *s[pos].begin());	
		pos += lim;
		while(pos > 1){
			pos >>= 1;
			tree[pos] = min(tree[2*pos], tree[2*pos+1]);
		}
	}
	pi query(int l, int r){
		l += lim;
		r += lim;
		pi ans(1e9, 1e9);
		while(l < r){
			if(l % 2 == 1) ans = min(ans, tree[l++]);
			if(r % 2 == 0) ans = min(ans, tree[r--]);
			l >>= 1;
			r >>= 1;
		}
		if(l == r) ans = min(ans, tree[l]);
		return ans;
	}
}seg3, seg4;

struct punk{
	lint first, second;
	int idx;
	punk(lint x, lint y, int i){
		first = x, second = y, idx = i;
	}
};

int rem[MAXN], t[MAXN];
lint x[MAXN], y[MAXN];

void solve(){
	vector<lint> vx1, vy1, vx2, vy2;
	int n;
	char buf[5];
	cin >> n;
	int cnt = 0;
	for(int i=0; i<n; i++){
		scanf("%lld %lld %s",&x[i],&y[i],buf);
		t[i] = (*buf == 'N');
		vx1.push_back(y[i] - 2 * x[i]);
		vy1.push_back(y[i] + 2 * x[i]);
		vx2.push_back(y[i] - x[i]);
		vy2.push_back(y[i] + x[i]);
	}
	sort(vx1.begin(), vx1.end());
	sort(vy1.begin(), vy1.end());
	sort(vx2.begin(), vx2.end());
	sort(vy2.begin(), vy2.end());
	seg1.init(n);
	seg2.init(n);
	seg3.init(n);
	seg4.init(n);
	for(int i=0; i<n; i++){
		int px1 = lower_bound(vx1.begin(), vx1.end(), y[i] - 2 * x[i]) - vx1.begin();
		int py1 = lower_bound(vy1.begin(), vy1.end(), y[i] + 2 * x[i]) - vy1.begin();
		int px2 = lower_bound(vx2.begin(), vx2.end(), y[i] - 1 * x[i]) - vx2.begin();
		int py2 = lower_bound(vy2.begin(), vy2.end(), y[i] + 1 * x[i]) - vy2.begin();
		if(seg1.query(px1, n) >= py1 || seg2.query(px2, n) >= py2){
			puts("FAIL");
			continue;
		}
		if(t[i]){
			while(true){
				auto l = seg3.query(0, px1);
				if(l.first > py1) break;
				if(!rem[l.second]){
					rem[l.second] = 1;
					cnt--;
				}
				int ipx1 = lower_bound(vx1.begin(), vx1.end(), y[l.second] - 2 * x[l.second]) - vx1.begin();
				seg3.erase(ipx1, l);
			}
			seg1.upd(px1, py1);
			seg3.insert(px1, pi(py1, i));
			seg4.insert(px2, pi(py2, i));
		}
		else{
			while(true){
				auto l = seg4.query(0, px2);
				if(l.first > py2) break;
				if(!rem[l.second]){
					rem[l.second] = 1;
					cnt--;
				}
				int ipx2 = lower_bound(vx2.begin(), vx2.end(), y[l.second] - 1 * x[l.second]) - vx2.begin();
				seg4.erase(ipx2, l);
			}
			seg2.upd(px2, py2);
			seg3.insert(px1, pi(py1, i));
			seg4.insert(px2, pi(py2, i));
		}
		cnt++;
		printf("%d\n", cnt);
	}
}

void clear(){
	memset(rem, 0, sizeof(rem));
}

int main(){
	int tc; cin >> tc;
	while(tc--){
		solve();
		clear();
	}
}
