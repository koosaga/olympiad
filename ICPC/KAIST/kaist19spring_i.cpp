#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
const int MAXN = 250005;

struct swp{
	int pos, l, r;
	bool operator<(const swp &s)const{
		return pos < s.pos;
	}
};

lint solve(int n, pi src, pi dst, vector<pi> p1, vector<pi> p2, vector<int> w){
	if(src > dst) swap(src, dst);
	vector<swp> seg;
	for(int i=0; i<n; i++){
		if(src.first < p1[i].first && p1[i].first < dst.first){
			seg.push_back({p1[i].first, p1[i].second, p2[i].second});
		}
	}
	set<pair<int, lint>> s;
	s.emplace(src.second, 0ll);
	sort(seg.begin(), seg.end());
	for(auto &i : seg){
		auto its = s.lower_bound(make_pair(i.l, -1ll));
		if(its == s.end() || its->first > i.r) continue;
		lint lmin = 1e18, rmin = 1e18;
		while(its != s.end() && its->first <= i.r){
			lmin = min(lmin, its->second + its->first - i.l);
			rmin = min(rmin, its->second + i.r - its->first);
			its = s.erase(its);
		}
		s.emplace(i.l, lmin);
		s.emplace(i.r, rmin);
	}
	if(s.begin()->first <= dst.second && dst.second <= s.rbegin()->first){
		lint ret = 1e18;
		for(auto &i : s){
			ret = min(ret, abs(dst.second - i.first) + i.second);
		}
		ret += dst.first - src.first;
		return ret;
	}
	return 1e18;
}

lint shortest_path(pi src, pi dst, vector<pi> p1, vector<pi> p2, vector<int> w){
	int n = w.size();
	lint ret = solve(n, src, dst, p1, p2, w);
	swap(src.first, src.second);
	swap(dst.first, dst.second);
	for(int i=0; i<n; i++){
		swap(p1[i].first, p1[i].second);
		swap(p2[i].first, p2[i].second);
	}
	ret = min(ret, solve(n, src, dst, p1, p2, w));
	if(ret > 1e13) ret = abs(src.first - dst.first) + abs(src.second - dst.second);
	return ret;
}

int main(){
	int n; pi x, y;
	scanf("%d %d %d %d %d",&n,&x.first,&x.second,&y.first,&y.second);
	vector<pi> st(n);
	vector<pi> ed(n);
	vector<int> w(n);
	for(int i=0; i<n; i++){
		scanf("%d %d %d %d",&st[i].first,&st[i].second,&ed[i].first,&ed[i].second);
	}
	printf("%lld\n", shortest_path(x, y, st, ed, w));
}
