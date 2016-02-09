#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>
#include <utility>
using namespace std;
typedef pair<int,int> pi;

int n, l[100005], r[100005];
int s1[100005], s2[100005], dep[100005];

int dmin = 1e9, dmax = 0;

void dfs1(int x){
	if(l[x] < 0){
		dmin = min(dmin, dep[x] + 1);
		dmax = max(dmax, dep[x] + 1);
	}
	else{
		dep[l[x]] = dep[x] + 1;
		dfs1(l[x]);
	}
	if(r[x] < 0){
		dmin = min(dmin, dep[x] + 1);
		dmax = max(dmax, dep[x] + 1);
	}
	else{
		dep[r[x]] = dep[x] + 1;
		dfs1(r[x]);
	}
}

void dfs2(int x){
	if(l[x] < 0){
		if(dep[x] + 1 == dmax) s1[x]++;
		s2[x]++;
	}
	else{
		dfs2(l[x]);
		s1[x] += s1[l[x]];
		s2[x] += s2[l[x]];
	}
	if(r[x] < 0){
		if(dep[x] + 1 == dmax) s1[x]++;
		s2[x]++;
	}
	else{
		dfs2(r[x]);
		s1[x] += s1[r[x]];
		s2[x] += s2[r[x]];
	}
} 

int dp[100005];

int vacant(int x, int p){
	if(x == -1){
		return dep[p] + 1 == dmax ? 1e9 : 0;
	}
	return s1[x] == 0 ? 0 : 1e9;
}

int full(int x, int p){
	if(x == -1){
		return dep[p] + 1 == dmax ? 0 : 1e9;
	}
	return s1[x] == s2[x] ? 0 : 1e9;
}

int f(int x){
	if(x == -1) return 0;
	if(~dp[x]) return dp[x];
	int ret = 1e9;
	ret = min(ret, full(l[x], x) + f(r[x]));
	ret = min(ret, 1 + f(l[x]) + full(r[x], x));
	ret = min(ret, f(l[x]) + vacant(r[x], x));
	ret = min(ret, 1 + vacant(l[x], x) + f(r[x]));
	return dp[x] = ret;
}

int main(){
	scanf("%d",&n);
	for(int i=1; i<=n; i++){
		scanf("%d %d",&l[i], &r[i]);
	}
	dfs1(1);
	if(dmax - dmin > 1){
		puts("-1");
		return 0;
	}
	dfs2(1);
	memset(dp, -1, sizeof(dp));
	int ret = f(1);
	if(ret > 1e8) ret = -1;
	printf("%d",ret);
}