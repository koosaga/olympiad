// Ivan Carvalho
// Solution to https://www.spoj.com/problems/CNTINDX2/
#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
using namespace std;
const int MAXN = 2*(1e5) + 10;
vector<int> val[MAXN],esq[MAXN],dir[MAXN];
int segIt[MAXN];
set<int> conjunto;
map<int,int> compressao;
int op[MAXN],vetor1[MAXN],vetor2[MAXN],vetor3[MAXN],atual[MAXN],freq[4*MAXN],n,m,cnt;
void update_freq(int pos,int left,int right,int x,int delta){
	if(left == right){
		freq[pos] += delta;
		return;
	}
	int mid = (left+right)/2;
	if(x <= mid){
		freq[pos] += delta;
		update_freq(2*pos,left,mid,x,delta);
	}
	else{
		freq[pos] += delta;
		update_freq(2*pos+1,mid+1,right,x,delta);
	}
}
int kth_freq(int pos,int left,int right,int count){
	if(left == right){
		return left;
	}
	int mid = (left+right)/2;
	int davez = freq[2*pos];
	if(count <= davez) return kth_freq(2*pos,left,mid,count);
	return kth_freq(2*pos+1,mid+1,right,count - davez);
}
void update_sparse(int id,int pos,int left,int right,int x,int delta){
	if(left == right){
		val[id][pos] += delta;
		return;
	}
	int mid = (left + right)/2;
	if(x <= mid){
		if(esq[id][pos] == -1){
			esq[id].push_back(-1);
			dir[id].push_back(-1);
			val[id].push_back(0);
			esq[id][pos] = ++segIt[id]; 
		}
		val[id][pos] += delta;
		update_sparse(id,esq[id][pos],left,mid,x,delta);
	}
	else{
		if(dir[id][pos] == -1){
			esq[id].push_back(-1);
			dir[id].push_back(-1);
			val[id].push_back(0);
			dir[id][pos] = ++segIt[id]; 
		}
		val[id][pos] += delta;
		update_sparse(id,dir[id][pos],mid+1,right,x,delta);
	}
}
int query_sparse(int id,int pos,int left,int right,int i,int j){
	if(left > right || left > j || right < i) return 0;
	if(left >= i && right <= j){
		return val[id][pos];
	}
	int mid = (left + right)/2;
	int sinistra = (esq[id][pos] == -1) ? 0 : query_sparse(id,esq[id][pos],left,mid,i,j);
	int destra = (dir[id][pos] == -1) ? 0 : query_sparse(id,dir[id][pos],mid+1,right,i,j);
	return sinistra + destra;
}
int main(){
	scanf("%d %d",&n,&m);
	for(int i=1;i<=n;i++){
		scanf("%d",&vetor2[i]);
		op[i] = 1;
		vetor1[i] = i;
		conjunto.insert(vetor2[i]);
	}
	for(int i = n + 1;i <= n+m;i++){
		scanf("%d",&op[i]);
		if(op[i] == 1){
			scanf("%d %d",&vetor1[i],&vetor2[i]);
			vetor1[i]++;
			conjunto.insert(vetor2[i]);
		}
		else if(op[i] == 2){
			scanf("%d %d",&vetor1[i],&vetor2[i]);
			conjunto.insert(vetor2[i]);
		}
		else{
			scanf("%d %d %d",&vetor1[i],&vetor2[i],&vetor3[i]);
			conjunto.insert(vetor3[i]);
		}
	}
	for(set<int>::iterator it = conjunto.begin();it != conjunto.end();it++){
		compressao[*it] = ++cnt;
	}
	for(int i=1;i <= n+m;i++){
		if(op[i] == 1){
			vetor2[i] = compressao[vetor2[i]];
		}
		else if(op[i] == 2){
			vetor2[i] = compressao[vetor2[i]];
		}
		else{
			vetor3[i] = compressao[vetor3[i]];
		}
	}
	for(int i=1;i<=cnt;i++){
		dir[i].push_back(-1);
		esq[i].push_back(-1);
		val[i].push_back(0);
	}
	for(int i=1;i<=n+m;i++) update_freq(1,1,n+m,i,1);
	for(int i = n + m;i >= 1;i --){
		if(op[i] == 1){
			vetor1[i] = kth_freq(1,1,n+m,vetor1[i]);
			update_freq(1,1,n+m,vetor1[i],-1);
		}
		else if(op[i] == 2){
			vetor1[i] = kth_freq(1,1,n+m,vetor1[i]);
		}
		else{
			vetor1[i] = kth_freq(1,1,n+m,vetor1[i]);
			vetor2[i] = kth_freq(1,1,n+m,vetor2[i]);
		}
	}
	for(int i=1;i<=n+m;i++){
		if(op[i] == 1){
			atual[vetor1[i]] = vetor2[i];
			update_sparse(vetor2[i],0,1,n+m,vetor1[i],1);
		}
		else if(op[i] == 2){
			update_sparse(atual[vetor1[i]],0,1,n+m,vetor1[i],-1);
			atual[vetor1[i]] = vetor2[i];
			update_sparse(vetor2[i],0,1,n+m,vetor1[i],1);
		}
		else{
			printf("%d\n",query_sparse(vetor3[i],0,1,n+m,vetor1[i],vetor2[i]));
		}
	}
	return 0;
}