#include <bits/stdc++.h>
using namespace std;
using lint = long long;
const int mod = 1e9 + 7;
const int MAXN = 1100005;

int n, p[MAXN], q[MAXN];

void add(int x){ 
	if(p[x]){
		p[x] = 0;
		add(x + 1);
		if(x >= 2) add(max(x - 2, 1));
		return;
	}
	if(p[x + 1]){
		p[x + 1] = 0;
		add(x + 2);
	}
	else if(p[x - 1]){
		p[x - 1] = 0;
		add(x + 1);
	}
	else p[x] = 1;
}

int main(){
	scanf("%d",&n);
	for(int i=1; i<=n; i++){
		scanf("%d",&p[i]);
	}
	int m; scanf("%d",&m);
	for(int i=1; i<=m; i++){
		scanf("%d",&q[i]);
	}
	for(int i=m; i; i--){
		if(q[i]) add(i);
	}
	for(int i=MAXN-1; i; i--){
		if(p[i]){
			n = i;
			break;
		}
	}
	printf("%d ", n);
	for(int i=1; i<=n; i++) printf("%d ", p[i]);
}
