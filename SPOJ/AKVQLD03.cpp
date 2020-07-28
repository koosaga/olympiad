// Ivan Carvalho
// Solution to https://www.spoj.com/problems/AKVQLD03/
#include <cstdio>
#define MAXN 1000010
#define LSOne(S) (S & (-S))
typedef long long ll;
ll bit[MAXN];
int n,q;
void update(int pos,ll val){
	while(pos <= n){
		bit[pos] += val;
		pos += LSOne(pos);
	}
}
ll query(int pos){
	ll answer = 0;
	while(pos > 0){
		answer += bit[pos];
		pos -= LSOne(pos);
	}
	return answer;
}
int main(){
	scanf("%d %d",&n,&q);
	while(q--){
		char entrada[10];
		scanf("%s",entrada);
		if (entrada[0] == 'f'){
			int a,b;
			scanf("%d %d",&a,&b);
			printf("%lld\n",query(b) - query(a-1));
		}
		if (entrada[0] == 'a'){
			int idx,val;
			scanf("%d %d",&idx,&val);
			update(idx,ll(val));
		}
	}
	return 0;
}