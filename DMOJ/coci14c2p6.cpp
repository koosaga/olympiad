// Ivan Carvalho
// Solution to https://dmoj.ca/problem/coci14c2p6
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 5*1e5 + 10;
const int SZ = 1048595;
const int MOD = 1e9;

struct node{

	int soma_len,soma_min,soma_max,soma_minmax,soma_lenmin,soma_lenmax,soma_lenminmax,lazy_len,lazy_min,lazy_max;

	node(){
		soma_len = 0;
		soma_min = 0;
		soma_max = 0;
		soma_minmax = 0;
		soma_lenmin = 0;
		soma_lenmax = 0;
		soma_lenminmax = 0;
		lazy_len = 0;
		lazy_min = 0;
		lazy_max = 0;
	}

	node operator+(const node& other)const{
		node novo;
		novo.soma_len = (soma_len + other.soma_len) % MOD;
		novo.soma_min = (soma_min + other.soma_min) % MOD;
		novo.soma_max = (soma_max + other.soma_max) % MOD;
		novo.soma_minmax = (soma_minmax + other.soma_minmax) % MOD;
		novo.soma_lenmin = (soma_lenmin + other.soma_lenmin) % MOD;
		novo.soma_lenmax = (soma_lenmax + other.soma_lenmax) % MOD;
		novo.soma_lenminmax = (soma_lenminmax + other.soma_lenminmax) % MOD;
		novo.lazy_len = novo.lazy_max = novo.lazy_min = 0;
		return novo; 
	}

};

node seg[SZ];
int N,vetor[MAXN];

void propagate(int pos,int left,int right){

	ll tamanho = (right - left + 1);

	if(seg[pos].lazy_len != 0){
		seg[pos].soma_len = (int)((seg[pos].soma_len + 1LL*seg[pos].lazy_len*tamanho) % MOD);
		seg[pos].soma_lenmin = (int)((seg[pos].soma_lenmin + 1LL*seg[pos].soma_min*seg[pos].lazy_len) % MOD);
		seg[pos].soma_lenmax = (int)((seg[pos].soma_lenmax + 1LL*seg[pos].soma_max*seg[pos].lazy_len) % MOD);
		seg[pos].soma_lenminmax = (int)((seg[pos].soma_lenminmax + 1LL*seg[pos].soma_minmax*seg[pos].lazy_len) % MOD);
		if(left != right){
			seg[2*pos].lazy_len += seg[pos].lazy_len;
			seg[2*pos+1].lazy_len += seg[pos].lazy_len;
		}
		seg[pos].lazy_len = 0;
 	}

 	if(seg[pos].lazy_min != 0){
 		seg[pos].soma_min = (int)((1LL*seg[pos].lazy_min*tamanho) % MOD);
 		seg[pos].soma_minmax = (int)((1LL*seg[pos].lazy_min*seg[pos].soma_max) % MOD);
 		seg[pos].soma_lenmin = (int)((1LL*seg[pos].lazy_min*seg[pos].soma_len) % MOD);
 		seg[pos].soma_lenminmax = (int)((1LL*seg[pos].lazy_min*seg[pos].soma_lenmax) % MOD);
 		if(left != right){
 			seg[2*pos].lazy_min = seg[pos].lazy_min;
 			seg[2*pos+1].lazy_min = seg[pos].lazy_min;
 		}
 		seg[pos].lazy_min = 0;
 	}

 	if(seg[pos].lazy_max != 0){
 		seg[pos].soma_max = (int)((1LL*seg[pos].lazy_max*tamanho) % MOD);
 		seg[pos].soma_minmax = (int)((1LL*seg[pos].lazy_max*seg[pos].soma_min) % MOD);
 		seg[pos].soma_lenmax = (int)((1LL*seg[pos].lazy_max*seg[pos].soma_len) % MOD);
 		seg[pos].soma_lenminmax = (int)((1LL*seg[pos].lazy_max*seg[pos].soma_lenmin) % MOD);
 		if(left != right){
 			seg[2*pos].lazy_max = seg[pos].lazy_max;
 			seg[2*pos+1].lazy_max = seg[pos].lazy_max;
 		}
 		seg[pos].lazy_max = 0;
 	}

}

void update_len(int pos,int left,int right,int i,int j,int val){
	
	propagate(pos,left,right);
	if(left > right || left > j || right < i) return;
	
	if(left >= i && right <= j){
		seg[pos].lazy_len += val;
		propagate(pos,left,right);
		return;
	}

	int mid = (left + right)/2;
	update_len(2*pos,left,mid,i,j,val);
	update_len(2*pos+1,mid+1,right,i,j,val);
	seg[pos] = seg[2*pos] + seg[2*pos+1];

}

void update_min(int pos,int left,int right,int i,int j,int val){
	
	propagate(pos,left,right);
	if(left > right || left > j || right < i) return;
	
	if(left >= i && right <= j){
		seg[pos].lazy_min = val;
		propagate(pos,left,right);
		return;
	}

	int mid = (left + right)/2;
	update_min(2*pos,left,mid,i,j,val);
	update_min(2*pos+1,mid+1,right,i,j,val);
	seg[pos] = seg[2*pos] + seg[2*pos+1];

}

void update_max(int pos,int left,int right,int i,int j,int val){
	
	propagate(pos,left,right);
	if(left > right || left > j || right < i) return;
	
	if(left >= i && right <= j){
		seg[pos].lazy_max = val;
		propagate(pos,left,right);
		return;
	}

	int mid = (left + right)/2;
	update_max(2*pos,left,mid,i,j,val);
	update_max(2*pos+1,mid+1,right,i,j,val);
	seg[pos] = seg[2*pos] + seg[2*pos+1];

}

int main(){

	ll somatorio = 0;
	stack<int> menor,maior;
	scanf("%d",&N);

	for(int i = 1;i<=N;i++){
		scanf("%d",&vetor[i]);
		int comeco_menor,comeco_maior;
		
		while(!menor.empty() && vetor[i] <= vetor[menor.top()]){
			menor.pop();
		}
		while(!maior.empty() && vetor[i] >= vetor[maior.top()]){
			maior.pop();
		}
		

		if(!menor.empty()) comeco_menor = menor.top() + 1;
		else comeco_menor = 1;
		if(!maior.empty()) comeco_maior = maior.top() + 1;
		else comeco_maior = 1;
		
		update_len(1,1,N,1,i,1);
		update_max(1,1,N,comeco_maior,i,vetor[i]);
		update_min(1,1,N,comeco_menor,i,vetor[i]);

		somatorio = (somatorio + seg[1].soma_lenminmax) % MOD;
		menor.push(i);
		maior.push(i);

	}

	printf("%lld\n",somatorio);

	return 0;
}