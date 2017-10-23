#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, double> pi;
const int MAXN = 205;

struct edg{
	int pos;
	double cap;
	int rev;
};

vector<edg> gph[MAXN];
void clear(){for(int i=0; i<MAXN; i++) gph[i].clear();}
void add_edge(int s, int e, double x){
	gph[s].push_back({e, x, (int)gph[e].size()});
	gph[e].push_back({s, 0, (int)gph[s].size()-1});
}
int dis[MAXN], pnt[MAXN];
bool bfs(int src, int sink){
	memset(dis, 0, sizeof(dis));
	memset(pnt, 0, sizeof(pnt));
	queue<int> que;
	que.push(src);
	dis[src] = 1;
	while(!que.empty()){
		int x = que.front();
		que.pop();
		for(auto &e : gph[x]){
			if(e.cap > 0 && !dis[e.pos]){
				dis[e.pos] = dis[x] + 1;
				que.push(e.pos);
			}
		}
	}
	return dis[sink] > 0;
}

double dfs(int x, int sink, double f){
	if(x == sink) return f;
	for(; pnt[x] < gph[x].size(); pnt[x]++){
		edg e = gph[x][pnt[x]];
		if(e.cap > 0 && dis[e.pos] == dis[x] + 1){
			double w = dfs(e.pos, sink, min(f, e.cap));
			if(w > 0){
				gph[x][pnt[x]].cap -= w;
				gph[e.pos][e.rev].cap += w;
				return w;
			}
		}
	}
	return 0;
}

double match(int src, int sink){
	double ret = 0;
	while(bfs(src, sink)){
		double r;
		while((r = dfs(src, sink, 2e9))) ret += r;
	}
	return ret;
}

int n, m, s[20005], e[20005], x[20005];
int idx[205][205];
double v, a;

void cg(){
	clear();
	for(int i=0; i<m; i++){
		add_edge(s[i], e[i], x[i]);
		add_edge(e[i], s[i], x[i]);
	}
}

vector<pi> retrieve_fucking_residual(){
	vector<pi> v;
	for(int i=0; i<m; i++){
		double ans = 0;
		bool f = 0;
		for(auto &j : gph[s[i]]){
			if(e[i] == j.pos){
				if(!f) ans += x[i] - j.cap;
				else ans -= j.cap;
				f = 1;
			}
		}
		v.push_back(pi(i, ans));
	}
	return v;
}

double fuck[20005];

int main(){
	cin >> n >> m >> v >> a;
	for(int i=0; i<m; i++){
		cin >> s[i] >> e[i] >> x[i];
		idx[s[i]][e[i]] = idx[e[i]][s[i]] = i;
	}
	cg();
	double arg1e = match(1, 3);
	double arg2s = match(2, 3);
	cg();
	double arg2e = match(2, 3);
	double arg1s = match(1, 3);
	auto trial = [&](double arg){
		double f = arg1s * arg + arg1e * (1 - arg);
		double w = arg2e * arg + arg2s * (1 - arg);
		return pow(f / v, a) * pow(w, 1 - a);
	};
	double st = 0, ed = 1;
	for(int i=0; i<100; i++){
		double m1 = (st * 2 + ed) / 3;
		double m2 = (st + 2 * ed) / 3;
		if(trial(m1) < trial(m2)) st = m1;
		else ed = m2;
	}
	double ans = trial(st);
	cg();
	double f = arg1s * st + arg1e * (1 - st);
	double w = arg2e * st + arg2s * (1 - st);
	add_edge(0, 1, f);
	add_edge(0, 2, w);
	match(0, 3);
	auto l = retrieve_fucking_residual();
	clear();
	for(auto &i : l){
		fuck[i.first] = i.second;
		if(i.second < 0){
			add_edge(e[i.first], s[i.first], -i.second);
		}
		else{
			add_edge(s[i.first], e[i.first], i.second);
		}
	}
	add_edge(0, 1, f);
	match(0, 3);
	for(int i=0; i<m; i++){
		double a1, a2;
		if(fuck[i] < 0){
			for(auto &j : gph[s[i]]){
				if(j.pos == e[i]){
					a1 = j.cap;
					a2 = abs(fuck[i]) - j.cap;
					a1 *= -1;
					a2 *= -1;
				}
			}
		}
		else{
			for(auto &j : gph[e[i]]){
				if(j.pos == s[i]){
					a1 = j.cap;
					a2 = fuck[i] - j.cap;
				}
			}
		}
		printf("%.10f %.10f\n", a1 / v, a2);
	}
	printf("%.10f\n", ans);
}

