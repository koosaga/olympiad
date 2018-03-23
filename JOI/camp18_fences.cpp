#include <bits/stdc++.h>
using namespace std;
const int MAXN = 222;
typedef pair<double, double> pi;

double ccw(pi a, pi b, pi c){
	double dx1 = b.first - a.first;
	double dy1 = b.second - a.second;
	double dx2 = c.first - a.first;
	double dy2 = c.second - a.second;
	return dx1 * dy2 - dy1 * dx2;
}

double dot(pi a, pi b, pi c){
	double dx1 = b.first - a.first;
	double dy1 = b.second - a.second;
	double dx2 = c.first - a.first;
	double dy2 = c.second - a.second;
	return dx1 * dx2 + dy1 * dy2;
}

double pdist(pi a, pi b){
	return hypot(a.first - b.first, a.second - b.second);
}

const double eps = 1e-7;
bool line_segment_intersection(pi a, pi b, pi c, pi d){
	double k1 = ccw(a, b, c);
	double k2 = ccw(a, b, d);
	if(k1 > eps && k2 > eps) return false;
	if(k1 < -eps && k2 < -eps) return false;
	k1 = ccw(c, d, a);
	k2 = ccw(c, d, b);
	if(k1 > eps && k2 > eps) return false;
	if(k1 < -eps && k2 < -eps) return false;
	return true;
}

int n, c;
pi a[MAXN];

struct node{
	int pos, arg;
	double dist;
	bool operator<(const node &n)const{
		return dist > n.dist;
	}
};

struct seg{
	double first;
	int second, basecross;
};

vector<seg> gph[MAXN];
double dist[2][MAXN];
bool vis[2][MAXN];

double solve(int p){
	priority_queue<node> pq;
	for(int i=0; i<2; i++){
		for(int j=0; j<2*n+8; j++){
			dist[i][j] = 1e9;
			vis[i][j] = 0;
		}
	}
	dist[0][p] = 0;
	while(true){
		int sx = -1, sy = -1;
		double cur = 1e9;
		for(int i=0; i<2; i++){
			for(int j=0; j<2*n+8; j++){
				if(!vis[i][j] && dist[i][j] < cur){
					cur = dist[i][j];
					sx = i;
					sy = j;
				}
			}
		}
		if(sx == -1 || sy == -1) break;
		vis[sx][sy] = 1;
		for(auto &i : gph[sy]){
			if(dist[sx ^ i.basecross][i.second] > i.first + cur){
				dist[sx ^ i.basecross][i.second] = i.first + cur;
			}
		}
	}
	return dist[1][p];
}

bool is_cross(pi a, pi b){
	return line_segment_intersection(a, b, pi(0, 0), pi(233, 569));
}

void makeGraph(){
	auto add_edge = [&](int s, int e, double x, bool augment = false){
	//	printf("%d %d %.10f\n",s ,e , x);
		gph[s].push_back({x, e, is_cross(a[s], a[e]) ^ augment});
		gph[e].push_back({x, s, is_cross(a[s], a[e]) ^ augment});
	};
	for(int i=0; i<n+4; i++){
		add_edge(2*i, 2*i+1, 0);
	}
	add_edge(2*n, 2*n+2, 2*c);
	add_edge(2*n, 2*n+4, 2*c);
	add_edge(2*n+2, 2*n+6, 2*c);
	add_edge(2*n+4, 2*n+6, 2*c);
	for(int i=0; i<2*n+8; i++){
		for(int j=0; j<2*n; j++){
			if(j % 2 == 1) continue;
			if(i / 2 == j / 2) continue;
			pi p1 = a[i];
			pi p2 = pi(-1, -1);
			if(dot(a[j], a[j+1], p1) < 0 || dot(a[j+1], a[j], p1) < 0){
				if(pdist(a[j], p1) < pdist(a[j+1], p1)) p2 = a[j];
				else p2 = a[j+1];
			}
			else{
				double arg = ccw(a[j], a[j+1], p1) / pdist(a[j], a[j+1]);
				double dx = (a[j+1].first - a[j].first) / pdist(a[j], a[j+1]);
				double dy = (a[j+1].second - a[j].second) / pdist(a[j], a[j+1]);
				p2 = p1;
				p2.first += dy * arg;
				p2.second -= dx * arg;
			}
			if(i == 2 * n || i == 2 * n + 1){
				if(p2.first <= -c || p2.second <= -c) {
					add_edge(i, j, pdist(p1, p2), is_cross(a[i], a[j]) ^ is_cross(p1, p2) ^ is_cross(p2, a[j]));
				}
				else continue;
			}
			if(i == 2 * n + 2 || i == 2 * n + 3){
				if(p2.first <= -c || p2.second >= c){
					add_edge(i, j, pdist(p1, p2), is_cross(a[i], a[j]) ^ is_cross(p1, p2) ^ is_cross(p2, a[j]));
				}
				else continue;
			}
			if(i == 2 * n + 4 || i == 2 * n + 5){
				if(p2.first >= c || p2.second <= -c){
					add_edge(i, j, pdist(p1, p2), is_cross(a[i], a[j]) ^ is_cross(p1, p2) ^ is_cross(p2, a[j]));
				}
				else continue;
			}
			if(i == 2 * n + 6 || i == 2 * n + 7){
				if(p2.first >= c || p2.second >= c){
					add_edge(i, j, pdist(p1, p2), is_cross(a[i], a[j]) ^ is_cross(p1, p2) ^ is_cross(p2, a[j]));
				}
				else continue;
			}
			double lx = -c, rx = c;
			if(line_segment_intersection(p1, p2, pi(lx, rx), pi(lx, lx))) continue;
			if(line_segment_intersection(p1, p2, pi(lx, rx), pi(rx, rx))) continue;
			if(line_segment_intersection(p1, p2, pi(rx, rx), pi(rx, lx))) continue;
			if(line_segment_intersection(p1, p2, pi(rx, lx), pi(lx, lx))) continue;
			add_edge(i, j, pdist(p1, p2), is_cross(a[i], a[j]) ^ is_cross(p1, p2) ^ is_cross(p2, a[j]));
		}
	}
}

int main(){
	cin >> n >> c;
	for(int i=0; i<2*n; i++){
		cin >> a[i].first >> a[i].second;
	}
	a[2*n+0] = a[2*n+1] = pi(-c, -c);
	a[2*n+2] = a[2*n+3] = pi(-c, c);
	a[2*n+4] = a[2*n+5] = pi(c, -c);
	a[2*n+6] = a[2*n+7] = pi(c, c);
	makeGraph();
	double ans = 1e9;
	for(int i=0; i<2*n+8; i++) ans = min(ans, solve(i));
	printf("%.10f\n", ans);
}
