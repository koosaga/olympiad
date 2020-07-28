// Ivan Carvalho
// Solution to https://dmoj.ca/problem/cco10p3
#include <cstdio>
#include <algorithm>
#include <vector>
#define MAXN 1000010
using namespace std;
int vetor[MAXN];
int mapa[MAXN];
char entrada[MAXN];
int entradak[MAXN];
int entradax[MAXN];
int entradar[MAXN];
vector<int> compressao;
int seg[4*MAXN];
void update(int pos,int l,int r,int a,int d){
		if(l==r){
			seg[pos]+=d;
			return;
		}
		seg[pos]+=d;
		int m = (l+r)/2;
		if(a<=m){
			update(2*pos,l,m,a,d);
		}
		else{
			update(2*pos+1,m+1,r,a,d);
		}
	}
int query(int pos,int l,int r,int k){
	int cnt = seg[2*pos];
	//printf("L %d R %d K %d C %d\n",l,r,k,cnt);
	if(l == r) return l;
	int m = (l+r)/2;
	if(k<=cnt){
		return query(2*pos,l,m,k);
	}
	else{
		return query(2*pos+1,m+1,r,k - cnt);
	}
}
int main(){
	int q,qtd = 0;
	scanf("%d",&q);
	for(int i=0;i<q;i++){
		char op;
		scanf(" %c",&op);
		entrada[i] = op;
		if(op == 'N'){	
			int x,r;
			scanf("%d %d",&x,&r);
			entradax[i] = x;
			entradar[i] = r;
			compressao.push_back(r);
		}
		else if(op == 'M'){
			int x,r;
			scanf("%d %d",&x,&r);
			entradax[i] = x;
			entradar[i] = r;
			compressao.push_back(r);
		}
		else if(op == 'Q'){
			int k;
			scanf("%d",&k);
			entradak[i] = k;
		}
	}
	sort(compressao.begin(),compressao.end());
	unique(compressao.begin(),compressao.end());
	int lo = 1, hi = compressao.size();
	for(int i=0;i<q;i++){
		char op = entrada[i];
		if(op == 'N'){	
			qtd++;
			int x,r;
			x = entradax[i];
			r = lower_bound(compressao.begin(),compressao.end(),entradar[i]) - compressao.begin() + 1;
			mapa[r] = x;
			vetor[x] = r;
			update(1,lo,hi,r,1);
			//printf("%d\n",raiz->val);
		}
		else if(op == 'M'){
			int x,r;
			x = entradax[i];
			r = lower_bound(compressao.begin(),compressao.end(),entradar[i]) - compressao.begin() + 1;
			update(1,lo,hi,vetor[x],-1);
			mapa[vetor[x]] = 0;
			vetor[x] = r;
			update(1,lo,hi,r,1);
			mapa[r] = x;
		}
		else if(op == 'Q'){
			int k;
			k = entradak[i];
			k = qtd - k + 1;
			printf("%d\n",mapa[query(1,lo,hi,k)]);
		}
	}
	return 0;
}lo,hi,k)]);
		}
	}
	return 0;
}