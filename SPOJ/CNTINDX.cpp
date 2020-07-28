// Ivan Carvalho
// Solution to https://www.spoj.com/problems/CNTINDX/
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
const int MAXN = 2*1e5 + 10;
vector<int> esq[MAXN],dir[MAXN],val[MAXN];
int segIt[MAXN],n;
vector<int> vetor;
void update(int id,int pos,int left,int right,int x,int delta){
	if(left == right){
		val[id][pos] += delta;
		return;
	}
	int mid = (left+right)/2;
	if(x <= mid){
		if(esq[id][pos] == -1){
			esq[id].push_back(-1);
			dir[id].push_back(-1);
			val[id].push_back(0);
			esq[id][pos] = ++segIt[id];
		}
		val[id][pos] += delta;
		update(id,esq[id][pos],left,mid,x,delta);
	}
	else{
		if(dir[id][pos] == -1){
			esq[id].push_back(-1);
			dir[id].push_back(-1);
			val[id].push_back(0);
			dir[id][pos] = ++segIt[id];
		}
		val[id][pos] += delta;
		update(id,dir[id][pos],mid+1,right,x,delta);
	}
}
int query(int id,int pos,int left,int right,int i,int j){
	if(left > right || left > j || right < i) return 0;
	if(left >= i && right <= j){
		return val[id][pos];
	}
	int mid = (left+right)/2;
	int sinistra = (esq[id][pos] == -1) ? 0 : query(id,esq[id][pos],left,mid,i,j);
	int destra = (dir[id][pos] == -1) ? 0 : query(id,dir[id][pos],mid+1,right,i,j);
	return sinistra + destra;
}
int main(){
	for(int i=1;i<MAXN;i++){
		esq[i].push_back(-1);
		dir[i].push_back(-1);
		val[i].push_back(0);
	}
	scanf("%d",&n);
	for(int vez = 1;vez <= n;vez++){
		int op;
		scanf("%d",&op);
		if(op == 0){
			if(vetor.empty()){
				printf("invalid\n");
				continue;
			}
			update(vetor[vetor.size()-1],0,1,n,vetor.size(),-1);
			vetor.pop_back();
		}
		else if(op == 1){
			int davez;
			scanf("%d",&davez);
			vetor.push_back(davez);
			update(davez,0,1,n,vetor.size(),1);
		}
		else{
			int x,i,j;
			scanf("%d %d %d",&x,&i,&j);
			printf("%d\n",query(x,0,1,n,i,j));
		}
	}
	return 0;
}