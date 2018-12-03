#include <bits/stdc++.h>
const int MAXN = 50005;
using namespace std;
vector<string> ans_seq;

char buf[55];

void JOIN(int a, int b){
	sprintf(buf, "j %d %d\n", a, b);
	string dap = buf;
	ans_seq.push_back(dap);
}

void RECOLOR(int a, int c1, int c2){
	sprintf(buf, "r %d %d %d\n", a, c1, c2);
	string dap = buf;
	ans_seq.push_back(dap);
}

void CONNECT(int a, int c1, int c2){
	sprintf(buf, "c %d %d %d\n", a, c1, c2);
	string dap = buf;
	ans_seq.push_back(dap);
}

vector<int> gph[MAXN];
int n, dfn[MAXN], low[MAXN], piv;

void dfs(int x, int p){
	dfn[x] = low[x] = ++piv;
	for(auto &i : gph[x]){
		if(i == p) continue;
		if(!dfn[i]){
			dfs(i, x);
			low[x] = min(low[x], low[i]);
		}
		else low[x] = min(low[x], dfn[i]);
	}
}

vector<int> bcc[MAXN], cmp[MAXN]; int c;

void color(int x, int p){
	if(p){
		bcc[p].push_back(x);
		cmp[x].push_back(p);
	}
	for(auto &i : gph[x]){
		if(cmp[i].size()) continue;
		if(low[i] >= dfn[x]){
			bcc[++c].push_back(x);
			cmp[x].push_back(c);
			color(i, c);
		}
		else color(i, p);
	}
}

void merge(int c, int v);

void solve(int c){
	if(bcc[c].size() == 2){
		merge(c, bcc[c][1]);
		return;
	}
	else{
		for(int i=1; i<bcc[c].size(); i++){
			merge(c, bcc[c][i]);
		}
		RECOLOR(bcc[c][1], 2, 4);
		JOIN(bcc[c][1], bcc[c][2]);
		CONNECT(bcc[c][1], 2, 4);
		for(int i=3; i<bcc[c].size(); i++){
			RECOLOR(bcc[c][i], 2, 3);
			JOIN(bcc[c][i-1], bcc[c][i]);
			CONNECT(bcc[c][i-1], 2, 3);
			RECOLOR(bcc[c][i], 2, 1);
			RECOLOR(bcc[c][i], 3, 2);
		}
		RECOLOR(bcc[c][1], 3, 2);
		RECOLOR(bcc[c][1], 4, 3);
	}
}

void merge(int c, int v){
	RECOLOR(v, 1, 4);
	for(auto &i : cmp[v]){
		if(i != c){
			solve(i);
			JOIN(v, bcc[i][1]);
		}
	}
	CONNECT(v, 2, 4);
	CONNECT(v, 3, 4);
	RECOLOR(v, 2, 1);
	RECOLOR(v, 3, 1);
	RECOLOR(v, 4, 2);
}

int main(){
	int k;
	scanf("%d %d",&n,&k);
	while(k--){
		int x, y; scanf("%d %d",&x,&y);
		gph[x].push_back(y);
		gph[y].push_back(x);
		continue;
		for(int i=0; i<x-1; i++){
			int z; scanf("%d",&z);
			gph[y].push_back(z);
			gph[z].push_back(y);
			y = z;
		}
	}
	dfs(1, 0);
	color(1, 0);
	merge(-1, 1);
	printf("%d\n", ans_seq.size());
	for(auto &i : ans_seq) printf(i.c_str());
}
