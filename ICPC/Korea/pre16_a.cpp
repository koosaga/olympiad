#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;

int dep[2222222], n;
int mx[2222222];

int main(){
	scanf("%d",&n);
	for(int i=2; i<(2<<n); i++){
		scanf("%d",&dep[i]);
	}
	lint ret = 0;
	for(int i=(1<<n)-1; i; i--){
		mx[i] = max(mx[2*i] + dep[2*i], mx[2*i+1] + dep[2*i+1]);
		ret += 2 * mx[i] - mx[2*i] - mx[2*i+1];
	}
	printf("%lld\n", ret);
}
