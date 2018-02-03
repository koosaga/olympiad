#include <bits/stdc++.h>
using namespace std;
const int MAXN = 500005;
typedef long long lint;
typedef pair<int, int> pi;

double cur_pos;
int n;

struct circ{
	int x, y, r, t, idx;
};

double func(circ c){
	double dx = abs(c.x - cur_pos);
	double r = (c.r - 0.001);
	double y = sqrt(r * r - dx * dx);
	if(c.t == 0) return c.y - y;
	return c.y + y;
}

bool same(circ a, circ b){
	return a.idx == b.idx && a.t == b.t;
}

auto cmp = [](circ a, circ b){ return func(a) < func(b); };
set<circ, decltype(cmp)> s(cmp);

struct event{
	circ val;
	int pos, mode;
	bool operator<(const event &e)const{
		return pi(pos, mode) < pi(e.pos, e.mode);
	}
};

vector<event> v;
int x[MAXN], y[MAXN], r[MAXN];
vector<pi> cnd;

bool ok(int p, int q){
	if(x[p] + r[p] == x[q] - r[q]) return 0;
	if(x[p] - r[p] == x[q] + r[q]) return 0;
	int dx = x[p] - x[q];
	int dy = y[p] - y[q];
	int rr = r[p] + r[q];
	return 1ll * dx * dx + 1ll * dy * dy == 1ll * rr * rr;
}

lint solve_case(){
	vector<pi> lx, rx;
	for(int i=0; i<n; i++){
		lx.emplace_back(x[i] - r[i], y[i]);
		rx.emplace_back(x[i] + r[i], y[i]);
	}
	sort(lx.begin(), lx.end());
	sort(rx.begin(), rx.end());
	lint ans = 0;
	for(auto &i : lx){
		if(binary_search(rx.begin(), rx.end(), i)) ans++;
	}
	return ans;
}

lint solve(vector<pi> v){
	set<pi> s;
	for(auto &i : v){
		if(i.first == i.second) continue;
		if(i.first > i.second) swap(i.first, i.second);
		if(!ok(i.first, i.second)) continue;
		if(s.find(i) != s.end()) continue;
		s.insert(i);
	}
	return s.size();
}

int main(){
	scanf("%d",&n);
	for(int i=0; i<n; i++){
		scanf("%d %d %d",&x[i],&y[i],&r[i]);
		circ c1 = {x[i], y[i], r[i], 0, i};
		circ c2 = {x[i], y[i], r[i], 1, i};
		v.push_back({c1, x[i] - r[i], 1});
		v.push_back({c2, x[i] - r[i], 1});
		v.push_back({c1, x[i] + r[i], 0});
		v.push_back({c2, x[i] + r[i], 0});	
	}
	sort(v.begin(), v.end());
	for(auto &i : v){
		if(i.mode == 0){
			cur_pos = i.pos - 0.01;
			auto l = s.lower_bound(i.val);
			if(l == s.end() || !same(*l, i.val)) l--;
			assert(same(*l, i.val));
			s.erase(l);
			l = s.lower_bound(i.val);
			int lidx = -1, ridx = -1;
			if(l != s.end()){
				ridx = l->idx;
			}
			if(l != s.begin()){
				l--;
				lidx = l->idx;
			}
			if(lidx != -1 && ridx != -1) cnd.emplace_back(lidx, ridx);
		}
		else{
			cur_pos = i.pos + 0.01;
			auto l = s.lower_bound(i.val);
			if(l != s.end()){
				cnd.emplace_back(i.val.idx, l->idx);
			}
			if(l != s.begin()){
				l--;
				cnd.emplace_back(i.val.idx, l->idx);
			}
			s.insert(i.val);
		}
	}
	cout << solve(cnd) + solve_case() << endl;
}
