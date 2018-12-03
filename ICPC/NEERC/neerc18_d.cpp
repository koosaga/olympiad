#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<lint, lint>;
const int MAXN = 100005;
const int MAXG = 200;

struct disj{
	int pa[MAXN];
	void init(int n){
		iota(pa, pa + n + 1, 0);
	}
	int find(int x){
		return pa[x] = (pa[x]== x ? x : find(pa[x]));
	}
	bool uni(int p, int q){
		p = find(p);
		q = find(q);
		if(p == q) return 0;
		pa[q] = p; return 1;
	}
}disj;

int n, m, dep[MAXN], par[MAXN], din[MAXN], dout[MAXN], piv;
vector<int> gph[MAXN], tr[MAXN];
int dist[MAXG][MAXN], chk[MAXN];

void dfs(int x, int p){
	din[x] = ++piv;
	for(auto &i : tr[x]){
		if(i != p){
			dep[i] = dep[x] + 1;
			par[i] = x;
			dfs(i, x);
		}
	}
	dout[x] = piv;
}

void bfs(int idx, int src){
	dist[idx][src] = 0;
	queue<int> que;
	que.push(src);
	while(!que.empty()){
		int x = que.front();
		que.pop();
		for(auto &i : gph[x]){
			if(dist[idx][i] > dist[idx][x] + 1){
				dist[idx][i] = dist[idx][x] + 1;
				que.push(i);
			}
		}
	}
}

int lca(int x, int y){
	while(dep[x] < dep[y]) y = par[y];
	while(dep[x] > dep[y]) x = par[x];
	while(x != y) x = par[x], y = par[y];
	return x;
}

int sz[MAXN];

pi explore(int x, int p, int d){
	pi ret(1, d);
	sz[x] = 1;
	for(auto &i : tr[x]){
		if(i == p || chk[i]) continue;
		lint p, q; tie(p, q) = explore(i, x, d + 1);
		ret.first += p;
		ret.second += q;
		sz[x] += sz[i];
	}
	return ret;
}

lint inner_tree(int x, int p, int d){
	lint ret = 0;
	for(auto &i : tr[x]){
		if(i == p || chk[i]) continue;
		ret += inner_tree(i, x, d);
		ret += 1ll * (d - sz[i]) * sz[i];
	}
	return ret;
}

int lbl[MAXN];

lint SUM(int x){ return 1ll * x * (x + 1) / 2; }

vector<lint> vtxPrecalc[MAXG];
vector<lint> sumPrecalc[MAXG];
vector<lint> HAP_vtxPrecalc[MAXG];
vector<lint> IHAP_vtxPrecalc[MAXG];
vector<lint> HAP_sumPrecalc[MAXG];

