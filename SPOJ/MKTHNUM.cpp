// Ivan Carvalho
// Solution to https://www.spoj.com/problems/MKTHNUM/
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
const int MAXN = 1e5 + 10;
vector<int> esq,dir,val,reverso,entrada;
int segIt;
int vetor[MAXN],raiz[MAXN],n,q,tam;
void update(int novo,int velho,int left,int right,int x){
	if(left == right){
		val[novo] = val[velho] + 1;
		return;
	}
	int mid = (left+right)/2;
	if(x <= mid){
		segIt++;
		esq.push_back(0);
		dir.push_back(0);
		val.push_back(0);
		esq[novo] = segIt;
		dir[novo] = dir[velho];
		val[novo] = val[velho] + 1;
		update(esq[novo],esq[velho],left,mid,x);
	}
	else{
		segIt++;
		esq.push_back(0);
		dir.push_back(0);
		val.push_back(0);
		esq[novo] = esq[velho];
		dir[novo] = segIt;
		val[novo] = val[velho] + 1;
		update(dir[novo],dir[velho],mid+1,right,x);
	}
}
int kth(int a,int b,int left,int right,int count){
	if(left == right){
		return left;
	}
	int mid = (left + right)/2;
	int davez = val[esq[a]] - val[esq[b]];
	if(count <= davez) return kth(esq[a],esq[b],left,mid,count);
	return kth(dir[a],dir[b],mid+1,right,count - davez);
}
int main(){
	scanf("%d %d",&n,&q);
	for(int i=1;i<=n;i++){
		scanf("%d",&vetor[i]);
		entrada.push_back(vetor[i]);
	}
	sort(entrada.begin(),entrada.end());
	unique(entrada.begin(),entrada.end());
	reverso.push_back(-1);
	for(int i=0;i<entrada.size();i++){
		reverso.push_back(entrada[i]);
	}
	tam = (int)entrada.size();
	for(int i=1;i<=n;i++){
		vetor[i] = lower_bound(entrada.begin(),entrada.end(),vetor[i]) - entrada.begin() + 1;
	}
	esq.push_back(0);
	dir.push_back(0);
	val.push_back(0);
	for(int i=1;i<=n;i++){
		esq.push_back(0);
		dir.push_back(0);
		val.push_back(0);
		raiz[i] = ++segIt;
		update(raiz[i],raiz[i-1],1,tam,vetor[i]);
	}
	while(q--){
		int l,r,count;
		scanf("%d %d %d",&l,&r,&count);
		printf("%d\n",reverso[kth(raiz[r],raiz[l-1],1,tam,count)]);
	}
	return 0;
} 
