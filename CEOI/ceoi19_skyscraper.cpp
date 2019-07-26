#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
using namespace std;
const int MAXN = 150005;
using lint = long long;
using pi = pair<int, int>;
const int dx[8] = {1, 0, -1, 0, -1, -1, 1, 1};
const int dy[8] = {0, 1, 0, -1, -1, 1, -1, 1};
 
struct AGISEOKHWAN{
	int pa[MAXN];
	void init(int n){
		iota(pa, pa + n + 1, 0);
	}
	int find(int x){
		return pa[x] = (pa[x] == x ? x : find(pa[x]));
	}
	bool uni(int p, int q){
		p = find(p); q = find(q);
		if(p == q) return 0;
		pa[q] = p; return 1;
	}
}AGISEOKHWAN;
 
struct point{
	int x, y, idx;
	bool operator<(const point &p)const{
		return pi(x, y) < pi(p.x, p.y);
	}
}a[MAXN];
 
struct node{
	int x, y, fs;
};
 
vector<node> disj[MAXN * 4];
 
int n;
bool vis[MAXN];
 
pi dual_edge[MAXN][4];
int prec[MAXN][8];
int faces;
int outer_area;
int V[MAXN], E[MAXN], F[MAXN];
  
int getV(int x){
	int msk = 0;
	for(int j=0; j<8; j++){
		int pos = prec[x][j];
		if(pos != -1 && !vis[pos]){
			if(dx[j] <= 0 && dy[j] <= 0) msk |= 1;
			if(dx[j] <= 0 && dy[j] >= 0) msk |= 2;
			if(dx[j] >= 0 && dy[j] >= 0) msk |= 4;
			if(dx[j] >= 0 && dy[j] <= 0) msk |= 8;
		}
	}
	msk ^= 15;
	int remVtx = 0;
	for(int i=0; i<4; i++){
		if((msk >> i) & 1) remVtx++;
	}
	return remVtx;
}
 
int getE(int x){
	int remEdg = 4;
	for(int i=0; i<4; i++){
		int pos = prec[x][i];
		if(pos != -1 && !vis[pos]){
			remEdg--;
		}
	}
	return remEdg;
}

int rev[MAXN];
set<int> s[MAXN];
priority_queue<pi> pq;
bool chk[MAXN];

void enq(int x){
	if(chk[x] && !vis[x]){
		pq.emplace(V[x] - E[x] + F[x], a[x].idx);
	}
}

int getF(int x){
	s[x].clear();
	for(int i=0; i<4; i++){
		int pos = prec[x][i];
		if(pos != -1 && !vis[pos]){
			continue;
		}
		else{
			s[x].insert(dual_edge[x][i].first);
			s[x].insert(dual_edge[x][i].second);
		}
	}
	if(s[x].find(outer_area) != s[x].end()) chk[x] = 1;
	return max(sz(s[x]) - 1, 0);
}
 
void uni(int x, int y){
	if(x == y) return;
	if(disj[x].size() < disj[y].size()) swap(x, y);
	if(outer_area == y){
		outer_area = x;
		for(auto &i : disj[x]){
			F[i.x] = getF(i.x);
			enq(i.x);
		}
	}
	for(auto &i : disj[y]){
		disj[x].push_back(i);
		if(i.fs == 0){
			dual_edge[i.x][i.y].first = x;
		}
		else{
			dual_edge[i.x][i.y].second = x;
		}
	}
	for(auto &i : disj[y]){
		F[i.x] = getF(i.x);
		enq(i.x);
	}
	disj[y].clear();
}
 
void relax(int x){
	for(int i=0; i<4; i++){
		int pos = prec[x][i];
		if(pos != -1 && !vis[pos]){
			continue;
		}
		else{
			uni(dual_edge[x][i].first, dual_edge[x][i].second);
		}
	}
	for(int j=0; j<8; j++){
		int pos = prec[x][j];
		if(pos != -1 && !vis[pos]){
			V[pos] = getV(pos);
			E[pos] = getE(pos);
			F[pos] = getF(pos);
			enq(pos);
		}
	}
}
 
void solve(){
	vector<int> seq;
	for(int i=0; i<n; i++){
		V[i] = getV(i);
		E[i] = getE(i);
		F[i] = getF(i);
	}
	for(int i=0; i<n; i++) enq(i);
	for(int i=0; i<n-1; i++){
		pi ret(-1e9, -1e9);
		while(!pq.empty()){
			auto x = pq.top(); pq.pop();
			int y = rev[x.second];
			if(vis[y] || V[y] - E[y] + F[y] != 0 || V[y] - E[y] + F[y] != x.first) continue;
			ret = pi(x.second, y);
			break;
		}
		assert(ret.first > 0);
		vis[ret.second] = 1;
		seq.push_back(ret.first);
		relax(ret.second);
	}
	for(int i=0; i<n; i++){
		if(!vis[i]) seq.push_back(a[i].idx);
	}
	puts("YES");
	reverse(seq.begin(), seq.end());
	for(auto &i : seq) printf("%d\n", i);
}
 
