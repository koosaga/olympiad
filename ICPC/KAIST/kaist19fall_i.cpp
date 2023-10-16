#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
using namespace std;
const int MAXN = 505;
using lint = long long;
using pi = pair<int, int>;

struct edge{ int s, e, x; };
struct answer{ 
	lint len;
	int s, e, pos; 
	bool operator<(const answer &a)const{
		return len < a.len;
	}
};

int n, m;
int edg[MAXN][MAXN];
lint adj[MAXN][MAXN];
vector<int> ord[MAXN];
bool vis[MAXN];

int main(){
	scanf("%d %d",&n,&m);
	memset(adj, 0x3f, sizeof(adj));
	for(int i=0; i<m; i++){
		int s, e, x; scanf("%d %d %d",&s,&e,&x);
		edg[s][e] = edg[e][s] = x;
		adj[s][e] = adj[e][s] = x;
	}
	for(int i=1; i<=n; i++){
		adj[i][i] = 0;
	}
	for(int i=1; i<=n; i++){
		for(int j=1; j<=n; j++){
			for(int k=1; k<=n; k++){
			    adj[j][k] = min(adj[j][i] + adj[i][k], adj[j][k]);
			}
		}
	}
	for(int i=1; i<=n; i++){
		ord[i].resize(n);
		iota(ord[i].begin(), ord[i].end(), 1);
		sort(ord[i].begin(), ord[i].end(), [&](const int &a, const int &b){
			return adj[i][a] < adj[i][b];
		});
	}
	answer dap = {(lint)1e18, -1, -1, -1};
	auto upload = [&](int s, int e, int l, int x, int y){
		answer ans;
		ans.len = adj[s][ord[s][x - 1]] + adj[e][ord[e][y - 1]] + l;
		ans.s = s, ans.e = e;
		ans.pos = ans.len - 2 * adj[s][ord[s][x - 1]];
		dap = min(dap, ans);
	};
	for(int i=1; i<=n; i++){
		for(int j=1; j<i; j++){
			if(!edg[i][j]) continue;
			memset(vis, 0, sizeof(vis));
			int ptr = n;
			for(int k=0; k<sz(ord[i]); k++){
				vis[ord[i][k]] = 1;
				while(ptr > 0 && vis[ord[j][ptr-1]]) ptr--;
				if(ptr > 0 && abs(adj[i][ord[i][k]] - adj[j][ord[j][ptr - 1]]) <= edg[i][j]){
					upload(i, j, edg[i][j], k + 1, ptr);
				}
			}
		}
	}
	cout << dap.len << endl;
	vector<int> L, R;
	L.push_back(dap.s);
	R.push_back(dap.e);
	for(int j=1; j<=n; j++){
		if(j == dap.s || j == dap.e) continue;
		lint from_s = 2 * adj[dap.s][j] + dap.pos;
		lint from_e = 2 * adj[dap.e][j] + 2 * edg[dap.s][dap.e] - dap.pos;
		if(from_s <= from_e) L.push_back(j);
		else R.push_back(j);
	}
	sort(L.begin(), L.end(), [&](const int &a, const int &b){
		return adj[dap.s][a] < adj[dap.s][b];
	});
	sort(R.begin(), R.end(), [&](const int &a, const int &b){
		return adj[dap.e][a] < adj[dap.e][b];
	});
	cout << dap.s << " " << dap.e << endl;
	for(int i=1; i<sz(L); i++){
		for(int j=0; j<i; j++){
			if(adj[dap.s][L[j]] + edg[L[j]][L[i]] == adj[dap.s][L[i]]){
				printf("%d %d\n", L[i], L[j]);
				break;
			}
		}
	}
	for(int i=1; i<sz(R); i++){
		for(int j=0; j<i; j++){
			if(adj[dap.e][R[j]] + edg[R[j]][R[i]] == adj[dap.e][R[i]]){
				printf("%d %d\n", R[i], R[j]);
				break;
			}
		}
	}
}
