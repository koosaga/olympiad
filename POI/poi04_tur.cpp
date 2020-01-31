#include<bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXN = 100005;

int n;

vector<int> gph[MAXN];
vector<int> rev[MAXN];

int comp[MAXN], csz[MAXN], piv;
lint indeg[MAXN], outdeg[MAXN];
vector<int> dfn;
int pa[MAXN], chk[MAXN];

int find(int x){
	if(pa[x] != x) return pa[x] = find(pa[x]);
	if(chk[x]) return pa[x] = find(pa[x + 1]);
	return x;
}

void dfs(int x){
	int pos = 1;
	while(true){
		pos = find(pos);
		if(pos == n + 1) break;
		if(binary_search(all(gph[x]), pos)) pos++;
		else{
			chk[pos] = 1;
			dfs(pos);
		}
	}
	dfn.push_back(x);
}

void rdfs(int x, int p){
	comp[x] = p;
	csz[p]++;
	int pos = 1;
	while(true){
		pos = find(pos);
		if(pos == n + 1) break;
		if(binary_search(all(rev[x]), pos)) pos++;
		else{
			chk[pos] = 1;
			rdfs(pos, p);
		}
	}
}

static char buf[1 << 19]; // size : any number geq than 1024
static int idx = 0;
static int bytes = 0;
static inline int _read() {
	if (!bytes || idx == bytes) {
		bytes = (int)fread(buf, sizeof(buf[0]), sizeof(buf), stdin);
		idx = 0;
	}
	return buf[idx++];
}
static inline int _readInt() {
	int x = 0, s = 1;
	int c = _read();
	while (c <= 32) c = _read();
	if (c == '-') s = -1, c = _read();
	while (c > 32) x = 10 * x + (c - '0'), c = _read();
	if (s < 0) x = -x;
	return x;
}


int main(){
	n = _readInt();
	for(int i=1; i<=n; i++){
		int x = _readInt();
		while(x--){
			int p = _readInt();
			gph[p].push_back(i);
			rev[i].push_back(p);
		}
	}
	iota(pa, pa + n + 2, 0);
	for(int i=1; i<=n; i++){
		sort(gph[i].begin(), gph[i].end());
	//	sort(rev[i].begin(), rev[i].end());
	}
	for(int i=1; i<=n; i++){
		if(!chk[i]){
			chk[i] = 1;
			dfs(i);
		}
	}
	reverse(dfn.begin(), dfn.end());
	iota(pa, pa + n + 2, 0);
	fill(chk, chk + n + 2, 0);
	for(int i=0; i<dfn.size(); i++){
		if(!chk[dfn[i]]){
			chk[dfn[i]] = 1;
			rdfs(dfn[i], ++piv);
		}
	}
	for(int i=1; i<=piv; i++){
		indeg[i] = outdeg[i] = 1ll * (n - csz[i]) * csz[i];
	}
	for(int i=1; i<=n; i++){
		for(auto &j : gph[i]){
			if(comp[i] != comp[j]){
				outdeg[comp[i]]--;
				indeg[comp[j]]--;
			}
		}
	}
	if(count(indeg + 1, indeg + piv + 1, 0) != 1){
		puts("0");
		return 0;
	}
	for(int i=1; i<=piv; i++){
		if(indeg[i] == 0){
			printf("%d ", csz[i]);
			for(int j=1; j<=n; j++){
				if(comp[j] == i) printf("%d ", j);
			}
		}
	}
}

