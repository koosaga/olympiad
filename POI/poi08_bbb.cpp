#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
const int MAXN = 1000005;

int s, e, x, y; // make it look sexy
int n, a[2 * MAXN];
char str[MAXN];

int main(){
	scanf("%d %d %d %d %d",&n,&s,&e,&x,&y);
	scanf("%s", str + 1);
	for(int i=1; i<=n; i++){
		if(str[i] == '+') a[i] = a[i+n] = 1;
		else a[i] = a[i+n] = -1;
	}
	for(int i=1; i<=2*n; i++) a[i] += a[i-1];
	priority_queue<pi, vector<pi>, greater<pi> > que;
	for(int i=0; i<n; i++) que.push(pi(a[i], i));
	int ans = 2e9;
	for(int i=1; i<=n; i++){
		que.push(pi(a[i+n-1], i+n-1));
		while(!que.empty() && que.top().second < i - 1) que.pop();
		int minval = que.top().first - a[i-1] + s;
		int up = (max(-minval, 0) + 1) / 2;
		int result = s + a[i+n-1] - a[i-1] + up * 2;
		ans = min(ans, (abs(result - e) / 2 + up) * x + ((n + 1 - i) % n) * y);
	}
	cout << ans << endl;
}



