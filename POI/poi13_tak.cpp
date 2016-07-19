#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<lint, lint> pi;
 
lint p, q, n, a[500005];
 
int main(){
	scanf("%lld %lld %lld",&p,&q,&n);
	for(int i=0; i<n; i++) scanf("%lld",&a[i]);
	sort(a, a+n);
	reverse(a, a+n);
	int pos = -1;
	for(int i=0; i<n; i++){
		if(a[i] >= p - q) pos = i;
	}
	if(pos == -1){
		puts("0");
		return 0;
	}
	lint curp = 0;
	for(int i=0; i<pos; i++){
		lint go = abs(q - curp);
		curp += max(a[i] - go, 0ll);
		if(curp >= p){
			printf("%d\n", i + 1);
			return 0;
		}
	}
	if(curp + max(a[pos] - abs(q - curp), 0ll) >= p){
		printf("%d\n", pos + 1);
		return 0;
	}
	for(int i=pos+1; i<n; i++){
		lint go = abs(q - curp);
		curp += max(a[i] - go, 0ll);
		if(curp + max(a[pos] - abs(q - curp), 0ll) >= p){
			printf("%d\n", i + 1);
			return 0;
		}
	}
	puts("0");
}