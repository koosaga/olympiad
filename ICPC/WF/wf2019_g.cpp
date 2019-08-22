#include <bits/stdc++.h>
#define sz(v) ((int)((v).size()))
using namespace std;
const int MAXN = 1000005;
const int MAXC = 26;
const int mod = 998244353;
using lint = long long;
using pi = pair<int, int>;

int trie[MAXN][MAXC], fail[MAXN], term[MAXN], nxt[MAXN][MAXC], piv;

int n, q;
vector<pi> gph[MAXN];
vector<int> ftree[MAXN];
string str[MAXN];
int par[MAXN];
char buf[MAXN];
int ret[MAXN];

int aho_pos[MAXN];
int cnt[MAXN];

void dfs(int x){
	for(auto &i : gph[x]){
		int y = nxt[aho_pos[x]][i.first - 'A'];
		aho_pos[i.second] = y;
		dfs(i.second);
	}
}

int func[26];

void dfsf(int x){
	vector<int> backup(func, func + 26);
	for(int i=0; i<26; i++){
		if(trie[x][i]) func[i] = trie[x][i];
		nxt[x][i] = func[i];
	}
	for(auto &i : ftree[x]){
		dfsf(i);
	}
	for(int i=0; i<26; i++) func[i] = backup[i];
}

void dfsg(int x){
	for(auto &i : ftree[x]){
		dfsg(i);
		cnt[x] += cnt[i];
	}
}

int main(){
	scanf("%d",&n);
	scanf("%d",&q);
	for(int i=1; i<=n; i++){
		int p;
		scanf("%s %d", buf, &p);
		par[i] = p;
		gph[p].emplace_back(*buf, i);
	}
	for(int i=1; i<=q; i++){
		scanf("%s", buf);
		str[i] = buf;
		reverse(str[i].begin(), str[i].end());
		int p = 0;
		for(auto j : str[i]){
			j -= 'A';
			if(!trie[p][j]) trie[p][j] = ++piv;
			p = trie[p][j];
		}
		term[i] = p;
	}
	queue<int> que;
	for(int i=0; i<MAXC; i++){
		if(trie[0][i]) que.push(trie[0][i]);
	}
	while(!que.empty()){
		int x = que.front();
		que.pop();
		for(int i=0; i<MAXC; i++){
			if(trie[x][i]){
				int p = fail[x];
				while(p && !trie[p][i]) p = fail[p];
				p = trie[p][i];
				fail[trie[x][i]] = p;
				que.push(trie[x][i]);
			}
		}
	}
	for(int i=1; i<=piv; i++){
		ftree[fail[i]].push_back(i);
	}
	dfsf(0);
	dfs(0);
	for(int i=1; i<=n; i++) cnt[aho_pos[i]]++;
	dfsg(0);
	for(int i=1; i<=q; i++){
		printf("%d\n", cnt[term[i]]);
	}
}


