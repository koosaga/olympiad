// Ivan Carvalho
// Solution to https://www.spoj.com/problems/POSTERS/
#include <cstdio>
#include <cstring>
#include <set>
#include <map>
#include <algorithm>
#define MAXN 40010
using namespace std;
int n,N,arvore[8*MAXN],lazy[8*MAXN],A[MAXN],B[MAXN];
set<int> conjunto;
map<int,int> compressao;
void update(int pos,int left,int right,int i,int j,int val){
	if(lazy[pos] != 0){
		arvore[pos] = lazy[pos];
		if(left != right){
			lazy[2*pos] = lazy[pos];
			lazy[2*pos+1] = lazy[pos];
		}
		lazy[pos] = 0;
	}
	if(left > right || left > j || right < i) return;
	if(left >= i && right <= j){
		arvore[pos] = val;
		if(left != right){
			lazy[2*pos] = val;
			lazy[2*pos+1] = val;
		}
		return;
	}
	int mid = (left+right)/2;
	update(2*pos,left,mid,i,j,val);
	update(2*pos+1,mid+1,right,i,j,val);
}
int query(int pos,int left,int right,int x){
	if(lazy[pos] != 0){
		arvore[pos] = lazy[pos];
		if(left != right){
			lazy[2*pos] = lazy[pos];
			lazy[2*pos+1] = lazy[pos];
		}
		lazy[pos] = 0;
	}
	if(left > right || left > x || right < x) return 0;
	if(left == x && right == x){
		return arvore[pos];
	}
	int mid = (left+right)/2;
	return query(2*pos,left,mid,x) + query(2*pos+1,mid+1,right,x);
}
int main(){
	int TC;
	scanf("%d",&TC);
	while(TC--){
		scanf("%d",&n);
		N = 0;
		memset(arvore,0,sizeof(arvore));
		memset(lazy,0,sizeof(lazy));
		conjunto.clear();
		compressao.clear();
		for(int i=1;i<=n;i++){
			scanf("%d %d",&A[i],&B[i]);
			conjunto.insert(A[i]);
			conjunto.insert(B[i]);
		}
		for(set<int>::iterator it = conjunto.begin();it != conjunto.end();it++){
			compressao[*it] = ++N;
		}
		for(int i=1;i<=n;i++){
			A[i] = compressao[A[i]];
			B[i] = compressao[B[i]];
			update(1,1,N,A[i],B[i],i);
		}
		set<int> valores;
		for(int i=1;i<=N;i++){
			int val = query(1,1,N,i);
			if(val != 0) valores.insert(val);
		}
		printf("%d\n",(int)valores.size());
	}
	return 0;
}