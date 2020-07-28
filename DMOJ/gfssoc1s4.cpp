// Ivan Carvalho
// Solution to https://dmoj.ca/problem/gfssoc1s4
#include <cstdio>
#define MAXN 251
#define LSOne(S) (S & (-S))
typedef long long ll;
int n,q;
ll bit[MAXN][MAXN][MAXN],vetor[MAXN][MAXN][MAXN],resp;
inline void update(int posx,int posy,int posz,ll val){
	for(int  i = posx;i <= n;i += LSOne(i)){
		for(int j = posy;j <= n;j += LSOne(j)){
			for(int k = posz;k <= n;k += LSOne(k)){
				bit[i][j][k] += val;
			}
		}
	}
}
inline ll read_z(int posx,int posy,int posz){
	ll ans = 0;
	while(posz > 0){
		ans += bit[posx][posy][posz];
		posz -= LSOne(posz);
	}
	return ans;
}
inline ll query_z(int posx,int posy,int posz1,int posz2){
	return read_z(posx,posy,posz2) - read_z(posx,posy,posz1 - 1);
}
inline ll read_y(int posx,int posy,int posz1,int posz2){
	ll ans = 0;	
	while(posy > 0){
		ans += query_z(posx,posy,posz1,posz2);
		posy -= LSOne(posy);
	}
	return ans;
}
inline ll query_y(int posx,int posy1,int posy2,int posz1,int posz2){
	return read_y(posx,posy2,posz1,posz2) - read_y(posx,posy1 - 1,posz1,posz2);
}
inline ll read_x(int posx,int posy1,int posy2,int posz1,int posz2){
	ll ans = 0;
	while(posx > 0){
		ans += query_y(posx,posy1,posy2,posz1,posz2);
		posx -= LSOne(posx);
	}
	return ans;
}
inline ll query_x(int posx1,int posx2,int posy1,int posy2,int posz1,int posz2){
	return read_x(posx2,posy1,posy2,posz1,posz2) - read_x(posx1 - 1,posy1,posy2,posz1,posz2);
}
int main(){
	scanf("%d %d",&n,&q);
	while(q--){
		char op;
		scanf(" %c",&op);
		if(op == 'C'){
			int a,b,c;
			ll d;
			scanf("%d %d %d %lld",&a,&b,&c,&d);
			update(a,b,c,-vetor[a][b][c]);
			vetor[a][b][c] = d;
			update(a,b,c,vetor[a][b][c]);
		}
		else{
			int a,b,c,d,e,f;
			scanf("%d %d %d %d %d %d",&a,&b,&c,&d,&e,&f);
			resp += query_x(a,d,b,e,c,f);
		}
	}
	printf("%lld\n",resp);
	return 0;
}
}