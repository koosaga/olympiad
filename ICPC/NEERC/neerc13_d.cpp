#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;
using namespace std;

// starts from node 0. assumes there exists at least one dmst.
// edge is reversed : if there is edge s -> e, INSERT IN gph[e]
struct edge { int to, cost, id; };
using elist = vector<edge>;
void dmst(vector<elist> &g, vector<int>& res) {
	const int n = g.size();
	vector<edge*> to(n);
	vector<int> u(n, 0);
	for (int i = 1; i < n; ++i) {
		int mn = g[i][0].cost;
		for (int j = 0; j < g[i].size(); ++j)
			mn = min(mn, g[i][j].cost);
		for (int j = 0; j < g[i].size(); ++j) {
			if (g[i][j].cost == mn)
				to[i] = &g[i][j];
			g[i][j].cost -= mn;
		}
	}
	for (int i = 1; i < n; ++i) {
		if (u[i]) continue;
		int x = i;
		vector<int> order(1, x);
		u[x] = 1;
		while (to[x]->to > 0 && u[to[x]->to] == 0) {
			x = to[x]->to;
			u[x] = 1;
			order.push_back(x);
		}
		int y = to[x]->to;
		vector<int> cycle(find(order.begin(), order.end(), y), order.end());
		if (cycle.size() == 0) continue;
		vector<int> in_cycle(n);
		for (int j = 0; j < cycle.size(); ++j) in_cycle[cycle[j]] = 1;
		vector<int> nw_id(n);
		for (int j = 1; j < n; ++j) nw_id[j] = nw_id[j - 1] + !in_cycle[j];
		int nn = n - cycle.size();
		vector<elist> gn(nn + 1);
		for (int j = 1; j < n; ++j) {
			if (in_cycle[j]) {
				for (int k = 0; k < g[j].size(); ++k)
					if (!in_cycle[g[j][k].to])
						gn[nn].push_back({nw_id[g[j][k].to], g[j][k].cost, g[j][k].id});
			} else {
				for (int k = 0; k < g[j].size(); ++k)
					if (in_cycle[g[j][k].to])
						gn[nw_id[j]].push_back({nn, g[j][k].cost, g[j][k].id});
					else
						gn[nw_id[j]].push_back({nw_id[g[j][k].to], g[j][k].cost, g[j][k].id});
			}
		}
		dmst(gn, res);
		set<int> used_e(res.begin(), res.end());
		for (int j = 0; j < cycle.size(); ++j) {
			bool found = false;
			for (int k = 0; k < g[cycle[j]].size(); ++k)
				found |= used_e.count(g[cycle[j]][k].id);
			if (found) {
				for (int k = 0; k < cycle.size(); ++k) {
					if (k != j)
						res.push_back(to[cycle[k]]->id);
				}
				return;
			}
		}
	}
	for (int i = 1; i < n; ++i) res.push_back(to[i]->id);
}

const int MAXN = 55;
int n;
string s[MAXN];

pi cost(string a, string b){
	auto ret = pi(0, -1);
	for(int i=0; i<a.size(); i++){
		int idx = 0;
		for(int j=0; j<b.size(); j++){
			if(i+j >= a.size() || a[i+j] != b[j]) break;
			idx = j+1;
		}
		ret = max(ret, pi(idx, i));
	}
	return ret;
}

int adj[MAXN][MAXN];
int trie[505][26], piv;
vector<int> gph[MAXN];

void dfs(int v, int ptr){
	vector<int> plist = {ptr};
	for(auto &i : s[v]){
		int cur = plist.back();
		if(!trie[cur][i - 'a']){
			trie[cur][i - 'a'] = ++piv;
		}
		plist.push_back(trie[cur][i - 'a']);
	}
	for(auto &j : gph[v]){
		int x = cost(s[v], s[j]).second;
		dfs(j, plist[x]);
	}
}

int resultNum[505];
int resultChr[505];
void dfs(int x){
	for(int i=0; i<26; i++){
		if(trie[x][i]){
			resultNum[trie[x][i]] = x + 1;
			resultChr[trie[x][i]] = i + 'a';
			dfs(trie[x][i]);
		}
	}
}

int main(){
	cin >> n;
	for(int i=1; i<=n; i++) cin >> s[i];
	for(int i=1; i<=n; i++){
		for(int j=1; j<=n; j++) adj[i][j] = cost(s[i], s[j]).first;
	}
	int curmax = -1;
	vector<int> curset;
	for(int i=1; i<=n; i++){
		int rel[MAXN] = {}, cnt = 0;
		rel[i] = 0;
		for(int j=1; j<=n; j++){
			if(i != j) rel[j] = ++cnt;
		}
		vector<elist> g(n);
		for(int i=1; i<=n; i++){
			for(int j=1; j<=n; j++){
				if(i != j){
					g[rel[j]].push_back({rel[i], -adj[i][j], i * (n+5) + j});
				}
			}
		}
		vector<int> ans;
		dmst(g, ans);
		int sum = 0;
		for(auto &i : ans){
			sum += adj[i / (n+5)][i % (n+5)];
		}
		if(curmax < sum){
			curmax = sum;
			curset = ans;
		}
	}
	set<int> s;
	for(int i=1; i<=n; i++) s.insert(i);
	for(auto &i : curset){
		gph[i / (n+5)].push_back(i % (n+5));
		s.erase(i % (n+5));
	}
	dfs(*s.begin(), 0);
	cout << piv + 1 << endl;
	puts("0");
	dfs(0);
	for(int i=1; i<=piv; i++) printf("%d %c\n", resultNum[i], resultChr[i]);
}
