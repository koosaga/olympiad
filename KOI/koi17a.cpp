#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<lint, int> pi;
const int mod = 1e9 + 7;
const int MAXN = 1505;

struct node{
	int x, y, d;
};

set<pi> vis;
queue<node> que;

void enqueue(int x, int y, int d){
	if(vis.find(pi(x, y)) != vis.end()) return;
	vis.insert(pi(x, y));
	que.push({x, y, d});
}

int main(){
	int n, m, a, b;
	scanf("%d %d %d %d",&n,&m,&a,&b);
	if(1 <= a && a < n && 1 <= b && b < m){
		puts("-1");
		return 0;
	}
	enqueue(0, 0, 0);
	while(!que.empty()){
		auto x = que.front();
		que.pop();
		if(pi(x.x, x.y) == pi(a, b)){
			cout << x.d;
			return 0;
		}
		enqueue(x.x, 0, x.d + 1);
		enqueue(x.x, m, x.d + 1);
		enqueue(0, x.y, x.d + 1);
		enqueue(n, x.y, x.d + 1);
		int delta = min(x.x, m - x.y);
		enqueue(x.x - delta, x.y + delta, x.d + 1);
		delta = min(x.y, n - x.x);
		enqueue(x.x + delta, x.y - delta, x.d + 1);
	}
	cout << -1;
}
