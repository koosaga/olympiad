#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100005;

bool leaf[MAXN];
int sz[MAXN];
map<string, int> gph[MAXN];
int t;

void dfs(int x){
	for(auto &i : gph[x]){
		dfs(i.second);
		sz[x] += sz[i.second];
	}
}

void dfsp(int x, string s){
	if(leaf[x]) return;
	bool ok = 0;
	bool fold = 0;
	for(auto &i : gph[x]){
		if(!leaf[i.second] && sz[i.second] >= t) ok = 1;
		if(!leaf[i.second]) fold = 1;
	}
	if(ok){
		printf("- %s %d\n", s.c_str(), sz[x]);
	}
	else if(fold){
		printf("+ %s %d\n", s.c_str(), sz[x]);
	}
	else{
		printf("  %s %d\n", s.c_str(), sz[x]);
	}
	if(ok){
		for(auto &i : gph[x]){
			dfsp(i.second, s + i.first + "/");
		}
	}
}


vector<string> splice(string s){
	string aux;
	vector<string> v;
	for(int i=0; i<s.size(); i++){
		if(s[i] == '/'){
			if(aux.size()){
				v.push_back(aux);
				aux.clear();
			}
		}
		else aux.push_back(s[i]);
	}
	if(aux.size()) v.push_back(aux);
	return v;
}

int main(){
	int n;
	scanf("%d",&n);
	int cnt = 0;
	for(int i=0; i<n; i++){
		string s;
		int x;
		cin >> s >> x;
		vector<string> v = splice(s);
		int r = 0;
		for(auto &i : v){
			if(gph[r].find(i) == gph[r].end()){
				gph[r][i] = ++cnt;
			}
			r = gph[r][i];
		}
		leaf[r] = 1;
		sz[r] = x;
	}
	cin >> t;
	dfs(0);
	dfsp(0, "/");
}
