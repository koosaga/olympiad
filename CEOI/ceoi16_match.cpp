#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
const int mod = 1e9 + 7;
typedef pair<int, int> pi;

int n;
char str[100005], ans[100005];
int trie[100005][26], par[100005], pae[100005], idx[100005], piv;
vector<int> nv[100005];

bool solve(int s, int e){
	if(s == e) return true;
	auto l = lower_bound(nv[idx[s+1]].begin(), nv[idx[s+1]].end(), e);
	if(l == nv[idx[s+1]].begin()) return false;
	if(*--l > s){
		ans[s] = '(';
		ans[*l] = ')';
		return solve(s+1, *l) && solve(*l + 1, e);
	}
	else return false;
}

int main(){
	scanf("%s", str);
	n = strlen(str);
	int p = 0;
	for(int i=0; i<n; i++){
		if(p > 0 && pae[p] == str[i]){
			p = par[p];
			idx[i+1] = p;
			continue;
		}
		if(!trie[p][str[i] - 'a']) trie[p][str[i] - 'a'] = ++piv;
		int prv = p;
		p = trie[p][str[i] - 'a'];
		par[p] = prv;
		pae[p] = str[i];
		idx[i+1] = p;
	}
	for(int i=0; i<=n; i++) nv[idx[i]].push_back(i);
	if(p != 0 || n % 2 == 1 || !solve(0, n)){
		puts("-1");
		return 0;
	}
	puts(ans);
}
