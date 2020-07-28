// Ivan Carvalho
// Solution to https://www.spoj.com/problems/GSS5/
#include <cstdio>
#include <algorithm>
#define MAXN 100010
using namespace std;
typedef struct node{
	int total,maximo_ini,maximo_fim,maximo; 
}no;
no arvore[4*MAXN];
int vetor[MAXN],acumulada[MAXN],n;
no join(no a,no b){
	no resultado;
	resultado.total = a.total + b.total;
	resultado.maximo_ini = max(a.maximo_ini,a.total + b.maximo_ini);
	resultado.maximo_fim = max(a.maximo_fim + b.total,b.maximo_fim);
	resultado.maximo = max(max(a.maximo,b.maximo), a.maximo_fim + b.maximo_ini );
	return resultado;
}
void build(int pos,int left,int right){
	if(left == right){
		arvore[pos].maximo = arvore[pos].maximo_ini = arvore[pos].maximo_fim = arvore[pos].total = vetor[left];
		return;
	}
	int mid = (left+right)/2;
	build(2*pos,left,mid);
	build(2*pos+1,mid+1,right);
	arvore[pos] = join(arvore[2*pos],arvore[2*pos+1]);
}
no query(int pos,int left,int right,int i,int j){
	if(left >= i && right <= j){
		return arvore[pos];
	}
	int mid = (left+right)/2;
	if(left > mid || left > j || mid < i){
		return query(2*pos+1,mid+1,right,i,j);
	}
	if(mid+1 > right || mid + 1 > j || right < i){
		return query(2*pos,left,mid,i,j);
	}
	return join(query(2*pos,left,mid,i,j),query(2*pos+1,mid+1,right,i,j));
}
int range_sum(int a,int b){
	return acumulada[b] - acumulada[a-1];
}
int solve(int x1,int y1,int x2,int y2){
	//printf("Solve\n");
	if(y1 < x2){
		return query(1,1,n,x1,y1).maximo_fim + range_sum(y1+1,x2-1) + query(1,1,n,x2,y2).maximo_ini;
	}
	//printf("Passou\n");
	int ans = query(1,1,n,x2,y1).maximo;
	if(x2 - 1 >= x1) ans = max(ans,query(1,1,n,x1,x2-1).maximo_fim + query(1,1,n,x2,y2).maximo_ini);
	if (y1 + 1 <= y2) ans = max(ans,query(1,1,n,x1,y1).maximo_fim + query(1,1,n,y1+1,y2).maximo_ini);
	return ans;
}
int main(){
	int TC;
	scanf("%d",&TC);
	while(TC--){
		scanf("%d",&n);
		for(int i=1;i<=n;i++){
			scanf("%d",&vetor[i]);
			acumulada[i] = vetor[i] + acumulada[i-1];
		}
		build(1,1,n);
		int q;
		scanf("%d",&q);
		while(q--){
			int x1,y1,x2,y2;
			scanf("%d %d %d %d",&x1,&y1,&x2,&y2);
			printf("%d\n",solve(x1,y1,x2,y2));				
		}
	}
	return 0;
}