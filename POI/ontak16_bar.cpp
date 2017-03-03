#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;

int n, a[1000005];
char str[1000005];

int main(){
	scanf("%d",&n);
	for(int i=1; i<=n; i++) scanf("%d",&a[i]);
	scanf("%s", str);
	priority_queue<pi, vector<pi>, greater<pi> > pq;
	int p = 0, b = 0, f = 0;
	for(int i=1; i<=n; i++){
		if(i + f <= n) pq.push(pi(a[i + f], i + f));
		while(i + b < pq.top().first){
			if(str[p] == 'B') b++;
			else{
				f++;
				if(i + f <= n) pq.push(pi(a[i + f], i + f));
			}
			p++;
		}
		pq.pop();
	}
	cout << p;
}