vector<pi> dual_vtx;
int gph[MAXN * 4][4];
int fce[MAXN * 4][4];
 
int main(){
	scanf("%d %*d",&n);
	for(int i=0; i<n; i++){
		scanf("%d %d",&a[i].x,&a[i].y);
		a[i].idx = i + 1;
		for(int j=0; j<2; j++){
			for(int k=0; k<2; k++){
				dual_vtx.emplace_back(a[i].x + j, a[i].y + k);
			}
		}
	}
	sort(dual_vtx.begin(), dual_vtx.end());
	dual_vtx.resize(unique(dual_vtx.begin(), dual_vtx.end()) - dual_vtx.begin());
	sort(a, a + n);
	int comp = n;
	AGISEOKHWAN.init(n);
	for(int i=0; i<n; i++){
		rev[a[i].idx] = i;
		for(int j=0; j<8; j++){
			int pos = lower_bound(a, a + n, (point){a[i].x + dx[j], a[i].y + dy[j], -1}) - a;
			if(pos < n && pi(a[i].x + dx[j], a[i].y + dy[j]) == pi(a[pos].x, a[pos].y)){
				prec[i][j] = pos;
				comp -= AGISEOKHWAN.uni(i, pos);
			}
			else prec[i][j] = -1;
		}
	}
	if(comp != 1){
		puts("NO");
		return 0;
	}
	memset(gph, -1, sizeof(gph));
	memset(fce, -1, sizeof(fce));
	auto add_edge = [&](int sx, int sy, int ex, int ey, int dir1, int dir2){
		auto l = lower_bound(dual_vtx.begin(), dual_vtx.end(), pi(sx, sy)) - dual_vtx.begin();
		auto r = lower_bound(dual_vtx.begin(), dual_vtx.end(), pi(ex, ey)) - dual_vtx.begin();
		gph[l][dir1] = r;
		gph[r][dir2] = l;
	};
	for(int i=0; i<n; i++){
		add_edge(a[i].x, a[i].y, a[i].x + 1, a[i].y, 0, 2);
		add_edge(a[i].x, a[i].y, a[i].x, a[i].y + 1, 1, 3);
		add_edge(a[i].x + 1, a[i].y + 1, a[i].x + 1, a[i].y, 3, 1);
		add_edge(a[i].x + 1, a[i].y + 1, a[i].x, a[i].y + 1, 2, 0);
	}
	auto getPos = [&](pi p){
		int pos = lower_bound(dual_vtx.begin(), dual_vtx.end(), p) - dual_vtx.begin();
		return pos;
	};
	auto getNext = [&](int pos, int d){
		auto p = dual_vtx[pos];
		p.first += dx[d];
		p.second += dy[d];
		return getPos(p);
	};
	for(int i=0; i<dual_vtx.size(); i++){
		for(int j=0; j<4; j++){
			if(gph[i][j] != -1 && fce[i][j] == -1){
				faces++;
				int px = i, py = j;
				while(fce[px][py] == -1){
					fce[px][py] = faces;
					px = getNext(px, py);
					py ^= 2;
					py = (py + 1) % 4;
					while(gph[px][py] == -1) py = (py + 1) % 4;
				}
				assert(px == i && py == j);
			}
		}
	}
	for(int i=0; i<n; i++){
		int ll = getPos(pi(a[i].x, a[i].y));
		int lr = getPos(pi(a[i].x, a[i].y + 1));
		int rl = getPos(pi(a[i].x + 1, a[i].y));
		int rr = getPos(pi(a[i].x + 1, a[i].y + 1));
		dual_edge[i][0] = pi(fce[rl][1], fce[rr][3]);
		dual_edge[i][1] = pi(fce[rr][2], fce[lr][0]);
		dual_edge[i][2] = pi(fce[lr][3], fce[ll][1]);
		dual_edge[i][3] = pi(fce[ll][0], fce[rl][2]);
		for(int j=0; j<4; j++){
			disj[dual_edge[i][j].first].push_back({i, j, 0});
			disj[dual_edge[i][j].second].push_back({i, j, 1});
		}
	}
	outer_area = fce[0][0];
	solve();
}

