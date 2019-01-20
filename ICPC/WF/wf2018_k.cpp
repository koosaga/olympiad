#include <bits/stdc++.h>
using namespace std;
const int MAXN = 10005;
using pi = pair<int, int>;

int n, m;
int deg[MAXN];
int dp[2][2 * MAXN];
short tr[MAXN][2 * MAXN];

int main(){
	scanf("%d %d",&n,&m);
	for(int i=0; i<m; i++){
		int x, y; scanf("%d %d",&x,&y);
		deg[x]++;
		deg[y]++;
	}
	memset(dp, 0x3f, sizeof(dp));
	dp[0][0] = 0;
	for(int i=1; i<=n; i++){
		pi minv(1e9, -1);
        dp[i%2][0] = 1e9;
		for(int j=1; j<=2*n-2; j++){
			minv = min(minv, pi(dp[(i-1)%2][j-1], j-1));
			dp[i%2][j] = minv.first + 1;
			tr[i][j] = minv.second;
			if(j >= deg[i-1]){
				if(dp[i%2][j] > dp[(i-1)%2][j - deg[i-1]]){
					dp[i%2][j] = dp[(i-1)%2][j - deg[i-1]];
					tr[i][j] = j - deg[i-1];
				}
			}
		}
	}
	cout << dp[n%2][2*n-2] << endl;
	printf("%d %d\n", n, n - 1);
	int ed = 2 * n - 2;
	for(int i=n; i; i--){
		int prv = tr[i][ed];
		deg[i - 1] = ed - prv;
		ed = prv;
	}
	queue<int> que;
	priority_queue<pi> pq;
	for(int i=0; i<n; i++){
		if(deg[i] == 1){
			que.push(i);
		}
		else pq.push(pi(deg[i], i));
	}
	while(!pq.empty()){
		int x = que.front();
		que.pop();
		auto y = pq.top();
		pq.pop();
		printf("%d %d\n", x, y.second);
		deg[y.second]--;
		if(deg[y.second] > 1) pq.push(pi(deg[y.second], y.second));
		else que.push(y.second);
	}
	printf("%d ", que.front());
	que.pop();
	printf("%d\n", que.front());
	que.pop();
}
