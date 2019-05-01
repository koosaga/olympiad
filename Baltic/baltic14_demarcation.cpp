#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXN = 100005;
const int oo = 1.05e9;

int n;
vector<pi> a;

lint ccw(pi a, pi b, pi c){
	int dx1 = b.first - a.first;
	int dy1 = b.second - a.second;
	int dx2 = c.first - a.first;
	int dy2 = c.second - a.second;
	return 1ll * dx1 * dy2 - 1ll * dy1 * dx2;
}

void normalize(vector<pi> &v){
	int minx = oo, miny = oo;
	for(auto &i : v){
		minx = min(minx, i.first);
		miny = min(miny, i.second);
	}
	for(auto &i : v){
		i.first -= minx;
		i.second -= miny;
	}
	rotate(v.begin(), min_element(v.begin(), v.end()), v.end());
}

void reflect(vector<pi> &v){
	for(auto &i : v){
		i.first = -i.first;
	}
	normalize(v);
}

void turn(vector<pi> &v){
	for(auto &i : v){
		i = pi(-i.second, i.first);
	}
	normalize(v);
}

lint get_area(vector<pi> &v){
	lint ret = 0;
	for(int i=2; i<v.size(); i++){
		ret += ccw(v[0], v[i-1], v[i]);
	}
	return ret;
}

bool hapdong(vector<pi> v1, vector<pi> v2){
	normalize(v1);
	normalize(v2);
	for(int i=0; i<4; i++){
		turn(v2);
		if(v1 == v2) return 1;
	}
	reflect(v2);
	for(int i=0; i<4; i++){
		turn(v2);
		if(v1 == v2) return 1;
	}
	reverse(v2.begin(), v2.end());
	normalize(v2);
	for(int i=0; i<4; i++){
		turn(v2);
		if(v1 == v2) return 1;
	}
	reflect(v2);
	for(int i=0; i<4; i++){
		turn(v2);
		if(v1 == v2) return 1;
	}
	return 0;
}

bool mid(int s, int x, int e){
	return 1ll * (e-x) * (x-s) >= 0;
}

bool smid(int s, int x, int e){
	return 1ll * (e-x) * (x-s) > 0;
}

void cut_polygon(vector<pi> in, vector<pi> &out1, vector<pi> &out2, int sx, int ex, int y){
	if(get_area(in) < 0) reverse(in.begin(), in.end());
	int p = min_element(in.begin(), in.end(), [&](const pi &a, const pi &b){
			return a.second < b.second;
			}) - in.begin();
	if(in[p].second >= y){
		out2 = in;
		return;
	}
	int cpos = 0;
	for(int i=0; i<in.size(); i++){
		pi p1 = in[p%in.size()];
		pi p2 = in[(p+1)%in.size()];
		p++;
		if(p1.second != p2.second && smid(p1.second, y, p2.second) && mid(sx, p1.first, ex)){
			if(cpos == 0) out1.push_back(p1);
			else out2.push_back(p1);
			out1.push_back(pi(p1.first, y));
			out2.push_back(pi(p1.first, y));
			cpos ^= 1;
		}
		else if(p1.second == y && p2.second == y && (mid(sx, p1.first, ex) || mid(sx, p2.first, ex))){
			if(sx != -oo && ex != oo && smid(sx, p1.first, ex) && smid(sx, p2.first, ex)){
				out1 = in;
				out2.clear();
				return;
			}
			if(cpos == 0) out1.push_back(p1);
			else out2.push_back(p1);
			cpos ^= 1;
		}
		else{
			if(cpos == 0) out1.push_back(p1);
			else out2.push_back(p1);
		}
	}
}

int rsx = -1, rsy = -1, rex = -1, rey = -1;

void save_results(int sx, int ex, int y){
	for(int i=0; i<n; i++){
		pi p1 = a[i];
		pi p2 = a[(i+1)%n];
		if(p1.second != y || p2.second != y) continue;
		if(p1.first > p2.first) swap(p1, p2);
		if(sx < p1.first && p2.first < ex) return;
		if(p1.first <= sx && sx <= p2.first) sx = p2.first;
		if(p1.first <= ex && ex <= p2.first) ex = p1.first;
	}
	assert(sx < ex);
	rsx = sx;
	rex = ex;
	rsy = y;
	rey = y;
}

struct rect{
	int sx, ex, sy, ey;
};

struct event1{
	int x, y, idx, mode;
	bool operator<(const event1 &sg)const{
		return pi(x, y) < pi(sg.x, sg.y);
	}
};

struct event2{
	int pos, s, e;
	bool operator<(const event2 &b)const{
		return pi(s, e) < pi(b.s, b.e);
	}
};

struct event3{
	int yc, xs, xe, act;
	bool operator<(const event3 &b)const{
		return pi(yc, -act) < pi(b.yc, -b.act);
	}
};

struct disj{
	int pa[MAXN];
	void init(){
		iota(pa, pa + MAXN, 0);
	}
	int find(int x){
		return pa[x] = (pa[x] == x ? x : find(pa[x]));
	}
	bool uni(int p, int q){
		p = find(p);
		q = find(q);
		if(p == q) return 0;
		pa[q] = p; return 1;
	}
}disj;

lint area[MAXN];
lint sum[MAXN], msz[MAXN];
vector<int> gph[MAXN];

