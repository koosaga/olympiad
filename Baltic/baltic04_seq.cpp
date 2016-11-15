#include <bits/stdc++.h>
using namespace std;
typedef long long lint;

int n, x;
int opt[1000005];

int main(){
	scanf("%d",&n);
	priority_queue<int> pq;
	lint ret = 0;
	for(int i=0; i<n; i++){
		scanf("%d",&x); x -= i;
		if(!pq.empty() && pq.top() > x){
			pq.pop();
			pq.push(x);
		}
		pq.push(x);
		ret += abs(x - pq.top());
	}
	printf("%lld\n", ret);
}