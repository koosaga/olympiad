#include <bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
using lint = long long;
const int MAXN = 100005;

vector<int> gph[MAXN];
vector<int> v;
int n;

void dfs(int x, int p){
	if(gph[x].size() == 1) v.push_back(x);
	for(auto &i : gph[x]){
		if(i != p) dfs(i, x);
	}
}

int main(){
	scanf("%d",&n);
	for(int i=1; i<n; i++){
		int s, e; scanf("%d %d",&s,&e);
		gph[s].push_back(e);
		gph[e].push_back(s);
	}
	if(n == 2){
		puts("1\n1 2");
		return 0;
	}
	for(int i=1; i<=n; i++){
		if(gph[i].size() != 1){
			dfs(i, -1);
			int k = (v.size() + 1) / 2;
			cout << k << endl;
			for(int i=0; i<k; i++){
				printf("%d %d\n", v[i], v[v.size() - k + i]);
			}
			return 0;
		}
	}
}
