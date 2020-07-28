// Ivan Carvalho
// Solution to https://www.spoj.com/problems/HRSIAM/
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e5 + 10;
const int BUCKET = 2160;
struct upd{int pos,velho,novo;};
struct que{int l,r,t,id;};
int divisao[MAXN];
bool comp(que A,que B){
	if(divisao[A.l] != divisao[B.l]) return divisao[A.l] < divisao[B.l];
	if(divisao[A.r] != divisao[B.r]) return divisao[A.r] < divisao[B.r];
	return A.t < B.t;
}
int mo_left,mo_right,mo_time,n,q,freq[MAXN],vetor[MAXN],angry[MAXN];
long long exibir[MAXN],resp;
vector<que> Q;
vector<upd> U;
void add(int val){
	freq[val]++;
	resp += 1LL*angry[freq[val]]*val;
}
void remove(int val){
	resp -= 1LL*angry[freq[val]]*val;
	freq[val]--;
}
void update(int idx,int novo){
	if(mo_left <= idx && idx <= mo_right){
		remove(vetor[idx]);
		vetor[idx] = novo;
		add(vetor[idx]); 
	}
	else{
		vetor[idx] = novo;
	}
}
void doQuery(int idx){
	for(int t = mo_time+1;t<=Q[idx].t;t++) update(U[t-1].pos,U[t-1].novo);
	for(int t = mo_time;t>Q[idx].t;t--) update(U[t-1].pos,U[t-1].velho);
	for(int i = mo_right + 1;i<=Q[idx].r;i++) add(vetor[i]);
	for(int i = mo_left - 1;i>=Q[idx].l;i--) add(vetor[i]);
	for(int i = mo_right;i>Q[idx].r;i--) remove(vetor[i]);
	for(int i = mo_left;i<Q[idx].l;i++) remove(vetor[i]);
	mo_left = Q[idx].l;mo_right = Q[idx].r;mo_time = Q[idx].t;
	exibir[Q[idx].id] = resp;
}
int main(){
	scanf("%d",&n);
	for(int i = 0;i<n;i++){
		scanf("%d",&vetor[i]);
		divisao[i] = i/BUCKET;
	}
	for(int i = 1;i<=n;i++){
		scanf("%d",&angry[i]);
	}
	scanf("%d",&q);
	for(int i = 0;i<q;i++){
		int x,y,z;
		scanf("%d %d %d",&x,&y,&z);
		if(x == 1){
			que davez;
			y--;z--;
			davez.l = y;davez.r = z;davez.t = mo_time;davez.id = i;
			Q.push_back(davez);
		}
		else{
			y--;mo_time++;
			upd davez;
			davez.pos = y;davez.velho = vetor[y];davez.novo = z;
			vetor[y] = z;
			U.push_back(davez);
			exibir[i] = -1;
		}
	}
	sort(Q.begin(),Q.end(),comp);
	for(int i = 0;i<n;i++) add(vetor[i]);
	mo_left = 0;mo_right = n-1;
	for(int i = 0;i<Q.size();i++) doQuery(i);
	for(int i = 0;i<q;i++) if(exibir[i] != -1) printf("%lld\n",exibir[i]);
	return 0;
} 