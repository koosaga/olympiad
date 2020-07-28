// Ivan Carvalho
// Solution to https://www.spoj.com/problems/ADARAIN/
#include <cstdio>
#define LSOne(S) (S & -S)
const int MAXN = 1e6 + 10;
int n,m,l,bit[MAXN];
inline void updateplus(int idx){
	while(idx < MAXN){
		bit[idx]++;
		idx += LSOne(idx);
	}
}
inline void updateless(int idx){
	while(idx < MAXN){
		bit[idx]--;
		idx += LSOne(idx);
	}
}
inline int query(int idx){
	int ans = 0;
	while(idx > 0){
		ans += bit[idx];
		idx -= LSOne(idx);
	}
	return ans;
}
int main(){
	scanf("%d %d %d",&n,&m,&l);
	while(n--){
		int a,b;
		scanf("%d %d",&a,&b);
		a++;
		b++;
		updateplus(a);
		updateless(b+1);
	}
	while(m--){
		int a;
		scanf("%d",&a);
		a++;
		printf("%d\n",query(a));
	}
	return 0;
}