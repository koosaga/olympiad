#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> pi;
const int MAXN = 1000005;

int n, p, q;
int minc[MAXN];

int main(){
	scanf("%d %d",&p,&q);
	memset(minc, 0x3f, sizeof(minc));
	while(q--){
		int dis, val;
		scanf("%d %d",&val,&dis);
		minc[n] = val;
		n += dis;
	}
	priority_queue<pi, vector<pi>, greater<pi> > pq;
	int ans = 0;
	for(int i=1; i<=n; i++){
		pq.push(pi(minc[i - 1], i - 1));
		while(!pq.empty() && pq.top().second < i - p) pq.pop();
		ans += pq.top().first;
	}
	cout << ans << endl;
}

