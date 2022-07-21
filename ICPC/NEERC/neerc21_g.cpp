#include <bits/stdc++.h>
using namespace std;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using lint = long long;
using pi = pair<lint, lint>;
using llf = long double;
 
typedef pair<int,int> pii;
const int INF = 0x3f3f3f3f;
const int MAXN = 100005;
 
llf ccw(pi a, pi b, pi c, int h1, int h2, int h3){
	int dx1 = b.first - a.first;
	int dy1 = b.second - a.second;
	int dx2 = c.first - a.first;
	int dy2 = c.second - a.second;
	vector<lint> x = {dx1, dy1, h2 - h1};
	vector<lint> y = {dx2, dy2, h3 - h1};
	llf X = x[1] * y[2] - y[1] * x[2];
	llf Y = x[2] * y[0] - y[2] * x[0];
	llf Z = x[0] * y[1] - y[0] * x[1];
	return sqrt(X*X+Y*Y+Z*Z);
}
 
struct queries{
	int v, h, idx;
};
 
struct event{
	int t; // event time -> active, after processing all queries > t
	int type; // type == 0 <- polynomial set, 1 <- merge
	int v, w; // if type is 1, merge this two vertices
	llf a, b, c; // if type is 0, add this polynomial to vertex v
	bool operator<(const event &e)const{
		return t > e.t;
	}
};
 
event newEdgeEvent(int u, int v, int h){
	return (event){h - 1, 1, u, v, 0.0, 0.0, 0.0};
}
 
event newPolyEvent(int v, int h, llf a, llf b, llf c){
	return (event){h, 0, v, v, a, b, c};
}
 
struct disj {
	int pa[MAXN];
	llf a[MAXN], b[MAXN], c[MAXN];
	void init(int n){
		iota(pa, pa + n + 1, 0);
	}
	int find(int x){
		return pa[x] = (pa[x] == x ? x : find(pa[x]));
	}
	void add(int u, llf _a, llf _b, llf _c){
		//	cout << "add " << u << " " << _a << " " << _b << " " << _c << endl;
		u = find(u);
		a[u] += _a;
		b[u] += _b;
		c[u] += _c;
	}
	bool uni(int p, int q){
//		cout << "uni " << p << " " << q << endl;
		p = find(p); q = find(q);
		if(p == q) return 0;
		pa[q] = p;
		a[p] += a[q];
		b[p] += b[q];
		c[p] += c[q];
		return 1;
	}
	llf query(int v, int h){
		//	cout << "query " << v << " " << h << endl;
		v = find(v);
		return a[v] * h * h + b[v] * h + c[v];
	}
}disj;
 
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	int n; cin >> n;
	vector<pi> a(n);
	vector<int> h(n);
	for(int i = 0; i < n; i++){
		cin >> a[i].first >> a[i].second >> h[i];
	}
	int m; cin >> m;
	vector<int> p2t(n);
	map<pi, int> mp;
	vector<event> events;
	auto addEdge = [&](int u, int v, int eidx){
		if(mp.count(pi(u, v))){
			int x = mp[pi(u, v)];
			int y = eidx;
			events.push_back(newEdgeEvent(x, y, max(h[u], h[v])));
		}
		else{
			mp[pi(u, v)] = eidx;
		}
	};
	for(int i = 0; i < m; i++){
		int x, y, z; cin >> x >> y >> z;
		if(x > y) swap(x, y);
		if(x > z) swap(x, z);
		if(y > z) swap(y, z);
		x--; y--; z--;
		p2t[x] = p2t[y] = p2t[z] = i;
		addEdge(x, y, i);
		addEdge(y, z, i);
		addEdge(x, z, i);
		{
			llf area = ccw(a[x], a[y], a[z], h[x], h[y], h[z]);
			if(area < 0) area *= -1;
			int mx = max({h[x], h[y], h[z]});
			int mn = min({h[x], h[y], h[z]});
			int middle = h[x] + h[y] + h[z] - mx - mn;
			if(middle < mx){
				llf L = middle;
				llf R = mx;
				llf objective = 0.5 * area * (mx - middle) / (mx - mn);
				llf C =  objective / ((R - L) * (R - L));
				events.push_back(newPolyEvent(i, mx, C, -2 * R * C, C * R * R));
				events.push_back(newPolyEvent(i, middle, -C, +2 * R * C, objective - C * R * R));
			}
			if(mn < middle){
				llf L = mn;
				llf R = middle;
				llf objective = 0.5 * area * (middle - mn) / (mx - mn);
				llf C =  objective / ((R - L) * (R - L));
				events.push_back(newPolyEvent(i, middle, -C, 2 * L * C, -C * L * L + objective));
				events.push_back(newPolyEvent(i, mn, C, -2 * L * C, C * L * L));
			}
			if(mx == mn) events.push_back(newPolyEvent(i, mn, 0, 0, 0.5 * area));
		}
	}
	int q; cin >> q;
	vector<queries> qr(q);
	vector<llf> ans(q, -1);
	for(int i = 0; i < q; i++){
		cin >> qr[i].h >> qr[i].v;
		qr[i].v--;
		qr[i].idx = i;
	}
	sort(all(qr), [&](const queries &a, const queries &b){
		return a.h > b.h;
	});
	sort(all(events));
	int p = 0;
	disj.init(m);
	for(auto &x : qr){
		while(p < sz(events) && events[p].t >= x.h){
			if(events[p].type == 0) {
				disj.add(events[p].v, events[p].a, events[p].b, events[p].c);
			}
			else{
				disj.uni(events[p].v, events[p].w);
			}
			p++;
		}
		if(h[x.v] <= x.h) continue;
		else ans[x.idx] = disj.query(p2t[x.v], x.h);
	}
	for(auto &x : ans){
		if(x < -0.5) cout << "-1\n";
		else cout << fixed << setprecision(69) << x << "\n";
	}
}
