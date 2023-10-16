#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
const int MAXN = 300005;
using lint = long long;
using pi = pair<int, int>;

int col[MAXN], bad;
int cnt[3];
vector<int> gph[MAXN];

void dfs(int x, int c){
	if(col[x]){
		if(col[x] != c) bad = 1;
		return;
	}
	col[x] = c;
	cnt[col[x]]++;
	for(auto &i : gph[x]) dfs(i, 3 - c);
}

lint fn(int x){
	return 1ll * x * (x - 1) / 2;
}

int main(){
	int n, m;
	scanf("%d %d",&n,&m);
	for(int i=0; i<n; i++) scanf("%*d");
	for(int i=0; i<m; i++){
		int s, e; scanf("%d %d",&s,&e);
		gph[s].push_back(e);
		gph[e].push_back(s);
	}
	lint ret = 0;
	for(int i=1; i<=n; i++){
		if(!col[i]){
			bad = 0;
			cnt[1] = cnt[2] = 0;
			dfs(i, 1);
			if(bad){
				ret += fn(cnt[1] + cnt[2]);
			}
			else{
				ret += fn(cnt[1]) + fn(cnt[2]);
			}
		}
	}
	cout << ret << endl;
}
