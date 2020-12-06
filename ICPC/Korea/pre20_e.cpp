#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int mod = 1e9 + 7;
const int MAXN = 500005;

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

int main(){
	int n, m;
	scanf("%d %d",&n,&m);
	disj.init(n);
	for(int i=1; i<=m; i++){
		int s, e; scanf("%d %d",&s,&e);
		if(disj.uni(s, e) == 0){
			cout << i << endl;
			return 0;
		}
	}
	puts("0");
}
