// Let's study BOJ 17461! https://www.dropbox.com/s/57m4x4ae7dqpacz/gp5div1sol.pdf?dl=0

#include <bits/stdc++.h>
using namespace std;
const int MAXN = 200005;
const int MAXT = 530005;
using pi = pair<int, int>;
using lint = long long;
#define sz(v) ((int)(v).size())

struct seg{
	int tree[MAXT], lim;
	void init(vector<int> &a){
		for(lim = 1; lim <= sz(a); lim <<= 1);
		memset(tree, 0x3f, sizeof(tree));
		for(int i=0; i<sz(a); i++){
			tree[i + lim] = a[i];
		}
		for(int i=lim-1; i; i--) tree[i] = min(tree[2*i], tree[2*i+1]);
	}
	int query(int s, int e){
		s += lim;
		e += lim;
		int ret = 1e9;
		while(s < e){
			if(s%2 == 1) ret = min(ret, tree[s++]);
			if(e%2 == 0) ret = min(ret, tree[e--]);
			s >>= 1;
			e >>= 1;
		}
		if(s == e) ret = min(ret, tree[s]);
		return ret;
	}
}seg;

struct point{
	pi p; int l, r;
};

lint cost(pi x, pi y){ return 1ll * (y.first - x.first) * (x.second + y.second); }

lint optimal_search(vector<pi> &v, vector<point> &w){
	auto overtake = [&](int x, int y){ // given x < y, return range [0, ret) that x is efficient 
		int s = 0, e = v.size();
		while(s != e){
			int m = (s + e) / 2;
			if(cost(v[m], w[x].p) < cost(v[m], w[y].p)) e = m;
			else s = m + 1;
		}
		return s;
	};
	lint ret = 0;
	for(int i=0; i<w.size(); ){
		int e = i;
		while(e < w.size() && w[i].l - 1 <= w[e].r) e++;
		// two ranges : [w[e - 1].l, w[i].l - 1] | [w[i].l, w[i].r]
		vector<int> hull;
		int unsolved = w[i].r;
		for(int j=i; j<e; j++){
			while(hull.size() >= 2 && overtake(hull[hull.size() - 2], hull.back()) >= overtake(hull.back(), j)){
				hull.pop_back();
			}
			hull.push_back(j);
			int thres = (j + 1 < e ? w[j+1].r : (w[i].l - 1));
			while(unsolved > thres){
				while(hull.size() >= 2 && overtake(hull[hull.size() - 2], hull.back()) > unsolved){
					hull.pop_back();
				}
				ret = max(ret, cost(v[unsolved--], w[hull.back()].p));
			}
		}
		hull.clear();
		unsolved = w[e - 1].l;
		for(int j=e-1; j>i; j--){
			while(hull.size() >= 2 && overtake(hull.back(), hull[hull.size() - 2]) <= overtake(j, hull.back())){
				hull.pop_back();
			}
			hull.push_back(j);
			int thres = w[j - 1].l;
			while(unsolved < thres){
				while(hull.size() >= 2 && overtake(hull.back(), hull[hull.size() - 2]) <= unsolved) hull.pop_back();
				ret = max(ret, cost(v[unsolved++], w[hull.back()].p));
			}
		}
		i = e;
	}
	return ret;
}

struct rect{
	int s, e, x;
	bool operator<(const rect &r)const{
		return e - s < r.e - r.s;
	}
};

lint dnc_second(int l, int r, vector<rect> a, vector<rect> b){
	if(a.empty() || b.empty() || l == r) return 0;
	int m = (l + r) / 2;
	vector<rect> upa, dna, mia, upb, dnb, mib;
	for(auto i : a){
		if(i.e <= m) upa.push_back(i);
		else if(i.s <= m && m + 1 <= i.e){
			mia.push_back(i);
			upa.push_back(i);
		}
		else if(i.s > m){
			dna.push_back(i);
		}
		else assert(0); // ???
	}
	for(auto i : b){
		if(i.e <= m) upb.push_back(i);
		else if(i.s <= m && m + 1 <= i.e){
			mib.push_back(i);
			dnb.push_back(i);
		}
		else if(i.s > m) dnb.push_back(i);
		else assert(0);
	}
	lint ret = max(dnc_second(l, m, upa, upb), dnc_second(m+1, r, dna, dnb));
	if(mia.empty() || mib.empty()) return ret;
	// merge mia mib
	vector<pi> up;
	vector<point> dn;
	for(auto &i : mia) up.emplace_back(i.s, i.x);
	int lbnd = mia.size();
	int ubnd = mia.size();
	for(auto &i : mib){
		while(lbnd > 0 && mia[lbnd - 1].e >= i.e) lbnd--;
		while(ubnd > 0 && mia[ubnd - 1].s <= i.s) ubnd--;
		if(lbnd < ubnd){
			dn.push_back({pi(i.e, i.x), lbnd, ubnd - 1});
		}
	}
	if(!dn.empty()) ret = max(ret, optimal_search(up, dn));
	return ret;
}

vector<rect> generate_rectangle(vector<int> &a){
	vector<pi> stk;
	vector<rect> ans;
	for(int i=0; i<sz(a); i++){
		while(!stk.empty() && stk.back().second > a[i]){
			int correspL = (stk.size() >= 2 ? stk[stk.size() - 2].first : -1) + 1;
			int hV = stk.back().second;
			stk.pop_back();
			ans.push_back({correspL, i, hV});
		}
		stk.emplace_back(i, a[i]);
	}
	while(!stk.empty()){
		int correspL = (stk.size() >= 2 ? stk[stk.size()-2].first : -1) + 1;
		int hV = stk.back().second;
		stk.pop_back();
		ans.push_back({correspL, sz(a), hV});
	}
	return ans;
}

int main(){
	int n;
	scanf("%d",&n);
	vector<int> a(n), b(n);
	for(int i=0; i<n; i++) scanf("%d %d",&a[i],&b[i]);
	auto lv = generate_rectangle(a);
	auto rv = generate_rectangle(b);
	sort(lv.begin(), lv.end());
	sort(rv.rbegin(), rv.rend());
	seg.init(a);
	lint ret = 0;
	for(auto &i : rv){
		ret = max(ret, 1ll * (i.e - i.s) * (i.x + seg.query(i.s, i.e - 1)));
	}
	seg.init(b);
	for(auto &i : lv){
		ret = max(ret, 1ll * (i.e - i.s) * (i.x + seg.query(i.s, i.e - 1)));
	}
	ret = max(ret, dnc_second(0, n, lv, rv));
	reverse(lv.begin(), lv.end());
	reverse(rv.begin(), rv.end());
	ret = max(ret, dnc_second(0, n, rv, lv));
	cout << ret << endl;
}
