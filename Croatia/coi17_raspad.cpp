#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;

struct disj{
	int pa[2500005];
	void init(int n){
		for(int i=1; i<=n; i++) pa[i] = i;
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
char str[100005][55];
int col[100005][55];
pi stp[2500005], edp[2500005];
int l1[2500005], l2[2500005], h1[2500005], h2[2500005];

int dfs(int prv, int cur, int dst){
	if(cur == dst) return cur;
	if(prv > cur){
		if(prv == l2[cur]){
			if(l1[cur] <= h1[cur]){
				return min(dfs(cur, l1[cur], dst), cur);
			}
			else{
				return min(dfs(cur, h2[cur], dst), cur);
			}
		}
		else{
			return min(dfs(cur, prv - 1, dst), cur);
		}
	}
	else{
		if(prv == h1[cur]){
			if(l2[cur] <= h2[cur]){
				return min(dfs(cur, h2[cur], dst), cur);
			}
			else{
				return min(dfs(cur, l1[cur], dst), cur);
			}
		}
		else{
			return min(dfs(cur, prv + 1, dst), cur);
		}
	}
}

int main(){
	scanf("%d %d",&n,&m);
	lint ret = 0;
	for(int i=0; i<n; i++){
		scanf("%s", str[i]);
		int v = 0;
		for(int j=0; j<m; j++){
			if(str[i][j] == '1'){
				int e = j;
				while(e < m && str[i][e] == '1') e++;
				k++;
				for(int l=j; l<e; l++) col[i][l] = k;
				stp[k] = pi(i, j);
				edp[k] = pi(i, e-1);
				j = e;
				v++;
			}
		}
		ret += 1ll * v * (i + 1) * (n - i);
	}
	memset(l1, 0x3f, sizeof(l1));
	memset(l2, 0x3f, sizeof(l2));
	for(int i=1; i<=k; i++){
		for(int j=stp[i].second; j<=edp[i].second; j++){
			int px = stp[i].first;
			int py = j;
			if(px > 0 && str[px-1][py] == '1'){
				l1[i] = min(l1[i], col[px-1][py]);
				h1[i] = max(h1[i], col[px-1][py]);
			}
			if(px < n-1 && str[px+1][py] == '1'){
				l2[i] = min(l2[i], col[px+1][py]);
				h2[i] = max(h2[i], col[px+1][py]);
			}
		}
	}
	disj.init(k);
	for(int i=0; i<n; i++){
		int prv = -1;
		for(int j=0; j<m; j++){
			if(col[i][j] && prv != col[i][j]){
				prv = col[i][j];
				for(int k=l2[prv]; k<=h2[prv]; k++){
					if(disj.uni(prv, k)){
						ret -= 1ll * (n - 1 - i) * (i + 1);
					}
					else{
						int minv = min(k, dfs(k, prv, k));
						int minp = stp[minv].first + 1;
						ret -= 1ll * (n - 1 - i) * (i + 1 - minp);
					}
				}
			}
		}
	}
	cout << ret;
}
