#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;

int n, d, x[105], y[105];

int dis(int p, int q){
	return (x[p] - x[q]) * (x[p] - x[q]) + (y[p] - y[q]) * (y[p] - y[q]);
}

int ccw(int p, int q, int r){
	int dx1 = x[q] - x[p];
	int dy1 = y[q] - y[p];
	int dx2 = x[r] - x[p];
	int dy2 = y[r] - y[p];
	return dx1 * dy2 - dy1 * dx2;
}

const int MAXN = 105;
const int MAXM = 105;

struct bpm{
	vector<int> gph[MAXN];
	int dis[MAXN], l[MAXN], r[MAXN];

	void clear(){
		for(int i=0; i<MAXN; i++){
			gph[i].clear();
		}
	}

	void add_edge(int l, int r){
		gph[l].push_back(r);
	}

	bool bfs(int n){
		queue<int> que;
		bool ok = 0;
		memset(dis, 0, sizeof(dis));
		for(int i=0; i<n; i++){
			if(l[i] == -1 && !dis[i]){
				que.push(i);
				dis[i] = 1;
			}
		}
		while(!que.empty()){
			int x = que.front();
			que.pop();
			for(auto &i : gph[x]){
				if(r[i] == -1) ok = 1;
				else if(!dis[r[i]]){
					dis[r[i]] = dis[x] + 1;
					que.push(r[i]);
				}
			}
		}
		return ok;
	}

	bool dfs(int x){
		for(auto &i : gph[x]){
			if(r[i] == -1 || (dis[r[i]] == dis[x] + 1 && dfs(r[i]))){
				l[x] = i;
				r[i] = x;
				return 1;
			}
		}
		return 0;
	}

	int match(int n){
		memset(l, -1, sizeof(l));
		memset(r, -1, sizeof(r));
		int ret = 0;
		while(bfs(n)){
			for(int i=0; i<n; i++){
				if(dis[i] == 1 && dfs(i)) ret++;
			}
		}
		return ret;
	}

	bool chk[MAXN + MAXM];

	void rdfs(int x, int n){
		if(chk[x]) return;
		chk[x] = 1;
		for(int idx=0; idx<gph[x].size(); idx++){
			int i = gph[x][idx];
			chk[i + n] = 1;
			assert(r[i] != -1);
			rdfs(r[i], n);
		}
	}

	vector<int> getcover(int n, int m){
		match(n);
		memset(chk, 0, sizeof(chk));
		for(int i=0; i<n; i++){
			if(l[i] == -1) rdfs(i, n);
		}
		vector<int> v;
		for(int i=0; i<n; i++){
			if(!chk[i]) v.push_back(i);
		}
		for(int i=n; i<n+m; i++){
			if(chk[i]) v.push_back(i);
		}
		return v;
	}
}bpm;

vector<int> solve(int p, int q){
	vector<int> l, r;
	for(int i=0; i<n; i++){
		if(i == p || i == q) continue;
		if(dis(i, p) <= dis(p, q) && dis(i, q) <= dis(p, q)){
			if(ccw(p, q, i) >= 0) l.push_back(i);
			else r.push_back(i);
		}
	}
	bpm.clear();
	for(int i=0; i<l.size(); i++){
		for(int j=0; j<r.size(); j++){
			if(dis(l[i], r[j]) > dis(p, q)){
				bpm.add_edge(i, j);
			}
		}
	}
	int chk[105] = {};
	vector<int> g = bpm.getcover(l.size(), r.size());
	for(auto &i : g){
		chk[i] = 1;
	}
	vector<int> ret;
	for(int i=0; i<l.size(); i++){
		if(!chk[i]) ret.push_back(l[i]);
	}
	for(int i=0; i<r.size(); i++){
		if(!chk[i+l.size()]) ret.push_back(r[i]);
	}
	ret.push_back(p);
	ret.push_back(q);
	return ret;
}

int main(){
	cin >> n >> d;
	for(int i=0; i<n; i++){
		cin >> x[i] >> y[i];
	}
	vector<int> r;
	for(int i=0; i<n; i++){
		for(int j=0; j<i; j++){
			if(dis(i, j) <= d * d){
				auto w = solve(i, j);
				if(w.size() > r.size()) r = w;
			}
		}
	}
	if(r.empty()) r.push_back(0);
	cout << r.size() << endl;
	for(auto &i : r) printf("%d ", i + 1);
}
