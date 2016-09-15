#include <bits/stdc++.h>
using namespace std;
typedef long long lint;

int n, x;

int main(){
	scanf("%d",&n);
	lint ret = 0;
	priority_queue<int> pq;
	for(int i=0; i<n; i++){
		scanf("%d",&x); x -= i;
		if(!pq.empty() && pq.top() > x){
			ret += pq.top() - x;
			pq.pop();
			pq.push(x);
		}
		pq.push(x);
	}
	printf("%lld\n", ret);
}