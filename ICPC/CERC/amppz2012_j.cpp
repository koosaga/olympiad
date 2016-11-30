#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;

bool cmp(pi a, pi b){
	return a.second > b.second;
}

int n;
pi a[1000005];

int main(){
	scanf("%d",&n);
	for(int i=0; i<n; i++) scanf("%d %d",&a[i].first, &a[i].second);
	sort(a, a+n, cmp);
	int dap = a[0].second - a[0].first;
	for(int i=1; i<n; i++){
		dap = min(dap, a[i].second) - a[i].first;
	}
	printf("%d\n", dap);
}