int main(){
	scanf("%d %d",&n,&m);
	disj.init(n);
	vector<pi> droga; // back edge
	vector<pi> tree_droga; // tree edge
	vector<int> punkty;
	for(int i=0; i<m; i++){
		int s, e; scanf("%d %d",&s,&e);
		if(disj.uni(s, e)){
			tr[s].push_back(e);
			tr[e].push_back(s);
		}
		else{
			droga.emplace_back(s, e);
			punkty.push_back(s);
			punkty.push_back(e);
		}
		gph[s].push_back(e);
		gph[e].push_back(s);
	}
	if(m == n - 1){
		explore(1, 0, 0);
		cout << inner_tree(1, 0, n) << endl;
		return 0;
	}
	dfs(1, 0);
	{
		auto in = [&](int x, int y){ return din[x] <= din[y] && dout[y] <= dout[x]; };
		sort(punkty.begin(), punkty.end(), [&](const int &a, const int &b){
			return din[a] < din[b];
		});	
		int m = punkty.size();
		for(int i=1; i<m; i++) punkty.push_back(lca(punkty[i-1], punkty[i]));
		sort(punkty.begin(), punkty.end(), [&](const int &a, const int &b){
			return din[a] < din[b];
		});
		punkty.resize(unique(punkty.begin(), punkty.end()) - punkty.begin());
		vector<int> stk;
		for(auto &i : punkty){
			while(!stk.empty() && !in(stk.back(), i)){
				stk.pop_back();
			}
			if(!stk.empty()) tree_droga.emplace_back(stk.back(), i);
			stk.push_back(i);
		}
		for(auto &i : tree_droga){
			int l = lca(i.first, i.second);
			for(int j=i.first; j!=l; j=par[j]) chk[j] = 1;
			for(int j=i.second; j!=l; j=par[j]) chk[j] = 1;
			chk[l] = 1;
		}
		memset(lbl, -1, sizeof(lbl));
		for(int i=0; i<punkty.size(); i++) lbl[punkty[i]] = i;
	}
	memset(dist, 0x3f, sizeof(dist));
	lint ret = 0;
	vector<lint> accm_numVtx;
	vector<lint> accm_depSum;
	for(int i=0; i<punkty.size(); i++){
		bfs(i, punkty[i]);
		lint sum = accumulate(dist[i] + 1, dist[i] + n + 1, 0ll);
		// tree - tree (incl, punkty, do it unordered)
		lint num_of_vtx = 0;
		lint depth_sum = 0;
		tie(num_of_vtx, depth_sum) = explore(punkty[i], -1, 0);
		ret += 2 * inner_tree(punkty[i], -1, sz[punkty[i]]);
		sum -= depth_sum;
		// tree - out tree
		ret += sum * num_of_vtx + (n - num_of_vtx) * depth_sum;
		accm_numVtx.push_back(num_of_vtx);
		accm_depSum.push_back(depth_sum);
	}
	for(int i=0; i<tree_droga.size(); i++){
		int pos1 = tree_droga[i].first;
		int pos2 = tree_droga[i].second;
		int leni = dep[pos2] - dep[pos1];
		vtxPrecalc[i].resize(leni);
		sumPrecalc[i].resize(leni);
		HAP_vtxPrecalc[i].resize(leni);
		IHAP_vtxPrecalc[i].resize(leni);
		HAP_sumPrecalc[i].resize(leni);
		int curpos = pos2;
		for(int k=leni - 1; k>=1; k--){
			curpos = par[curpos];
			tie(vtxPrecalc[i][k], sumPrecalc[i][k]) = explore(curpos, -1, 0);
		}
		for(int k=1; k<leni; k++){
			HAP_vtxPrecalc[i][k] = HAP_vtxPrecalc[i][k-1] + vtxPrecalc[i][k];
			IHAP_vtxPrecalc[i][k] = IHAP_vtxPrecalc[i][k-1] + k* vtxPrecalc[i][k];
			HAP_sumPrecalc[i][k] = HAP_sumPrecalc[i][k-1] + sumPrecalc[i][k];
		}
	}
	for(int i=0; i<tree_droga.size(); i++){
		int pos1 = tree_droga[i].first;
		int pos2 = tree_droga[i].second;
		int leni = dep[pos2] - dep[pos1];
		int curpos = pos2;
		for(int k=leni-1; k>=1; k--){
			curpos = par[curpos];
			lint sum = 0;
			int ITR = 0;
			for(auto &j : punkty){
				int dis = dist[lbl[j]][curpos];
				sum += dis * accm_numVtx[ITR] + accm_depSum[ITR];
				ITR++;
			}
			for(int j=0; j<tree_droga.size(); j++){
				if(i == j) continue;
				int pos3 = tree_droga[j].first;
				int pos4 = tree_droga[j].second;
				int lenj = dep[pos4] - dep[pos3];
				int p1 = dist[lbl[pos3]][curpos];
				int p2 = dist[lbl[pos4]][curpos];
				{
					int X = p1; int Y = p2; int D = lenj;
					int left_is_less = (X + Y + D) / 2 - X;
					left_is_less = min(left_is_less, D - 1);
					left_is_less = max(left_is_less, 0);
					sum += HAP_sumPrecalc[j][lenj - 1];
					sum += X * HAP_vtxPrecalc[j][left_is_less];
					sum += IHAP_vtxPrecalc[j][left_is_less];
					sum += (Y + D) * (HAP_vtxPrecalc[j][lenj - 1] - HAP_vtxPrecalc[j][left_is_less]);
					sum -= IHAP_vtxPrecalc[j][lenj - 1] - IHAP_vtxPrecalc[j][left_is_less];
				}
			}
			sum += HAP_sumPrecalc[i][leni - 1] - sumPrecalc[i][k];
			int D = dist[lbl[pos1]][pos2] + leni;
			{
				int dem = max(1, k - D / 2);
				sum += (D - k) * (HAP_vtxPrecalc[i][dem - 1]);
				sum += IHAP_vtxPrecalc[i][dem - 1];
				sum += k * (HAP_vtxPrecalc[i][k-1] - HAP_vtxPrecalc[i][dem - 1]);
				sum -= IHAP_vtxPrecalc[i][k-1] - IHAP_vtxPrecalc[i][dem - 1];
			}
			{
				int dem = min(leni - 1, k + D / 2);
				sum += IHAP_vtxPrecalc[i][dem] - IHAP_vtxPrecalc[i][k];
				sum -= k * (HAP_vtxPrecalc[i][dem] - HAP_vtxPrecalc[i][k]);
				sum += (D + k) * (HAP_vtxPrecalc[i][leni-1] - HAP_vtxPrecalc[i][dem]);
				sum -= IHAP_vtxPrecalc[i][leni-1] - IHAP_vtxPrecalc[i][dem];
			}
			lint num_of_vtx = vtxPrecalc[i][k];
			lint depth_sum = sumPrecalc[i][k];
			ret += 2 * inner_tree(curpos, -1, sz[curpos]);
			// tree - out tree
			ret += sum * num_of_vtx + (n - num_of_vtx) * depth_sum;
		}
	}
	cout << ret / 2 << endl;
}