void build_tree(vector<rect> v){
	vector<event1> xl, yl;
	for(int i=0; i<v.size(); i++){
		xl.push_back({v[i].sx, v[i].sy, i, +1});
		xl.push_back({v[i].sx, v[i].ey, i, -1});
		xl.push_back({v[i].ex, v[i].sy, i, +1});
		xl.push_back({v[i].ex, v[i].ey, i, -1});

		yl.push_back({v[i].sy, v[i].sx, i, +1});
		yl.push_back({v[i].sy, v[i].ex, i, -1});
		yl.push_back({v[i].ey, v[i].sx, i, +1});
		yl.push_back({v[i].ey, v[i].ex, i, -1});
	}
	disj.init();
	auto proc = [&](vector<event1> v){
		sort(v.begin(), v.end());
		set<int> s;
		for(int i=0; i<v.size(); ){
			int e = i;
			while(e < v.size() && pi(v[i].x, v[i].y) == pi(v[e].x, v[e].y)) e++;
			for(int j=i; j<e; j++){
				if(v[j].mode == +1) s.insert(v[j].idx);
				else s.erase(v[j].idx);
			}
			if(s.size() > 1){
				assert(s.size() == 2);
				if(disj.uni(*s.rbegin(), *s.begin())){
					int x = *s.rbegin();
					int y = *s.begin();
					gph[x].push_back(y);
					gph[y].push_back(x);
				}
			}
			i = e;
		}
	};
	proc(xl); proc(yl);
}

void dfs(int x, int p){
	sum[x] = area[x];
	msz[x] = 0;
	for(auto &i : gph[x]){
		if(i != p){
			dfs(i, x);
			sum[x] += sum[i];
			msz[x] = max(msz[x], sum[i]);
		}
	}
}

void solve(){
	vector<event3> event;
	set<event2> s;
	vector<rect> rect_list;
	for(int i=0; i<n; i++){
		pi p1 = a[i];
		pi p2 = a[(i+1)%n];
		if(p1.first == p2.first) continue;
		if(p1.first < p2.first){
			event.push_back({p1.second, p1.first, p2.first, +1});
		}
		else{
			event.push_back({p1.second, p2.first, p1.first, -1});
		}
	}
	sort(event.begin(), event.end());
	auto rect_close = [&](event2 b, int pos){
		if(b.pos < pos){
			rect_list.push_back({b.s, b.e, b.pos, pos});
		}
	};
	for(auto &i : event){
		if(i.act == 1){
			auto lbnd = s.lower_bound({-1, i.xs, i.xe});
			int curs = i.xs, cure = i.xe;
			if(lbnd != s.begin() && prev(lbnd)->e == i.xs){
				curs = prev(lbnd)->s;
				rect_close(*prev(lbnd), i.yc);
				s.erase(prev(lbnd));
			}
			if(lbnd != s.end() && lbnd->s == i.xe){
				cure = lbnd->e;
				rect_close(*lbnd, i.yc);
				s.erase(lbnd);
			}
			s.insert({i.yc, curs, cure});
		}
		else{
			auto lbnd = --s.lower_bound({-1, i.xe + 1, -1});
			rect_close(*lbnd, i.yc);
			event2 nxt1 = {i.yc, lbnd->s, i.xs};
			event2 nxt2 = {i.yc, i.xe, lbnd->e};
			s.erase(lbnd);
			if(nxt1.s < nxt1.e) s.insert(nxt1);
			if(nxt2.s < nxt2.e) s.insert(nxt2);
		}
	}
	for(int i=0; i<rect_list.size(); i++){
		gph[i].clear();
		area[i] = 1ll * (rect_list[i].ex - rect_list[i].sx) * (rect_list[i].ey - rect_list[i].sy);
	}
	build_tree(rect_list);
	dfs(0, -1);
	if(sum[0] % 2) return;
	lint H = sum[0] / 2;
	for(int i=0; i<rect_list.size(); i++){
		lint mxvi = max(msz[i], sum[0] - sum[i]);
		if(mxvi <= H){
			lint thres = H;
			for(auto &j : gph[i]){
				if(rect_list[j].sy < rect_list[i].sy){
					dfs(j, i);
					thres -= sum[j];
				}
			}
			if(thres >= 0 && thres % (rect_list[i].ex - rect_list[i].sx) == 0){
				lint mok = thres / (rect_list[i].ex - rect_list[i].sx);
				mok += rect_list[i].sy;
				if(mok <= rect_list[i].ey){
					vector<pi> v1, v2;
					cut_polygon(a, v1, v2, rect_list[i].sx, rect_list[i].ex, mok);
					if(hapdong(v1, v2)){
						save_results(rect_list[i].sx, rect_list[i].ex, mok);
					}
				}
			}
			for(auto &j : gph[i]){
				dfs(j, i);
				if(sum[j] == H){
					int sx = max(rect_list[i].sx, rect_list[j].sx);
					int ex = min(rect_list[i].ex, rect_list[j].ex);
					int sy = max(rect_list[i].sy, rect_list[j].sy);
					int ey = min(rect_list[i].ey, rect_list[j].ey);
					assert(sy == ey && sx < ex);
					vector<pi> v1, v2;
					cut_polygon(a, v1, v2, sx, ex, sy);
					if(hapdong(v1, v2)){
						save_results(sx, ex, sy);
					}
				}
			}
			break;
		}
	}
}

int main(){
	scanf("%d",&n);
	a.resize(n);
	for(int i=0; i<n; i++){
		scanf("%d %d",&a[i].first, &a[i].second);
	}
	for(int i=0; i<2; i++){
		auto area = get_area(a);
		if(area < 0) reverse(a.begin(), a.end());
		solve();
		if(i == 1) swap(rsx, rsy), swap(rex, rey);
		if(rsx != -1){
			printf("%d %d %d %d",rsx, rsy, rex, rey);
			return 0;
		}
		for(int i=0; i<n; i++){
			swap(a[i].first, a[i].second);
		}
	}
	puts("NO");
}
