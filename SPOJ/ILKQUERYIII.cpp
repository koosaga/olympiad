// Ivan Carvalho
// Solution to https://www.spoj.com/problems/ILKQUERYIII/
#include <cstdio>
#include <vector>
#include <algorithm>
#include <set>
#include <map>
using namespace std;
const int MAXN = 1e6 + 10;
vector<int> val,dir,esq,ap[MAXN];
set<int> conjunto;
map<int,int> compressao;
int raiz[MAXN],vetor[MAXN],n,m,segIt,cnt;
inline int find_val(int ptr){
	if(ptr == -1) return 0;
	return val[ptr];
}
inline int find_esq(int ptr){
	if(ptr == -1) return - 1;
	return esq[ptr];
}
inline int find_dir(int ptr){
	if(ptr == -1) return -1;
	return dir[ptr];
}
void update(int novo,int velho,int left,int right,int x,int delta){
	if(left == right){
		val[novo] = find_val(velho) + delta;
		return;
	}
	int mid = (left+right)/2;
	if(x <= mid){
		segIt++;
		esq.push_back(-1);
		dir.push_back(-1);
		val.push_back(0);
		esq[novo] = segIt;
		dir[novo] = find_dir(velho);
		val[novo] = find_val(velho) + delta;
		update(esq[novo],find_esq(velho),left,mid,x,delta);
	}
	else{
		segIt++;
		esq.push_back(-1);
		dir.push_back(-1);
		val.push_back(0);
		esq[novo] = find_esq(velho);
		dir[novo] = segIt;
		val[novo] = find_val(velho) + delta;
		update(dir[novo],find_dir(velho),mid+1,right,x,delta);
	}
}
int kth(int a,int left,int right,int count){
	if(left == right){
		return left;
	}
	int mid = (left+right)/2;
	int davez = find_val(find_esq(a));
	if(count <= davez) return kth(find_esq(a),left,mid,count);
	return kth(find_dir(a),mid+1,right,count - davez);
}
int main(){
	scanf("%d %d",&n,&m);
	for(int i=1;i<=n;i++){
		scanf("%d",&vetor[i]);
		conjunto.insert(vetor[i]);
	}
	for(set<int>::iterator it = conjunto.begin();it != conjunto.end();it++){
		compressao[*it] = ++cnt;
	}
	for(int i=1;i<=n;i++){
		vetor[i] = compressao[vetor[i]];
		//printf("%d ",vetor[i]);
		ap[vetor[i]].push_back(i);
	}
	//printf("\n");
	dir.push_back(-1);
	esq.push_back(-1);
	val.push_back(0);
	update(0,-1,1,cnt,vetor[1],1);
	for(int i=2;i<=n;i++){
		dir.push_back(-1);
		esq.push_back(-1);
		val.push_back(0);
		raiz[i] = ++segIt;
		update(raiz[i],raiz[i-1],1,cnt,vetor[i],1);
	}
	while(m--){
		int op;
		scanf("%d",&op);
		if(op == 0){
			int i,l,count;
			scanf("%d %d %d",&i,&l,&count);
			i++;
			int k = kth(raiz[i],1,cnt,count);
			if(ap[k].size() >= l){
				printf("%d\n",ap[k][l-1] - 1);
			}
			else printf("-1\n");
		}
		else{
			int p;
			scanf("%d",&p);
			p++;
			if(p == n) continue;
			int antigo = raiz[p];
			dir.push_back(-1);
			esq.push_back(-1);
			val.push_back(0);
			raiz[p] = ++segIt;
			update(raiz[p],antigo,1,cnt,vetor[p],-1);
			vector<int>::iterator it1,it2;
			it1 = lower_bound(ap[vetor[p]].begin(),ap[vetor[p]].end(),p);
			*it1 = p+1;
			it2 = lower_bound(ap[vetor[p+1]].begin(),ap[vetor[p+1]].end(),p+1);
			*it2 = p;
			//printf("%d %d\n",*it1,*it2);
			swap(vetor[p],vetor[p+1]);
			antigo = raiz[p];
			dir.push_back(-1);
			esq.push_back(-1);
			val.push_back(0);
			raiz[p] = ++segIt;
			update(raiz[p],antigo,1,cnt,vetor[p],1);
		}
	}
	return 0;
}