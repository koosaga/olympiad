#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;

priority_queue<pi> pq1;
priority_queue<pi, vector<pi>, greater<pi> > pq2;
bool vis[1000005];

int main(){
	int n;
	scanf("%d",&n);
	lint ret = 0;
	int idx = 0;
	for(int i=0; i<n; i++){
		int t;
		scanf("%d",&t);
		while(t--){
			int p;
			scanf("%d",&p);
			pq1.push(pi(p, ++idx));
			pq2.push(pi(p, idx));
		}
		while(vis[pq1.top().second]) pq1.pop();
		vis[pq1.top().second] = 1;
		ret += pq1.top().first;
		pq1.pop();
		while(vis[pq2.top().second]) pq2.pop();
		vis[pq2.top().second] = 1;
		ret -= pq2.top().first;
	}
	cout << ret;
}
