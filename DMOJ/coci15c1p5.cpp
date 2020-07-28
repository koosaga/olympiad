// Ivan Carvalho
// Solution to https://dmoj.ca/problem/coci15c1p5
#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e5 + 10;
const int MOD = 1e4 + 7;
const int MAXC = 20;
const int SZ = 262153;

struct node{
	
	int produtorio,combinacoes[MAXC];
	
	node(){
		produtorio = 0;
		for(int i = 0;i<MAXC;i++) combinacoes[i] = 0;
	}
	
	node operator*(const node &other)const{
		node novo;
		for(int i = 0;i<MAXC;i++){
			for(int j = 0;j+i<MAXC;j++){
				novo.combinacoes[i+j] += combinacoes[i]*other.combinacoes[j];
			}
		}
		for(int i = 0;i<MAXC;i++) novo.combinacoes[i] %= MOD;
		novo.produtorio = (produtorio*other.produtorio) % MOD;
		return novo;
	}

};

int A[MAXN],B[MAXN],N,C,Q;
node seg[SZ];

void build(int pos,int left,int right){
	if(left == right){
		seg[pos].produtorio = A[left] + B[left];
		seg[pos].combinacoes[0] = B[left];
		seg[pos].combinacoes[1] = A[left];
		return;
	}
	int mid = (left+right)/2;
	build(2*pos,left,mid);
	build(2*pos+1,mid+1,right);
	seg[pos] = seg[2*pos]*seg[2*pos+1];
}

void update(int pos,int left,int right,int x){
	if(left == right){
		seg[pos].produtorio = A[left] + B[left];
		seg[pos].combinacoes[0] = B[left];
		seg[pos].combinacoes[1] = A[left];
		return;
	}
	int mid = (left+right)/2;
	if(x <= mid) update(2*pos,left,mid,x);
	else update(2*pos+1,mid+1,right,x);
	seg[pos] = seg[2*pos]*seg[2*pos+1];
}

int main(){
	scanf("%d %d",&N,&C);
	for(int i = 1;i<=N;i++){
		scanf("%d",&A[i]);
		A[i] %= MOD;
	}
	for(int i = 1;i<=N;i++){
		scanf("%d",&B[i]);
		B[i] %= MOD;
	}
	build(1,1,N);
	scanf("%d",&Q);
	for(int q = 1;q<=Q;q++){
		int pos,ai,bi;
		scanf("%d %d %d",&pos,&ai,&bi);
		A[pos] = ai % MOD;
		B[pos] = bi % MOD;
		update(1,1,N,pos);
		int tot = seg[1].produtorio;
		for(int i = 0;i<C;i++){
			tot -= seg[1].combinacoes[i];
		}
		tot = ( (tot % MOD) + MOD) % MOD;
		printf("%d\n",tot);
	}
	return 0;
}