#include<bits/stdc++.h>
using namespace std;
 
const int N = 200005, G = 20;
 
int n, m, s, par[G][N], dep[N];
 
vector<int> adj[N];
 
void dfs (int I) {
	for(auto &T : adj[I]) {
		if (par[0][T]) continue;
		par[0][T] = I;
		dep[T] = dep[I] + 1;
		dfs(T);
	}
}
 
int lca (int A, int B) {
	if(dep[A] < dep[B]) swap(A, B);
	for(int i=G;i--;) {
		if(dep[A] - dep[B] >= (1<<i)) A = par[i][A];
	}
	if(A == B) return A;
	for(int i=G;i--;) {
		if(par[i][A] != par[i][B]) {
			A = par[i][A];
			B = par[i][B];
		}
	}
	return par[0][A];
}
 
vector<int> uppath(int I) {
	vector<int> R;
	while(true) {
		R.push_back(I);
		if(I == s) break;
		I = par[0][I];
	}
	return R;
}
 
int main()
{
	scanf("%d%d%d",&n,&m,&s);
	for(int i=1;i<=m;i++) {
		int A, B;
		scanf("%d%d",&A,&B);
		adj[A].push_back(B);
	}
	par[0][s] = -1;
	dfs(s);
	for(int k=1;k<G;k++) {
		for (int i = 1; i <= n; i++) {
			par[k][i] = par[k - 1][par[k - 1][i]];
		}
	}
	for(int i=1;i<=n;i++) {
		for(auto &j : adj[i]) {
			if(j != s && par[0][j] != i && lca(i, j) == s) {
				vector<int> A = uppath(i), B = uppath(j);
				reverse(A.begin(), A.end());
				reverse(B.begin(), B.end());
				A.push_back(j);
				puts("Possible");
				printf("%d\n", (int)A.size());
				for(auto &T : A) printf("%d ", T);
				puts("");
				printf("%d\n", (int)B.size());
				for(auto &T : B) printf("%d ", T);
				puts("");
				return 0;
			}
		}
	}
	puts("Impossible");
}
