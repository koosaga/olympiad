#include <cstdio>
#include <algorithm>
using namespace std;

struct edg{int s,e,x;}a[10005];

struct disj{
	int pa[1005];
	void init(int n){
		for(int i=0; i<=n; i++) pa[i] = i;
	}
	int find(int x){
		return pa[x] = (pa[x] == x ? x : find(pa[x]));
	}
	bool uni(int p, int q){
		p = find(p), q = find(q);
		if(p == q) return 0;
		pa[q] = p;
		return 1;
	}
}disj;

int main(){
	while(1){
		int n, m;
		scanf("%d %d",&n,&m);
		if(n == 0) break;
		disj.init(n);
		for(int i=0; i<m; i++){
			scanf("%d %d %d",&a[i].s,&a[i].e,&a[i].x);
		}
		int cnt = 0;
		sort(a,a+m,[&](const edg &a, const edg &b){return a.x < b.x;});
		for(int i=0; i<m; i++){
			if(disj.uni(a[i].s, a[i].e)){
				cnt++;
				if(cnt == n/2){
					printf("%d\n",a[i].x);
					break;
				}
			}
		}
	}
}