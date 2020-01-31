#include<bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXN = 1000005;

int frnt[MAXN];
int val[MAXN * 2], nxt[MAXN * 2], lsz;

void add_edge(int s, int e){
	lsz++;
	val[lsz] = e;
	nxt[lsz] = frnt[s];
	frnt[s] = lsz;
}

int dep[MAXN];
int n, e, w;
int cur, pos;
int sz[MAXN];

pi que[MAXN];
int dfs(int x, int p){
	int piv = 0;
	que[piv++] = pi(x, p);
	for(int itr = 0; itr < piv; itr++){
		int x = que[itr].first;
		int p = que[itr].second;
		for(int ii = frnt[x]; ii; ii = nxt[ii]){
			int i = val[ii];
			if(i == p) continue;
			dep[i] = dep[x] + 1;
			que[piv++] = pi(i, x);
		}
	}
	reverse(que, que + piv);
	for(int itr = 0; itr < piv; itr++){
		int x = que[itr].first;
		int p = que[itr].second;
		sz[x] = (x >= n - w + 1);
		for(int ii = frnt[x]; ii; ii = nxt[ii]){
			int i = val[ii];
			if(i == p) continue;
			sz[x] += sz[i];
		}
		if(sz[x] == w && cur < dep[x]){
			cur = dep[x];
			pos = x;
		}
	}
	return 69;
}

void dfs2(int x, int p){
	int piv = 0;
	que[piv++] = pi(x, p);
	for(int itr = 0; itr < piv; itr++){
		int x = que[itr].first;
		int p = que[itr].second;
		for(int ii = frnt[x]; ii; ii = nxt[ii]){
			int i = val[ii];
			if(i == p) continue;
			dep[i] = dep[x] + 1;
			que[piv++] = pi(i, x);
		}
	}
}

int vl[MAXN], vr[MAXN];

int main(){
	cin >> n >> e >> w;
	for(int i=0; i<n-1; i++){
		int s, e;
		scanf("%d %d",&s,&e);
		add_edge(s, e);
		add_edge(e, s);
	}
	dfs(1, 0);
	dep[pos] = 0;
	dfs2(pos, 0);
	for(int i=n-w+1; i<=n; i++){
		vl[n - i] = dep[i];
	}
	sort(vl, vl + w);
	int q;
	scanf("%d",&q);
	for(int i=0; i<q; i++){
		int x;
		scanf("%d",&x);
		vr[i] = dep[x];
	}
	sort(vl, vl + w);
	sort(vr, vr + q);
	int low = -1;
	for(int i=0; i<q; i++){
		if(low < vl[i]){
			low = vl[i];
		}
		else{
			low++;
			vl[i] = low;
		}
	}
	low = -1;
	for(int i=0; i<q; i++){
		if(low < vr[i]){
			low = vr[i];
		}
		else{
			low++;
			vr[i] = low;
		}
	}
	int ret = 0;
	for(int i=0; i<q; i++){
		ret = max(ret, vl[i] + vr[q-i-1]);
	}
	cout << ret;
}


