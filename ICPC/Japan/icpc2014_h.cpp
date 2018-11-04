#include <bits/stdc++.h>
using namespace std;
using real_t = long double;
using pi = pair<real_t, real_t>;
const int MAXN = 10;
const real_t eps = 1e-8;
const real_t PI = acos(-1);

int n;
pi s, g, a[MAXN];

real_t my_fmod(real_t x, real_t d){
	return fmod(fmod(x, d) + 2 * d, d);
}

#define fmod my_fmod
real_t ccw(pi a, pi b, pi c){
	real_t dx1 = b.first - a.first;
	real_t dy1 = b.second - a.second;
	real_t dx2 = c.first - a.first;
	real_t dy2 = c.second - a.second;
	return dx1 * dy2 - dy1 * dx2;
}

real_t dot(pi a, pi b, pi c){
	real_t dx1 = b.first - a.first;
	real_t dy1 = b.second - a.second;
	real_t dx2 = c.first - a.first;
	real_t dy2 = c.second - a.second;
	return dx1 * dx2 + dy1 * dy2;
}

real_t dist(pi a, pi b){
	return hypot(a.first - b.first, a.second - b.second);
}

real_t seg_dist(pi a, pi b, pi c){
	if(dot(a, b, c) < 0) return dist(a, c);
	if(dot(b, a, c) < 0) return dist(b, c);
	return fabs(ccw(a, b, c)) / dist(a, b);
}

int VTX = 0;
vector<real_t> v[MAXN];
vector<int> idx[MAXN];

struct edges{
	int x; real_t th1;
	int y; real_t th2;
	real_t dist;
};

vector<edges> seg;

void Add_Edge(int x, real_t th1, int y, real_t th2){
	th1 = fmod(th1, 2 * PI);
	th2 = fmod(th2, 2 * PI);
	// check this point, and see whether it intersects
	pi p1 = a[x];
	if(x < n){
		p1.first += cos(th1);
		p1.second += sin(th1);
	}
	pi p2 = a[y];
	if(y < n){
		p2.first += cos(th2);
		p2.second += sin(th2);
	}
	for(int i=0; i<n; i++){
		if(i != x && i != y){
			if(seg_dist(p1, p2, a[i]) < 1) return;
		}
	}
	v[x].push_back(th1);
	v[y].push_back(th2);
	seg.push_back({x, th1, y, th2, dist(p1, p2)});
}

using node = pair<real_t, int>;
vector<node> gph[505];
priority_queue<node, vector<node>, greater<node> > pq;
real_t Dist[505];
bool vis[505];
int par[505];

real_t get_dist(int s, int e){
	fill(Dist, Dist + 505, 1e18);
	Dist[s] = 0;
	pq.emplace(0, s);
	while(!pq.empty()){
		auto x = pq.top();
		pq.pop();
		if(vis[x.second]) continue;
		vis[x.second] = 1;
		for(auto &i : gph[x.second]){
			if(Dist[i.second] > i.first + x.first){
				par[i.second] = x.second;
				Dist[i.second] = i.first + x.first;
				pq.emplace(Dist[i.second], i.second);
			}
		}
	}
	return Dist[e];
}

bool interval_cross(real_t s, real_t e, real_t rs, real_t re){
	vector<pair<real_t, real_t>> v1, v2;
	if(s > e){
		v1.emplace_back(s, 2 * PI);
		v1.emplace_back(0, e);
	}
	else v1.emplace_back(s, e);
	if(rs > re){
		v2.emplace_back(rs, 2 * PI);
		v2.emplace_back(0, re);
	}
	else v2.emplace_back(rs, re);
	for(auto &i : v1) for(auto &j : v2){
		if(min(j.second, i.second) - max(i.first, j.first) > 1e-7) return true;
	}
	return false;
}

