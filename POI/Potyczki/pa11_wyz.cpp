#include <bits/stdc++.h>
using namespace std;
const int MAXN = 2000005;
using pi = pair<int, int>;

int n, m;
int deg[MAXN];

int main(){
	scanf("%d",&n);
	for(int i=1; i<=n; i++) scanf("%d",&deg[i]);
	if(accumulate(deg + 1, deg + n + 1, 0ll) != 2 * n - 2){
		puts("BRAK");
		return 0;
	}

	queue<int> que;
	priority_queue<pi> pq;
	for(int i=1; i<=n; i++){
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

