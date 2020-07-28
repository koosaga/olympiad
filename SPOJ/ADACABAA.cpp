// Ivan Carvalho
// Solution to https://www.spoj.com/problems/ADACABAA/
#include <cstdio>
#include <algorithm>
#include <vector>
#define MP make_pair
#define PB push_back
#define LSOne(S) (S & (-S))
using namespace std;
typedef pair<int,int> ii;
typedef pair<int,ii> iii;
typedef pair<int,iii> iiii;
const int MAXN = 2*1e5 + 10;
vector<int> esq[MAXN],dir[MAXN],val[MAXN];
int segIt[MAXN],n;
void update_sparse(int id,int pos,int left,int right,int x,int delta){
	if(left == right){
		val[id][pos] = min(val[id][pos],delta);
		return;
	}
	int mid = (left+right)/2;
	if(x <= mid){
		if(esq[id][pos] == -1){
			esq[id].PB(-1);
			dir[id].PB(-1);
			val[id].PB(MAXN);
			esq[id][pos] = ++segIt[id];
		}
		update_sparse(id,esq[id][pos],left,mid,x,delta);
	}
	else{
		if(dir[id][pos] == -1){
			esq[id].PB(-1);
			dir[id].PB(-1);
			val[id].PB(MAXN);
			dir[id][pos] = ++segIt[id];
		}
		update_sparse(id,dir[id][pos],mid+1,right,x,delta);
	}
	int sinistra = (esq[id][pos] == -1) ? MAXN : val[id][esq[id][pos]];
	int destra = (dir[id][pos] == -1) ? MAXN : val[id][dir[id][pos]];
	val[id][pos] = min(sinistra,destra);
}
int query_sparse(int id,int pos,int left,int right,int i,int j){
	if(left > right || left > j || right < i) return MAXN;
	if(left >= i && right <= j){
		return val[id][pos];
	}
	int mid = (left + right)/2;
	int sinistra = (esq[id][pos] == -1 ) ? MAXN : query_sparse(id,esq[id][pos],left,mid,i,j);
	int destra = (dir[id][pos] == -1) ? MAXN : query_sparse(id,dir[id][pos],mid+1,right,i,j);
	return min(sinistra,destra);
}
void update_bit(int posx,int posy,int delta){
	while(posx <= n){
		update_sparse(posx,0,1,n,posy,delta);
		posx += LSOne(posx);
	}
}
int query_bit(int posx,int posy){
	int ans = MAXN;
	while(posx > 0){
		ans = min(ans,query_sparse(posx,0,1,n,1,posy));
		posx -= LSOne(posx);
	}
	return ans;
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		esq[i].PB(-1);
		dir[i].PB(-1);
		val[i].PB(MAXN);
	}
	vector<iiii> entrada;
	for(int i=1;i<=n;i++){
		int a,b,c,d;
		scanf("%d %d %d %d",&a,&b,&c,&d);
		entrada.push_back(MP(a,MP(b,MP(c,d))));
	}
	sort(entrada.begin(),entrada.end());
	int resp = 0;
	for(int i = 0;i < n;i++){
		int a = entrada[i].first, b = entrada[i].second.first, c = entrada[i].second.second.first, d = entrada[i].second.second.second;
		int maioral = query_bit(b,c);
		if(maioral > d){
			resp++;
			update_bit(b,c,d);
		}
	}
	printf("%d\n",resp);
	return 0;
}