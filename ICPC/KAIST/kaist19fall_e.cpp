#include <bits/stdc++.h>
using namespace std;
const int MAXN = 600;
using pi = pair<int, int>;

int n;
char str[MAXN][MAXN];
int vis[MAXN];

void solve(){
	int k = 1;
	while((1 << k) <= n) k++;
	vector<int> v;
	while(k--){
		pi ret(-1, -1);
		for(int j=0; j<n; j++){
			if(vis[j]) continue;
			int curCnt = 0;
			for(int k=0; k<n; k++){
				if(!vis[k] && str[j][k] == 'W'){
					curCnt++;
				}
			}
			ret = max(ret, pi(curCnt, j));
		}
		assert(ret.second != -1);
		for(int j=0; j<n; j++){
			if(!vis[j] && str[ret.second][j] != 'W'){
				vis[j] = 1;
			}
		}
		printf("%d ", ret.second + 1);
	}
	puts("");
}

int main(){
	int t; scanf("%d",&t); 
	for(int i=0; i<t; i++){
		scanf("%d",&n); 
		for(int j=0; j<n; j++){
			scanf("%s", str[j]);
			vis[j] = 0;
		}
		solve();
	}
}

