// Ivan Carvalho
// Solution to https://www.spoj.com/problems/ADASEA/
#include <cstdio>
#include <algorithm>
#define MAXN 1001
using namespace std;
typedef long long ll;
int dx[4] = {1,-1,0,0};
int dy[4] = {0,0,1,-1};
int pai[MAXN*MAXN],id[MAXN][MAXN],qtd[MAXN*MAXN],n,m,cont;
char entrada[MAXN][MAXN];
ll p,q,common;
inline int valido(int x,int y){
	return x >= 0 && x < n && y >= 0 && y < m && entrada[x][y] == '#';
}
ll gcd(ll x,ll y){
	if(x < y) swap(x,y);
	if(y == 0) return x;
	return gcd(y,x%y);
}
int find(int x){
	if(x == pai[x]) return x;
	return pai[x] = find(pai[x]);
}
void join(int x,int y){
	x = find(x);
	y = find(y);
	if(x == y) return;
	if(qtd[x] > qtd[y]){
		pai[y] = x;
		qtd[x] += qtd[y];
	}
	else{
		pai[x] = y;
		qtd[y] += qtd[x];
	}
}
int main(){
	int TC;
	scanf("%d",&TC);
	while(TC--){
		p = q = common = 0;
		cont = 0;
		scanf("%d %d",&n,&m);
		for(int i=0;i<n;i++){
			scanf("%s",entrada[i]);
			for(int j = 0;j < m;j++){
				id[i][j] = ++cont;
				pai[cont] = cont;
				qtd[cont] = (entrada[i][j] == '#');
			}
		}
		for(int i=0;i<n;i++){
			for(int j=0;j<m;j++){
				if(entrada[i][j] != '#') continue;
				for(int k=0;k<4;k++){
					int ni = i + dx[k];
					int nj = j + dy[k];
					if(valido(ni,nj)){
						join(id[i][j],id[ni][nj]);
					}
				}
			}
		}
		for(int i=0;i<n;i++){
			for(int j=0;j<m;j++){
				q++;
				p += (ll)qtd[find(id[i][j])];
			}
		}
		common = gcd(p,q);
		//printf("%lld %lld %lld\n",p,q,common);
		p /= common;
		q /= common;
		if(q == 1) printf("%lld\n",p);
		else printf("%lld / %lld\n",p,q);
	}
	return 0;
}