#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include <stack>
#include <queue>
#include <map>
#include <set>
#include <algorithm>
#include <string>
#include <functional>
#include <vector>
#include <numeric>
#include <deque>
#include <utility>
#include <bitset>
#include <iostream>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;

int m, n;
int trie[30005][2], piv;
int nxt[30005][2];
int fail[30005];
bool term[30005];

queue<int> q;
vector<int> top; // topology order
int rev[30005];
int dp[30005];
int indeg[30005];
bool vis[30005];

void bfs(int x){
	q.push(x);
	vis[x] = 1;
	while(!q.empty()){
		x = q.front();
		q.pop();
		for(int j=0; j<m; j++){
			if(!vis[nxt[x][j]] && !term[nxt[x][j]]){
				vis[nxt[x][j]] = 1;
				q.push(nxt[x][j]);
			}
		}
	}
}

void solve(){
	bfs(0);
	for(int i=0; i<=piv; i++){
		for(int j=0; j<m; j++){
			if(!vis[i] || !vis[nxt[i][j]]) continue;
			indeg[nxt[i][j]]++;
		}
	}
	for(int i=0; i<=piv; i++){
		if(vis[i] && indeg[i] == 0){
			q.push(i);
		}
	}
	while(!q.empty()){
		int qf = q.front();
		q.pop();
		top.push_back(qf);
		rev[qf] = top.size() - 1;
		for(int i=0; i<m; i++){
			int pos = nxt[qf][i];
			if(!vis[pos]) continue;
			indeg[pos]--;
			if(indeg[pos] == 0){
				q.push(pos);
			}
		}
	}
	if(*max_element(indeg, indeg + piv + 1) > 0){
		puts("TAK");
		exit(0);
	}
	for(int i=0; i<=piv; i++){
		for(int j=0; j<m; j++){
			if(!vis[nxt[i][j]] || !vis[i]) continue;
			if(rev[i] >= rev[nxt[i][j]]){
				puts("TAK");
				exit(0);
			}
		}
	}
	fill(dp, dp + piv + 1, -1e9);
	dp[0] = 0;
	for(auto &i : top){
		for(int j=0; j<m; j++){
			if(vis[nxt[i][j]]) dp[nxt[i][j]] = max(dp[i] + 1, dp[nxt[i][j]]);
		}
	}
	int ret = *max_element(dp, dp + piv + 1);
	if(ret == 0) puts("TAK");
	else puts("NIE");
}

int main(){
	m = 2;
	scanf("%d",&n);
	for(int i=0; i<n; i++){
		char str[30005];
		scanf("%s",str);
		int p = 0;
		for(int j=0; str[j]; j++){
			if(!trie[p][str[j] - '0']){
				trie[p][str[j] - '0'] = ++piv;
			}
			p = trie[p][str[j] - '0'];
		}
		term[p] = 1;
	}
	for(int i=0; i<m; i++){
		if(trie[0][i]){
			q.push(trie[0][i]);
		}
	}
	while(!q.empty()){
		int qf = q.front();
		q.pop();
		for(int i=0; i<m; i++){
			if(trie[qf][i]){
				int p = fail[qf];
				while(p && !trie[p][i]){
					p = fail[p];
				}
				p = trie[p][i];
				fail[trie[qf][i]] = p;
				if(term[p]) term[trie[qf][i]] = 1;
				q.push(trie[qf][i]);
			}
		}
	}
	for(int i=0; i<=piv; i++){
		for(int j=0; j<m; j++){
			int pos = i;
			while(!trie[pos][j]){
				pos = fail[pos];
			}
			pos = trie[pos][j];
			nxt[i][j] = pos;
		}
	}
	solve();
}
