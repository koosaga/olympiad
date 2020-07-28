// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1135
#include <cstdio>
#include <vector>
#include <algorithm>
#define gc getchar_unlocked
void getint(int &x){
    register int c = gc();
    x = 0;
    for(;(c<48 || c>57);c = gc());
    for(;c>47 && c<58;c = gc()) {x = (x<<1) + (x<<3) + c - 48;}
}
using namespace std;
#define MAXN 100001
#define LIMIT 1000000001
int n,q,nivel[MAXN],pai[MAXN];
long long int raiz[MAXN];
int LCA(int u, int v){
	while(u!=v){
		if (nivel[u]>nivel[v]) u = pai[u];
		else v = pai[v];
	}
	return u;
}
int main(){
	while(1){
		getint(n);
		if (n == 0) break;
		raiz[0]=0LL;
		nivel[0]=0;
		pai[0]=0;
		for(int i=1;i<n;i++){
			int a,b;
			getint(a);
			getint(b);
			pai[i]=a;
			nivel[i]= nivel[a]+1;
			raiz[i]= raiz[a]+b;
		}
		getint(q);
		bool verdade = false;
		while(q--){
			if (verdade) printf(" ");
			int x,y;
			getint(x);
			getint(y);
			printf("%lld",raiz[x]+raiz[y]-2*raiz[LCA(x,y)]);
			verdade=true;
		}
		printf("\n");
	}
	return 0;
}
