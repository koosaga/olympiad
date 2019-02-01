#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;

struct tra{
	int st, ed, t;
	bool operator<(const tra &c)const{
		return make_tuple(st, t, ed) < make_tuple(c.st, c.t, c.ed);
	}
}a[200005];
int n, q;
int nxt[18][200005];

int main(){
	scanf("%d %d",&n,&q);
	for(int i=0; i<n; i++){
		scanf("%d %d %d",&a[i].st,&a[i].ed,&a[i].t);
	}
	sort(a, a+n);
	a[n].t = 1e9;
	for(int i=0; i<n; i++){
		int pos = lower_bound(a, a+n, (tra){a[i].ed, -1, a[i].t + 1}) - a;
		if(a[pos].st == a[i].ed) nxt[0][i] = pos;
		else nxt[0][i] = n;
	}
	nxt[0][n] = n;
	for(int i=1; i<18; i++){
		for(int j=0; j<=n; j++){
			nxt[i][j] = nxt[i-1][nxt[i-1][j]];
		}
	}
	while(q--){
		int s, e, c;
		scanf("%d %d %d",&c,&s,&e);
		int pos = lower_bound(a, a+n, (tra){c, -1, s}) - a;
		if(a[pos].st != c || a[pos].t >= e){
			printf("%d\n", c);
			continue;
		}
		for(int i=17; i>=0; i--){
			if(a[nxt[i][pos]].t < e) pos = nxt[i][pos];
		}
		printf("%d\n", a[pos].ed);
	}
}
