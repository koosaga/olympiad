#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using llf = long double;
using pi = pair<int, int>;
const int MAXN = 100005;

struct disj{
	int pa[MAXN], sz[MAXN];
	void init(int n){
		iota(pa, pa + n, 0);
		fill(sz, sz + n, 1);
	}
	int find(int x){
		return pa[x] = (pa[x] == x ? x : find(pa[x]));
	}
	bool uni(int p, int q){
		p = find(p);
		q = find(q);
		if(p == q) return 0;
		pa[q] = p; sz[p] += sz[q]; return 1;
	}
}disj;

struct segment{
	int pos, s, e;
};

struct bit{
	int tree[MAXN];
	void add(int x, int v){
		for(int i = x + 2; i < MAXN; i += i & -i){
			tree[i] += v;
		}
	}
	int query(int x){
		int ret = 0;
		for(int i = x + 2; i; i -= i & -i){
			ret += tree[i];
		}
		return ret;
	}
	void clear(){
		memset(tree, 0, sizeof(tree));
	}
}bit;

vector<segment> generate_segments(vector<pi> a){
	struct event3{
		int yc, xs, xe, act;
		bool operator<(const event3 &b)const{
			return pi(yc, act) < pi(b.yc, b.act);
		}
	};
	int n = sz(a);
	vector<event3> points, events;
	set<int> s;
	vector<segment> rect_list;
	for(int i=0; i<n; i++){
		pi p1 = a[i];
		pi p2 = a[(i+1)%n];
		if(p1.first == p2.first){
			if(p1 > p2) swap(p1, p2);
			points.push_back({p1.second, p1.first, p1.first, +1});
			points.push_back({p2.second, p2.first, p2.first, -1});
		}
		if(p1.first < p2.first){
			events.push_back({p1.second, p1.first, p2.first, 0});
		}
		if(p1.first > p2.first){
			events.push_back({p1.second, p2.first, p1.first, 0});
		}
	}
	sort(all(points));
	sort(all(events));
	int ptr = 0;
	for(int i = 0; i < sz(events); ){
		int j = i;
		while(j < sz(events) && events[i].yc == events[j].yc) j++;
		vector<pi> intvs;
		for(int k = i; k < j; k++){
			intvs.emplace_back(events[k].xs, events[k].xe);
		}
		sort(all(intvs));
		while(ptr < sz(points) && points[ptr].yc <= events[i].yc){
			if(points[ptr].act == 1) s.insert(points[ptr].xs);
			else s.erase(points[ptr].xs);
			bit.add(points[ptr].xs, points[ptr].act);
			ptr++;
		}
		int curMax = -2e9;
		int y = events[i].yc;
		for(int i = 0; i + 1< sz(intvs); i++){
			curMax = max(curMax, intvs[i].second);
			if(curMax < intvs[i + 1].first){
				auto lo = s.upper_bound(curMax);
				if(lo != s.end() && *lo < intvs[i + 1].first){
				}
				else if(bit.query(curMax) % 2){
					rect_list.push_back({y, curMax, intvs[i + 1].first});
				}
			}
		}
		i = j;
	}
	bit.clear();
	return rect_list;
}

lint ccw(pi a, pi b, pi c){
	int dx1 = b.first - a.first;
	int dy1 = b.second - a.second;
	int dx2 = c.first - a.first;
	int dy2 = c.second - a.second;
	return 1ll * dx1 * dy2 - 1ll * dy1* dx2;
}

int main(){
	int n;
	scanf("%d",&n);
	vector<pi> a(n);
	vector<int> vx, vy;
	for(int i=0; i<n; i++){
		scanf("%d %d",&a[i].first, &a[i].second);
		vx.push_back(a[i].first);
		vy.push_back(a[i].second);
	}
	for(int i = 0; i < n ;i++){
		assert(ccw(a[i], a[(i+1)%n], a[(i+2)%n]));
	}
	sort(all(vx)); vx.resize(unique(all(vx)) - vx.begin());
	sort(all(vy)); vy.resize(unique(all(vy)) - vy.begin());
	for(auto &[x, y] : a){
		x = lower_bound(all(vx), x) - vx.begin();
		y = lower_bound(all(vy), y) - vy.begin();
	}
	auto seg1 = generate_segments(a);
	for(auto &[x, y] : a) swap(x, y);
	auto seg2 = generate_segments(a);
	int ret = n / 2 - 2;
	vector<pi> upds[MAXN];
	for(int i = 0; i < sz(seg2); i++){
		upds[seg2[i].s].emplace_back(seg2[i].pos, i + sz(seg1));
		upds[seg2[i].e + 1].emplace_back(seg2[i].pos, i + sz(seg1));
	}
	map<int, int> s;
	sort(all(seg1), [&](const segment &a, const segment &b){
		return a.pos < b.pos;
	});
	int ptr = 0;
	disj.init(MAXN);
	for(int i = 0; i < sz(seg1); i++){
		while(ptr <= seg1[i].pos){
			for(auto &[x, y] : upds[ptr]){
				if(s.find(x) == s.end()) s[x] = y;
				else s.erase(x);
			}
			ptr++;
		}
		auto itr = s.find(seg1[i].s);
		if(itr != s.end()){
			disj.uni(itr->second, i);
		}
		itr = s.find(seg1[i].e);
		if(itr != s.end()){
			disj.uni(itr->second, i);
		}
	}
	for(int i = 0; i < sz(seg1) + sz(seg2); i++){
		if(disj.find(i) == i){
			ret -= (1 + disj.sz[i]) / 2;
		}
	}
	cout << ret << endl;
}
