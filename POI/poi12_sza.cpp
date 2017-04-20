#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;

struct query{
	int idx, st, ed, k;
	bool operator<(const query &q)const{
		return st < q.st;
	}
};

struct elem{
	int s, e, x;
	bool operator<(const elem &e)const{
		return s < e.s;
	}
};

int dp[100005];
elem a[1005];
query b[1000005];
bool ans[1000005];
int n, q;

int main(){
	scanf("%d",&n);
	for(int i=1; i<=n; i++){
		int c, aa, b;
		scanf("%d %d %d",&c,&aa,&b);
		a[i] = {aa, b, c};
	}
	scanf("%d",&q);
	for(int i=0; i<q; i++){
		scanf("%d %d %d",&b[i].st, &b[i].k, &b[i].ed);
		b[i].idx = i;
		b[i].ed += b[i].st;
	}
	sort(b, b+q);
	sort(a+1, a+n+1);
	fill(dp + 1, dp + 100001, -1e9);
	dp[0] = 1e9;
	int p = 0;
	for(int i=1; i<=n; i++){
		while(p < q && b[p].st < a[i].s){
			if(dp[b[p].k] > b[p].ed) ans[b[p].idx] = 1;
			p++;
		}
		for(int j=100000; j>=a[i].x; j--){
			dp[j] = max(dp[j], min(dp[j - a[i].x], a[i].e));
		}
	}
	while(p < q){
		if(dp[b[p].k] > b[p].ed) ans[b[p].idx] = 1;
		p++;
	}
	for(int i=0; i<q; i++) puts(ans[i] ? "TAK" : "NIE");
}
