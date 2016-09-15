#include <bits/stdc++.h>
using namespace std;

int n, a[2005];

int main(){
	scanf("%d",&n);
	for(int i=0; i<n; i++) scanf("%d",&a[i]);
	int dap = 2e9;
	for(int i=0; i<2; i++){
		int ret = 0;
		priority_queue<int> pq;
		for(int j=0; j<n; j++){
			if(!pq.empty() && pq.top() > a[j]){
				ret += pq.top() - a[j];
				pq.pop();
				pq.push(a[j]);
			}
			pq.push(a[j]);
		}
		dap = min(dap, ret);
		reverse(a, a+n);
	}
	printf("%d\n", dap);
}
