#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
const int MAXN = 1000005;

vector<int> gph[MAXN];
vector<int> pth;
int n, r, m;
int par[MAXN], dp[MAXN], chk[MAXN];

void dfs(int x, int p){
	for(auto &i : gph[x]){
		if(i == p) continue;
		par[i] = x;
		dfs(i, x);
	}
}

int dfs2(int x, int p){
	vector<int> v = {0, 0};
	for(auto &i : gph[x]){
		if(i == p) continue;
		v.push_back(dfs2(i, x));
	}
	sort(v.begin(), v.end());
	return v[v.size() - 2] + gph[x].size() - 1;
}

vector<int> pthv[MAXN];

int trial(int x){
	int session = 1;
	for(int i=0; i<pth.size() - 1; i++){
		int v = pthv[i].size();
		for(auto &j : pthv[i]){
			if(j + v > x){
				v--;
				session--;
				x--;
			}
		}
		if(session < 0) return 0;
		session++;
	}
	return x>=0;
}

int main(){
	scanf("%d %d %d",&n,&r,&m);
	for(int i=0; i<n-1; i++){
		int s, e;
		scanf("%d %d",&s,&e);
		gph[s].push_back(e);
		gph[e].push_back(s);
	}
	dfs(r, -1);
	for(int i=m; i!=r; i=par[i]){
		pth.push_back(i);
	}
	pth.push_back(r);
	for(auto &i : pth) chk[i] = 1;
	for(int i=0; i<pth.size() - 1; i++){
		for(auto &j : gph[pth[i]]){
			if(!chk[j]) pthv[i].push_back(dfs2(j, pth[i]));
		}
	}
	int sum = 0;
	for(int i=pth.size()-2; i>=0; i--){
		for(auto &j : pthv[i]){
			j += sum;
		}
		sort(pthv[i].begin(), pthv[i].end());
		reverse(pthv[i].begin(), pthv[i].end());
		sum += gph[pth[i]].size() - 2;
	}
	int s = 0, e = 3e6;
	while(s != e){
		int m = (s+e)/2;
		if(trial(m)) e = m;
		else s = m+1;
	}
	cout << s;
}
