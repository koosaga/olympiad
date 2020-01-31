#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXN = 200005;

char str[MAXN];
int trie[MAXN][2], par[MAXN], piv;
lint head[MAXN];

vector<int> stk;

void dfs(int x){
	if(trie[x][0]){
		stk.push_back(x);
		dfs(trie[x][0]);
		stk.pop_back();
	}
	if(trie[x][1]){
		int pp = -1;
		if(sz(stk)){
			pp = stk.back(); 
			stk.pop_back();
		}
		if(~pp) head[trie[x][1]] = head[pp] + 1;
		dfs(trie[x][1]);
		if(~pp) stk.push_back(pp);
	}
}

int main(){
	scanf("%s", str);
	int p = 0;
	vector<int> qr;
	for(int i=0; str[i]; i++){
		if(str[i] == '-'){
			p = par[p];
		}
		else if(str[i] == '('){
			if(!trie[p][0]){
				trie[p][0] = ++piv;
				par[piv] = p;
			}
			p = trie[p][0];
		}
		else{
			if(!trie[p][1]){
				trie[p][1] = ++piv;
				par[piv] = p;
			}
			p = trie[p][1];
		}
		qr.push_back(p);
	}
	dfs(0);
	for(int i=1; i<=piv; i++) head[i] += head[par[i]];
	for(auto &i : qr) printf("%lld\n", head[i]);
}
