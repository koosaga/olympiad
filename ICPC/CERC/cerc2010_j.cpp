#include<bits/stdc++.h>
#define sz(v) ((int)(v).size())
using namespace std;
const int MAXN = 600005;
const int mod = 1e9 + 7;
using lint = long long;
using pi = pair<int, int>;

int m, adj[100][100];

void Do(int x){
	if(x == 1){
		adj[m][m] = 1;
		m++;
		return;
	}
	if(x & 1){
		Do(x - 1);
		adj[m-1][m] = 1;
		adj[m][m] = 1;
		adj[m][0] = 1;
		m++;
		return;
	}
	else{
		Do(x / 2);
		adj[m - 1][m] = 1;
		adj[m][m] = adj[m][m+1] = adj[m+1][m] = adj[m+1][m+1] = 1;
		m += 2;
		return;
	}
}

int main(){
	int tc; scanf("%d",&tc);
	while(tc--){
		int n; cin >> n;
		m = 0;
		memset(adj, 0, sizeof(adj));
		Do(n);
		cout << m << endl;
		for(int i=0; i<m; i++){
			for(int j=0; j<m; j++){
				printf("%d", adj[i][j]);
			}
			puts("");
		}
	}
}
