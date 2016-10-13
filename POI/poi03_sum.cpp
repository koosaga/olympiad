#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;

int n, a[50005];
int vis[50005];
int dist[50005];

int main(){
	cin >> n;
	for(int i=0; i<n; i++){
		scanf("%d",&a[i]);
		if(i){
			if(vis[a[i] % a[0]]){
				i--;
				n--;
				continue;
			}
			vis[a[i] % a[0]] = 1;
		}
	}
	priority_queue<pi, vector<pi>, greater<pi> > pq;
	pq.push(pi(0, 0));
	memset(dist, 0x3f, sizeof(dist));
	dist[0] = 0;
	while(!pq.empty()){
		auto x = pq.top();
		pq.pop();
		if(dist[x.second] != x.first) continue;
		for(int i=1; i<n; i++){
			int nxt = (x.second + a[i]) % a[0];
			if(dist[nxt] > dist[x.second] + a[i]){
				dist[nxt] = dist[x.second] + a[i];
				pq.push(pi(dist[nxt], nxt));
			}
		}
	}
	int q;
	cin>> q;
	for(int i=0; i<q; i++){
		int b;
		scanf("%d",&b);
		if(dist[b % a[0]] <= b) puts("TAK");
		else puts("NIE");
	}
}

