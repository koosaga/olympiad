// Ivan Carvalho
// Solution to https://dmoj.ca/problem/ncco3d1p1
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll,ll> ii;
const ll MAXN = 2*1e4 + 20;
ll ADD = 1e4 + 10;
ll freqX[MAXN],freqY[MAXN],X[MAXN],Y[MAXN],totX,totY,N,precoX[MAXN],precoY[MAXN];
set<ii> freq_ponto;
map<ll,ll> freqprecox;
vector<ii> melhores_x,melhores_y;
vector<ll> candidatos;
ll calcX(ll a,ll b){
	if(a > b ) return 0;
	ll resp = freqX[b];
	if(a != 0) resp -= freqX[a-1];
	return resp;
}
ll calcY(ll a,ll b){
	if(a > b ) return 0;
	ll resp = freqY[b];
	if(a != 0) resp -= freqY[a-1];
	return resp;
}
int main(){
	scanf("%lld",&N);
	for(ll i = 1;i<=N;i++){
		scanf("%lld %lld",&X[i],&Y[i]);
		X[i] += ADD;
		Y[i] += ADD;
		freqX[X[i]]++;
		freqY[Y[i]]++;
		freq_ponto.insert(ii(X[i],Y[i]));
	}
	for(ll i = 1;i<MAXN;i++){
		freqX[i] += freqX[i-1];
		freqY[i] += freqY[i-1];
	}
	for(ll i = 1;i<=N;i++) totX += X[i];
	melhores_x.push_back(ii(totX,0));	
	precoX[0] = totX;
	for(ll i = 1;i<MAXN;i++){
		totX += calcX(0,i-1);
		totX -= calcX(i,MAXN-1);
		melhores_x.push_back(ii(totX,i));
		freqprecox[totX]++;
		precoX[i] = totX;
	}
	for(ll i = 1;i<=N;i++) totY += Y[i];
	melhores_y.push_back(ii(totY,0));
	precoY[0] = totY;
	for(ll i = 1;i<MAXN;i++){
		totY += calcY(0,i-1);
		totY -= calcY(i,MAXN-1);
		melhores_y.push_back(ii(totY,i));
		precoY[i] = totY;
	}
	sort(melhores_x.begin(),melhores_x.end());
	sort(melhores_y.begin(),melhores_y.end());
	while(melhores_x.size() >= 500) melhores_x.pop_back();
	while(melhores_y.size() >= 500) melhores_y.pop_back();
	for(ii parx : melhores_x){
		for(ii pary : melhores_y){
			if(!freq_ponto.count(ii(parx.second,pary.second))){
				candidatos.push_back(parx.first+pary.first);
			}
		}	
	}
	sort(candidatos.begin(),candidatos.end());
	ll melhor=  candidatos[0],qtd = 0;
	for(ll i = 0;i<MAXN;i++){
		if(freqprecox.count(melhor - precoY[i])) qtd += freqprecox[melhor - precoY[i]];
	}
	for(ll i = 1;i<=N;i++){
		if(precoX[X[i]] + precoY[Y[i]] == melhor) qtd--;
	}
	printf("%lld %lld\n",melhor,qtd);
	return 0;
}
