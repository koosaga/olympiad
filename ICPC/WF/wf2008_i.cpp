#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<lint, int> pi;
const int mod = 1e9 + 7;

int n, m;
int trie[255][26], fail[255], term[255], piv;
int nxt[255][26];

void init(vector<string> &v){
	memset(trie, 0, sizeof(trie));
	memset(fail, 0, sizeof(fail));
	memset(term, 0, sizeof(term));
	memset(nxt, 0, sizeof(nxt));
	piv = 0;
	int w = 1;
	for(auto &i : v){
		int p = 0;
		for(auto &j : i){
			if(!trie[p][j - 'a']){
				trie[p][j - 'a'] = ++piv;
			}
			p = trie[p][j - 'a'];
		}
		term[p] |= w;
		w <<= 1;
	}
	queue<int> que;
	for(int i=0; i<26; i++){
		if(trie[0][i]) que.push(trie[0][i]);
	}
	while(!que.empty()){
		int x = que.front();
		que.pop();
		for(int i=0; i<26; i++){
			if(trie[x][i]){
				int p = fail[x];
				while(p && !trie[p][i]) p = fail[p];
				p = trie[p][i];
				fail[trie[x][i]] = p;
				term[trie[x][i]] |= term[p];
				que.push(trie[x][i]);
			}
		}
	}
	for(int i=0; i<=piv; i++){
		for(int j=0; j<26; j++){
			int p = i;
			while(p && !trie[p][j]) p = fail[p];
			p = trie[p][j];
			nxt[i][j] = p;
		}
	}
}

lint dp[27][105][1024];

lint f(int l, int c, int msk){
	if(l == 0) return msk == 0;
	if(~dp[l][c][msk]) return dp[l][c][msk];
	lint ret = 0;
	for(int i=0; i<26; i++){
		ret += f(l-1, nxt[c][i], msk & ~term[nxt[c][i]]);
	}
	return dp[l][c][msk] = ret;
}

string stk;

void bktk(int l, int c, int msk){
	if(l == 0){
		printf("%s\n", stk.c_str());
		return;
	}
	for(int i=0; i<26; i++){
		if(f(l-1, nxt[c][i], msk & ~term[nxt[c][i]])){
			stk.push_back(i + 'a');
			bktk(l-1, nxt[c][i], msk & ~term[nxt[c][i]]);
			stk.pop_back();
		}
	}
}

int main(){
	int n, m, tc = 0;
	while(1){
		scanf("%d %d",&n,&m);
		if(n + m == 0) break;
		vector<string> v;
		for(int i=0; i<m; i++){
			char str[55];
			scanf("%s", str);
			v.push_back(str);
		}
		init(v);
		memset(dp, -1, sizeof(dp));
		lint k = f(n, 0, (1<<m)-1);
		printf("Case %d: %lld suspects\n", ++tc, k);
		if(k <= 42)	bktk(n, 0, (1<<m) - 1);
	}
}
