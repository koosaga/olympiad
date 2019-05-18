#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100005;
const int MAXT = 270000;
const int inf = 1e9;

int n, a[MAXN];
vector<int> gph[MAXN];
int sz[MAXN], chn[MAXN], csz[MAXN], dfn[MAXN], par[MAXN], piv;

int slack[MAXN][3];

struct mtrx{
	int a[3][3];
}E;

mtrx mul(mtrx a, mtrx b){
	mtrx c; memset(c.a, 0x3f, sizeof(c.a));
	for(int i=0; i<3; i++){
		for(int j=0; j<3; j++){
			for(int k=0; k<3; k++){
				c.a[j][k] = min(a.a[j][i] + b.a[i][k], c.a[j][k]);
			}
		}
	}
	return c;
}

struct seg{
	int lim;
	mtrx tree[MAXT];
	void init(int n){
		for(lim = 1; lim <= n; lim <<= 1);
		for(int i=0; i<MAXT; i++){
			tree[i] = E;
		}
	}
	void add(int x, mtrx v){
		x += lim;
		tree[x] = v;
		while(x > 1){
			x >>= 1;
			tree[x] = mul(tree[2*x], tree[2*x+1]);
		}
	}
	mtrx query(int s, int e){
		s += lim;
		e += lim;
		mtrx lmtrx = E, rmtrx = E;
		while(s < e){
			if(s%2 == 1) lmtrx = mul(lmtrx, tree[s++]); 
			if(e%2 == 0) rmtrx = mul(tree[e--], rmtrx);
			s >>= 1;
			e >>= 1;
		}
		if(s == e) rmtrx = mul(tree[s], rmtrx);
		return mul(lmtrx, rmtrx);
	}	
}seg;

vector<int> line_query(int s, int e){
	auto quer = seg.query(s, e);
	vector<int> nxt(3);
	for(int i=0; i<3; i++){
		nxt[i]  = 1e9;
		for(int j=0; j<3; j++) nxt[i] = min(nxt[i], quer.a[i][j]);
	}
	return nxt;
}

void slack_update(int v){
	mtrx m;
	m.a[0][0] = slack[v][0] + (a[v] ? inf : 0);
	m.a[0][1] = slack[v][1] + 1 + (a[v] == 2 ? inf : 0);
	m.a[0][2] = slack[v][2] + 1 + (a[v] == 1 ? inf : 0);

	m.a[1][0] = slack[v][0] + (a[v] ? inf : 0);
	m.a[1][1] = slack[v][1] + 0 + (a[v] == 2 ? inf : 0);
	m.a[1][2] = slack[v][2] + 1 + (a[v] == 1 ? inf : 0);

	m.a[2][0] = slack[v][0] + (a[v] ? inf : 0);
	m.a[2][1] = slack[v][1] + 1 + (a[v] == 2 ? inf : 0);
	m.a[2][2] = slack[v][2] + 0 + (a[v] == 1 ? inf : 0);

	seg.add(v, m);
}

void Do(int v, int w){
	vector<int> pth;
	for(int i = v; i; i = par[chn[i]]){
		pth.push_back(i);
	}
	reverse(pth.begin(), pth.end());
	for(auto &i : pth){
		auto queryV = line_query(dfn[chn[i]], dfn[chn[i]] + csz[chn[i]] - 1);
		int parV = par[chn[i]];
		parV = dfn[parV];
		slack[parV][0] -= queryV[0];
		slack[parV][1] -= queryV[1];
		slack[parV][2] -= queryV[2];
		if(parV) slack_update(parV);
	}
	a[dfn[v]] = w;
	slack_update(dfn[v]);
	reverse(pth.begin(), pth.end());
	for(auto &i : pth){
		auto queryV = line_query(dfn[chn[i]], dfn[chn[i]] + csz[chn[i]] - 1);
		int parV = par[chn[i]];
		parV = dfn[parV];
		slack[parV][0] += queryV[0];
		slack[parV][1] += queryV[1];
		slack[parV][2] += queryV[2];
		if(parV) slack_update(parV);
	}
}

int cat(int v) {
	Do(v, 1);
	return *min_element(slack[0], slack[0] + 3);
}

int dog(int v) {
	Do(v, 2);
	return *min_element(slack[0], slack[0] + 3);
}

int neighbor(int v) {
	Do(v, 0);
	return *min_element(slack[0], slack[0] + 3);
}

void dfs(int x){
	sz[x] = 1;
	for(auto &i : gph[x]){
		gph[i].erase(find(gph[i].begin(), gph[i].end(), x));
		par[i] = x;
		dfs(i);
		sz[x] += sz[i];
	}
	sort(gph[x].begin(), gph[x].end(), [&](const int &a, const int &b){
		return sz[a] > sz[b];
	});
}

void hld(int x){
	dfn[x] = ++piv;
	csz[chn[x]]++;
	if(gph[x].empty()) return;
	chn[gph[x][0]] = chn[x];
	hld(gph[x][0]);
	for(int i=1; i<gph[x].size(); i++){
		chn[gph[x][i]] = gph[x][i];
		hld(gph[x][i]);
	}
}

void initialize(int N, std::vector<int> A, std::vector<int> B) {
	n = N;
	for(int i=0; i<n-1; i++){
		gph[A[i]].push_back(B[i]);
		gph[B[i]].push_back(A[i]);
	}
	dfs(1);
	chn[1] = 1;
	hld(1);
	for(int i=0; i<3; i++){
		for(int j=0; j<3; j++){
			E.a[i][j] = (i == j ? 0 : 1e9);
		}
	}
	seg.init(n);
}


int readInt(){
	int i;
	if(scanf("%d",&i)!=1){
		fprintf(stderr,"Error while reading input\n");
		exit(1);
	}
	return i;
}

int main(){
	int N=readInt();
	
	std::vector<int> A(N-1),B(N-1);
	for(int i=0;i<N-1;i++)
	{
		A[i]=readInt();
		B[i]=readInt();
	}
	initialize(N,A,B);
	int Q;
	assert(scanf("%d",&Q)==1);
	std::vector <int> T(Q),V(Q);
	std::vector<int> res(Q);
	for(int i=0;i<Q;i++)
	{
		T[i]=readInt();
		V[i]=readInt();
		int j = i;
		if(T[j]==1) res[j]=cat(V[j]);
		else if(T[j]==2) res[j]=dog(V[j]);
		else res[j]=neighbor(V[j]);
		printf("%d\n",res[j]);
	}
	return 0;
}
