#include <bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
using lint = long long;
const int MAXN = 200005, MAXC = 26;
const int mod = 1e9 + 7;

int trie[MAXN][MAXC], fail[MAXN], term[MAXN], piv;
int realfail[MAXN];

void init(vector<string> &v){
	memset(trie, 0, sizeof(trie));
	memset(fail, 0, sizeof(fail));
	memset(term, 0, sizeof(term));
	piv = 0;
	for(auto &i : v){
		int p = 0;
		for(auto &j : i){
			j -= 'a';
			if(!trie[p][j]) trie[p][j] = ++piv;
			p = trie[p][j];
		}
		term[p] = i.size();
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
				realfail[trie[x][i]] = realfail[p];
				if(term[p]) realfail[trie[x][i]] = p;
				que.push(trie[x][i]);
			}
		}
	}
}

char buf[MAXN];
int dp[MAXN];

int main(){
	int n;
	cin >> n;
	vector<string> v(n);
	for(auto &i : v){
		scanf("%s", buf);
		i = buf;
	}
	init(v);
	scanf("%s", buf + 1);
	dp[0] = 1;
	int p = 0;
	for(int i=1; buf[i]; i++){
		while(p && !trie[p][buf[i] - 'a']) p = fail[p];
		p = trie[p][buf[i] - 'a'];
		if(term[p]) dp[i] += dp[i - term[p]];
		for(int j = realfail[p]; j != 0; j = realfail[j]){
			dp[i] += dp[i - term[j]];
			dp[i] %= mod;
		}
	}
	cout << dp[strlen(buf + 1)] << endl;
}
