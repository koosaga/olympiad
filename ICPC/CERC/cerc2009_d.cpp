#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1005;

struct disj{
	int pa[4 * MAXN *MAXN];
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

int n, m;
char str[MAXN][MAXN];
bool chk[4 * MAXN * MAXN];

int get(int x, int y, int z){
	return (x * m + y) * 4 + z;
}

int solve(){
	disj.init(4*n*m);
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			if(str[i][j] == 'B'){
				chk[get(i, j, 2)] = chk[get(i, j, 3)] = 1;
				disj.uni(get(i, j, 2), get(i, j, 3));
			}
			if(str[i][j] == 'C'){
				chk[get(i, j, 0)] = chk[get(i, j, 3)] = 1;
				disj.uni(get(i, j, 0), get(i, j, 3));
			}
			if(str[i][j] == 'D'){
				chk[get(i, j, 0)] = chk[get(i, j, 1)] = 1;
				disj.uni(get(i, j, 0), get(i, j, 1));
			}
			if(str[i][j] == 'E'){
				chk[get(i, j, 1)] = chk[get(i, j, 2)] = 1;
				disj.uni(get(i, j, 2), get(i, j, 1));
			}
			if(str[i][j] == 'F'){
				for(int k=0; k<4; k++){
					chk[get(i, j, k)] = 1;
					disj.uni(get(i, j, k), get(i, j, (k+1)%4));
				}
			}
		}
	}
	for(int i=0; i<n; i++){
		for(int j=0; j<m-1; j++){
			if(chk[get(i, j, 1)] && chk[get(i, j+1, 3)]){
				disj.uni(get(i, j, 1), get(i, j+1, 3));
			}
		}
	}
	for(int i=0; i<n-1; i++){
		for(int j=0; j<m; j++){
			if(chk[get(i, j, 2)] && chk[get(i+1, j, 0)]){
				disj.uni(get(i, j, 2), get(i+1, j, 0));
			}
		}
	}
	int ans = 0;
	for(int i=0; i<4*n*m; i++){
		if(chk[i] && disj.find(i) == i) ans++;
	}
	return ans;
}

int main(){
	int tc;
	scanf("%d",&tc);
	while(tc--){
		scanf("%d %d",&n,&m);
		for(int i=0; i<n; i++)scanf("%s", str[i]);
		printf("%d\n", solve());
		fill(chk, chk + n * m * 4, 0);
	}
}