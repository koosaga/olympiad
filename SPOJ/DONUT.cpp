// Ivan Carvalho
// Solution to https://www.spoj.com/problems/DONUT/
#include <bits/stdc++.h>
using namespace std;
const long long MAXN = 2*1e9 + 1;
typedef pair<long long,long long> ii;
vector<ii> entrada;
vector<long long> raiz,esq,dir,val,compx;
long long N,Q,segPtr;
void update(long long novo,long long velho,long long left,long long right,long long x,long long delta){
	val[novo] = val[velho] + delta;
	if(left == right) return;
	long long temp = (1LL*left + 1LL*right)/2LL;
	long long meio = temp;
	if(x <= meio){
		esq[novo] = ++segPtr;
		dir[novo] = dir[velho];
		esq.push_back(0);dir.push_back(0);val.push_back(0);
		update(esq[novo],esq[velho],left,meio,x,delta);
	}
	else{
		esq[novo] = esq[velho];
		dir[novo] = ++segPtr;
		esq.push_back(0);dir.push_back(0);val.push_back(0);
		update(dir[novo],dir[velho],meio+1,right,x,delta);
	}
}
long long query(long long pos,long long left,long long right,long long i,long long j){
	if(left >= i && right <= j) return val[pos];
	long long temp = (1LL*left + 1LL*right)/2LL;
	long long meio = temp;
	if(j <= meio) return query(esq[pos],left,meio,i,j);
	else if(i >= meio + 1) return query(dir[pos],meio+1,right,i,j);
	return query(esq[pos],left,meio,i,j) + query(dir[pos],meio+1,right,i,j);
}
int main(){
	long long primeirao = 1;
	while(scanf("%lld",&N) && N > 0){
		if(primeirao) primeirao = 0;
		else printf("\n");
		entrada.clear();raiz.clear();esq.clear();dir.clear();val.clear();compx.clear();
		raiz.push_back(0);esq.push_back(0);dir.push_back(0);val.push_back(0);
		segPtr = 0;
		for(long long i = 1;i<=N;i++){
			long long x,y;
			scanf("%lld %lld",&x,&y);
			long long dx = y - x;
			long long dy = x + y;
			entrada.push_back(ii(dx,dy));
		}
		sort(entrada.begin(),entrada.end());
		for(long long i = 0;i<entrada.size();i++){
			long long x = entrada[i].first, y = entrada[i].second;
			compx.push_back(x);
			raiz.push_back(++segPtr);esq.push_back(0);dir.push_back(0);val.push_back(0);
			update(segPtr,raiz[raiz.size()-2],1,MAXN,y,1);
		}
		scanf("%lld",&Q);
		while(Q--){
			long long xx,yy;
			scanf("%lld %lld",&xx,&yy);
			long long x = yy - xx, y = xx + yy;
			long long ini = 0, fim = MAXN, meio, resp = -1;
			while(ini <= fim){
				long long temp = (1LL*ini + 1LL*fim)/2LL;
				long long meio = temp;
				long long lo = lower_bound(compx.begin(),compx.end(),x - meio) - compx.begin() + 1;
				long long hi = prev(upper_bound(compx.begin(),compx.end(),x + meio)) - compx.begin() + 1;
				long long y_l = max(1LL*y - temp,1LL);
				long long y_h = min(1LL*y + temp,1LL*MAXN);
				if(query(raiz[hi],1,MAXN,y_l,y_h) - query(raiz[lo-1],1,MAXN,y_l,y_h) >= 1){
					resp = meio;
					fim = meio - 1;
				}
				else{
					ini = meio + 1;
				}
			}
			printf("%lld\n",resp);
		}
	}
	return 0;
} 