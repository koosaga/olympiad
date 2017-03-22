#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;

int n, m;
char a[500005], b[500005];

int l1[500005], l2[500005];

bool trial(int n){
	int p = 0;
	for(int i=0; i<m; i++){
		while(p < n && a[p] != b[i]) p++;
		p = min(p, n);
		l1[i] = p;
		p++;
	}
	p = n-1;
	for(int i=m-1; i>=0; i--){
		while(p >= 0 && a[p] != b[i]) p--;
		p = max(p, -1);
		l2[i] = p;
		p--;
	}
	for(int i=0; i<m; i++){
		int st = (i > 0 ? l1[i-1] : -1);
		int ed = (i < m-1 ? l2[i+1] : n);
		if(st >= ed) return 0;
	}
	return 1;
}

int main(){
	scanf("%d %d %s %s",&n,&m,a,b);
	if(m == 1){
		puts("0");
		return 0;
	}
	int s = 0, e = n;
	while(s != e){
		int m = (s+e)/2;
		if(trial(m)) e = m;
		else s = m+1;
	}
	if(!trial(s)) puts("-1");
	else printf("%d", s);
}
