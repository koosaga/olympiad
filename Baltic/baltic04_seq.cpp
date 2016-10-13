#include <bits/stdc++.h>
using namespace std;
typedef long long lint;

int n, x;
int opt[1000005];

int main(){
	scanf("%d",&n);
	priority_queue<int> pq;
	for(int i=0; i<n; i++){
		scanf("%d",&x); x -= i;
		if(!pq.empty() && pq.top() > x){
			pq.pop();
			pq.push(x);
		}
		pq.push(x);
		opt[i] = pq.top();
	}
	for(int i=n-2; i>=0; i--){
		opt[i] = min(opt[i], opt[i+1]);
	}
	for(int i=0; i<n; i++){
		printf("%d\n", opt[i] + i);
	}
}