int main(){
	cin >> n >> g.first >> g.second;
	g.first /= 100;
	g.second /= 100;
	for(int i=0; i<n; i++){
		cin >> a[i].first >> a[i].second;
		a[i].first /= 100;
		a[i].second /= 100;
	}
	a[n] = s;
	a[n+1] = g;
	for(int i=0; i<n; i++){
		for(int j=0; j<i; j++){
			real_t ang_to_aj = atan2(a[j].second - a[i].second, a[j].first - a[i].first);
			if(dist(a[i], a[j]) > 2){
				real_t cur = dist(a[i], a[j]);
				real_t rad = acos(2.0 / cur);
				Add_Edge(i, ang_to_aj - rad, j, PI + ang_to_aj - rad);
				Add_Edge(i, ang_to_aj + rad, j, PI + ang_to_aj + rad);
			}
			Add_Edge(i, ang_to_aj - PI / 2, j, PI + ang_to_aj + PI / 2);
			Add_Edge(i, ang_to_aj + PI / 2, j, PI + ang_to_aj - PI / 2);
		}
	}
	for(int i=n; i<n+2; i++){
		for(int j=0; j<n; j++){
			real_t cur = dist(a[i], a[j]);
			real_t rad = acos(1 / cur);
			real_t ang_to_aj = PI + atan2(a[j].second - a[i].second, a[j].first - a[i].first);
			Add_Edge(i, 0, j, ang_to_aj + rad);
			Add_Edge(i, 0, j, ang_to_aj - rad);
		}
	}
	Add_Edge(n, 0, n+1, 0);
	v[n].clear();
	v[n+1].clear();
	v[n].push_back(0);
	v[n+1].push_back(0);
	for(int i=0; i<n+2; i++){
		sort(v[i].begin(), v[i].end());
		v[i].resize(unique(v[i].begin(), v[i].end()) - v[i].begin());
	//	printf("[");
		for(int j=0; j<v[i].size(); j++){
			idx[i].push_back(++VTX);
	//		printf("%d=%.10Lf,", VTX, v[i][j]);
		}
	//	puts("]");
	}
	for(auto &i : seg){
		int ST = -1, ED = -1;
		for(int k=0; k<v[i.x].size(); k++){
			if(fabs(v[i.x][k] - i.th1) < eps){
				ST = idx[i.x][k];
			}
		}
		for(int k=0; k<v[i.y].size(); k++){
			if(fabs(v[i.y][k] - i.th2) < eps){
				ED = idx[i.y][k];
			}
		}
		assert(ST != -1);
		assert(ED != -1);
		gph[ST].emplace_back(i.dist, ED);
		gph[ED].emplace_back(i.dist, ST);
//		printf("%d %d %.10Lf\n",ST, ED, i.dist);
	}
	for(int i=0; i<n; i++){
		for(int j=0; j<v[i].size(); j++){
			bool bad = false;
			for(int k=0; k<n; k++){
				if(i == k) continue;
				real_t cur = dist(a[i], a[k]);
				if(cur > 2) continue;
				real_t rad = acos(cur / 2);
				real_t ang_to_aj = atan2(a[k].second - a[i].second, a[k].first - a[i].first);
				real_t st = fmod(ang_to_aj - rad, 2 * PI);
				real_t ed = fmod(ang_to_aj + rad, 2 * PI);
				if(interval_cross(st, ed, v[i][j], v[i][(j+1)%v[i].size()])){
					bad = true;
				}
			}
			if(!bad){
				real_t rad = fmod(v[i][(j+1)%v[i].size()] - v[i][j], 2 * PI);
				gph[idx[i][j]].emplace_back(rad, idx[i][(j+1)%v[i].size()]);
				gph[idx[i][(j+1)%v[i].size()]].emplace_back(rad, idx[i][j]);
		//		printf("%d %d %.10Lf\n", idx[i][j], idx[i][(j+1)%v[i].size()], rad);
			}
		}
	}
	real_t ans = get_dist(idx[n][0], idx[n+1][0]) * 100;
	if(ans > 1e9) puts("0.0");
	else printf("%.10Lf\n", ans);
}