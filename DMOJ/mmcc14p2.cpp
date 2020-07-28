// Ivan Carvalho
// Solution to https://dmoj.ca/problem/mmcc14p2
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll,ll> ii;

const ll MOD1 = 1e9 + 9;
const ll prime1 = 999983;
const ll MOD2 = 1e9 + 7;
const ll prime2 = 999979;
const int MAXN = 2005;
const int MAXM = 5005;

ll pot1[MAXM],pot2[MAXM];
ll hash1[MAXN][MAXM],hash2[MAXN][MAXM];
char entrada[MAXM];
int N,M,Q;

inline ii get_hash(int idx,int a){
	return ii(hash1[idx][a],hash2[idx][a]);
}

inline int binary_search(int idx1,int idx2){
	int ans = 0,lo = 1,hi = M,mid;
	while(lo <= hi){
		mid = lo + (hi-lo)/2;
		if(get_hash(idx1,mid) == get_hash(idx2,mid)){
			ans = mid;
			lo = mid + 1;
		}
		else{
			hi = mid - 1;
		}
	}
	return ans;
}

struct node{
	int valor,prefixo;
	node operator*(const node& other)const{
		node novo;
		novo.valor = valor;
		novo.prefixo = min(min(prefixo,other.prefixo), binary_search(valor,other.valor));
		return novo;
	}
};

int vetor_indices[MAXN];
node seg[4*MAXN];

void build(int pos,int left,int right){
	if(left == right){
		seg[pos].valor = left;
		seg[pos].prefixo = M;
		return;
	}
	int mid = (left+right)/2;
	build(2*pos,left,mid);
	build(2*pos+1,mid+1,right);
	seg[pos] = seg[2*pos]*seg[2*pos+1];
}

node query(int pos,int left,int right,int i,int j){
	if(left >= i && right <= j) return seg[pos];
	int mid = (left+right)/2;
	if(j <= mid) return query(2*pos,left,mid,i,j);
	else if(i >= mid + 1) return query(2*pos+1,mid+1,right,i,j);
	else return query(2*pos,left,mid,i,j)*query(2*pos+1,mid+1,right,i,j);
}

void update(int pos,int left,int right,int x,int val){
	if(left == right){
		seg[pos].valor = val;
		seg[pos].prefixo = M;
		return;
	}
	int mid = (left+right)/2;
	if(x <= mid) update(2*pos,left,mid,x,val);
	else update(2*pos+1,mid+1,right,x,val);
	seg[pos] = seg[2*pos]*seg[2*pos+1];
}

int main(){
	scanf("%d %d",&N,&M);
	pot1[0] = pot2[0] = 1;
	for(int i = 1;i<=M;i++){
		pot1[i] = (pot1[i-1]*prime1) % MOD1;
		pot2[i] = (pot2[i-1]*prime2) % MOD2;
	}
	for(int i = 1;i<=N;i++){
		vetor_indices[i] = i;
		scanf("%s",entrada);
		for(int j = 1;j<=M;j++){
			hash1[i][j] = (hash1[i][j-1] + pot1[j]*entrada[j-1]) % MOD1;
			hash2[i][j] = (hash2[i][j-1] + pot2[j]*entrada[j-1]) % MOD2;
		}
	}
	build(1,1,N);
	scanf("%d",&Q);
	for(int q = 1;q<=Q;q++){
		int i,j;
		scanf("%d %d",&i,&j);
		node resposta = query(1,1,N,i,j);
		printf("%d\n",(j - i + 1)*resposta.prefixo);
		swap(vetor_indices[i],vetor_indices[j]);
		update(1,1,N,i,vetor_indices[i]);
		update(1,1,N,j,vetor_indices[j]);
	}
	return 0;
}
