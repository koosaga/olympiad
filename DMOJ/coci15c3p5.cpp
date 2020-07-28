// Ivan Carvalho
// Solution to https://dmoj.ca/problem/coci15c3p5
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int,int> ii;

const int MAXK = 52;
const int MAXN = 1e5 + 10;
const int INF = 1e9;

int N,K,M,vetor[MAXN];
ll mascara_alvo;

struct node{
	int ptr_ida,ptr_volta,menor;
	ii ida[MAXK],volta[MAXK];

	node(int valor = -1,int posicao = -1){
		if(valor == -1){
			ptr_ida = ptr_volta = 0;
			menor = INF;
		}
		else{
			ptr_ida = ptr_volta = 1;
			menor = (K == 1) ? (1) : (INF);
			ida[0] = ii(valor - 1,posicao);
			volta[0] = ii(valor - 1,posicao);
		}
	}

	node operator*(const node& other)const{
		node novo;
		// Construindo novo.ida
		ll bitmask = 0;
		for(int i = 0;i<ptr_ida;i++){
			novo.ida[i] = ida[i];
			bitmask |= (1LL << ida[i].first);
		}
		novo.ptr_ida = ptr_ida;
		for(int i = 0;i<other.ptr_ida && bitmask != mascara_alvo;i++){
			if(!(bitmask & (1LL << other.ida[i].first))){
				novo.ida[novo.ptr_ida] = other.ida[i];
				novo.ptr_ida++;
				bitmask |= (1LL << other.ida[i].first);
			}
		}
		// Construindo novo.volta
		bitmask = 0;
		for(int i = 0;i<other.ptr_volta;i++){
			novo.volta[i] = other.volta[i];
			bitmask |= (1LL << other.volta[i].first);
		}
		novo.ptr_volta = other.ptr_volta;
		for(int i = 0;i<ptr_volta && bitmask != mascara_alvo;i++){
			if(!(bitmask & 1LL << volta[i].first)){
				novo.volta[novo.ptr_volta] = volta[i];
				novo.ptr_volta++;
				bitmask |= (1LL << volta[i].first);
			}
		}	
		// Calculando o menor
		novo.menor = min(menor,other.menor);
		ll bitmask1 = 0, bitmask2 = 0,ponteiro = other.ptr_ida - 1;
		for(int i = 0;i<other.ptr_ida;i++){
			bitmask1 |= (1LL << other.ida[i].first);
		}
		for(int i = 0;i<ptr_volta;i++){
			bitmask2 |= (1LL << volta[i].first);
			while((bitmask1 | bitmask2) == mascara_alvo && ponteiro >= 0){
				novo.menor = min(novo.menor, abs(volta[i].second - other.ida[ponteiro].second) + 1);
				bitmask1 ^= (1LL << other.ida[ponteiro].first);
				ponteiro--;
			}
		}
		return novo;
	}

};

node seg[4*MAXN];

void build(int pos,int left,int right){
	if(left == right){
		seg[pos] = node(vetor[left],left);
		return;
	}
	int mid = (left+right)/2;
	build(2*pos,left,mid);
	build(2*pos+1,mid+1,right);
	seg[pos] = seg[2*pos]*seg[2*pos+1];
}

void update(int pos,int left,int right,int alvo){
	if(left == right){
		seg[pos] = node(vetor[left],left);
		return;
	}
	int mid = (left+right)/2;
	if(alvo <= mid) update(2*pos,left,mid,alvo);
	else update(2*pos+1,mid+1,right,alvo);
	seg[pos] = seg[2*pos]*seg[2*pos+1];
}

int main(){
	
	scanf("%d %d %d",&N,&K,&M);
	mascara_alvo = (1LL << K) - 1;
	for(int i = 1;i<=N;i++) scanf("%d",&vetor[i]);
	build(1,1,N);

	for(int m = 1;m<=M;m++){
		int op;
		scanf("%d",&op);
		if(op == 1){
			int p,v;
			scanf("%d %d",&p,&v);
			vetor[p] = v;
			update(1,1,N,p);
		}
		else{
			int ans = seg[1].menor;
			if(ans == INF) printf("-1\n");
			else printf("%d\n",ans);
		}
	}

	return 0;
}