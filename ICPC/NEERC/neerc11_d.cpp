#include <bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
using lint = long long;
const int MAXN = 400005;

int n;
string str[MAXN];
int trie[MAXN][26], term[MAXN], piv;
int startsWith[MAXN], only[MAXN];
char buf[MAXN];
vector<string> sfx;

lint dfs(int x){
	lint ret = term[x];
	for(int i=0; i<26; i++){
		if(trie[x][i]){
			if(x > 0 && !term[trie[x][i]]) ret += only[i];
			ret += dfs(trie[x][i]);
		}
		else{
			if(x > 0) ret += startsWith[i];
		}
	}
	return ret;
}

int main(){
	freopen("dictionary.in", "r", stdin);
	freopen("dictionary.out", "w", stdout);
	scanf("%d",&n);
	for(int i=0; i<n; i++){
		scanf("%s", buf);
		str[i] = buf;
		int p = 0;
		for(int j=0; j<str[i].size(); j++){
			if(!trie[p][str[i][j] - 'a']){
				trie[p][str[i][j] - 'a'] = ++piv;
			}
			p = trie[p][str[i][j] - 'a'];
			sfx.push_back(str[i].substr(j, str[i].size() - j));
		}
		term[p] = 1;
	}
	sort(sfx.begin(), sfx.end());
	sfx.resize(unique(sfx.begin(), sfx.end()) - sfx.begin());
	for(auto &i : sfx){
		if(i.size() == 1) only[i[0] - 'a'] = 1;
		startsWith[i[0] - 'a']++;
	}
	cout << dfs(0) << endl;
}
