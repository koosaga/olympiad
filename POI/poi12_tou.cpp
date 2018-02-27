#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
const int MAXN = 1000005;

struct disj{
	int pa[MAXN];
	void init(int n){
		iota(pa, pa + n + 1, 0);
	}
	int find(int x){
		return pa[x] = (pa[x] == x ? x : find(pa[x]));
	}
	bool uni(int p, int q){
		p = find(p);
		q = find(q);
		if(p == q) return 0;
		pa[q] = p; return 1;
	}
}disj;

int n, m, k;

vector<pi> edg, ans;


int main(){
	scanf("%d %d %d",&n,&m,&k);
	disj.init(n);
	for(int i=0; i<m; i++){
		int s, e;
		scanf("%d %d",&s,&e);
		if(s > k){
			disj.uni(s, e);
		}
		else{
			edg.push_back(pi(s, e));
		}
	}
	for(auto &i : edg){
		if(!disj.uni(i.first, i.second)){
			ans.push_back(i);
		}
	}
	printf("%d\n", ans.size());
	for(auto &i : ans){
		printf("%d %d\n", i.first, i.second);
	}
}

