#include <bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
using lint = long long;
const int MAXN = 20005;

int mtch[MAXN], piv;
int par[MAXN], chk[MAXN];

int dfs(string s){
	if(s.size() == 1){
		mtch[s[0]] = ++piv;
		return piv;
	}
	s = s.substr(1, s.size() - 2);
	int cnt = 0;
	for(int i=0; i<s.size(); i++){
		if(s[i] == '[') cnt++;
		if(s[i] == ']') cnt--;
		if(cnt == 0 && s[i] == '-'){
			int L = dfs(s.substr(0, i));
			int R = dfs(s.substr(i + 1, s.size() - i - 1));
			par[L] = par[R] = ++piv;
			return piv;
		}
	}
	assert(0);
}

int main(){
	string s;
	cin >> s;
	int root = dfs(s);
	int cnt = 0;
	for(auto &i : s){
		if(isalpha(i)) cnt++;
	}
	while(cnt--){
		string s; int x;
		cin >> s >> x;
		int pos = mtch[s[0]];
		for(int j=0; j<x; j++){
			chk[pos]++;
			pos = par[pos];
		}
		if(pos == 0){
			puts("No");
			return 0;
		}
		chk[pos]++;
	}
	if(count(chk, chk + MAXN, 1) == root) puts("Yes");
	else puts("No");
}
