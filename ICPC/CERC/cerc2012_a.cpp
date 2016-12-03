#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;

int n;
bool vis[1<<20];
int adj[20][20];
int get_bit[1<<20];

void dfs(int x){
	if(vis[x]) return;
	vis[x] = 1;
	for(int i=x; i; i-=i&-i){
		int ret = 0;
		for(int j=x; j; j-=j&-j){
			ret += adj[get_bit[j&-j]][get_bit[i&-i]];
		}
		if(ret < 0){
			dfs(x ^ (i&-i));
		}
	}
}

int main(){
	int t;
	cin >> t;
	for(int i=0; i<20; i++){
		get_bit[1<<i] = i;
	}
	while(t--){
		cin >> n;
		for(int i=0; i<n; i++){
			for(int j=0; j<n; j++){
				cin >> adj[i][j];
			}
		}
		for(int i=0; i<(1<<n); i++){
			vis[i] = 0;
		}
		dfs((1<<n) - 1);
		int cnt = 0;
		for(int i=0; i<n; i++){
			if(vis[1<<i]){
				printf("%d ",i + 1);
				cnt++;
			}
		}
		if(!cnt) puts("0");
		else puts("");
	}
}
