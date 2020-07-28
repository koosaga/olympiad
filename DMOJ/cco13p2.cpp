// Ivan Carvalho
// Solution to https://dmoj.ca/problem/cco13p2
#include <cstdio>
#include <algorithm>
#define MP make_pair
using namespace std;
const int TREE_SIZE = 2097161;
const int ARRAY_SIZE = (1 << 20) + 10;
typedef pair<int,int> ii;
ii arvore[TREE_SIZE];
int habilidade[ARRAY_SIZE],aparece[ARRAY_SIZE];
void build(int pos,int left,int right){
	if(left == right){
		arvore[pos] = MP(habilidade[left],left);
		aparece[left]++;
		return;	
	}
	int mid = (left+right)/2;
	build(2*pos,left,mid);
	build(2*pos+1,mid+1,right);
	arvore[pos] = max(arvore[2*pos],arvore[2*pos+1]);
	aparece[arvore[pos].second]++;
} 
void update(int pos,int left,int right,int x,int val){
	aparece[arvore[pos].second]--;
	if(left == right){
		arvore[pos] = MP(val,x);
		aparece[x]++;
		return;
	}
	int mid = (left+right)/2;
	if(x <= mid){
		update(2*pos,left,mid,x,val);
	}
	else{
		update(2*pos+1,mid+1,right,x,val);
	}
	arvore[pos] = max(arvore[2*pos],arvore[2*pos+1]);
	aparece[arvore[pos].second]++;
}
int main(){
	int N,M;
	scanf("%d %d",&N,&M);
	N = (1 << N);
	for(int i=1;i<=N;i++) scanf("%d",&habilidade[i]);
	build(1,1,N);
	while(M--){
		char op;
		scanf(" %c",&op);
		if(op == 'R'){
			int i,S;
			scanf("%d %d",&i,&S);
			update(1,1,N,i,S);
		}
		else if(op == 'W'){
			printf("%d\n",arvore[1].second);
		}
		else if(op == 'S'){
			int i;
			scanf("%d",&i);
			printf("%d\n",aparece[i] - 1);
		}
	}
	return 0;
}