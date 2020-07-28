// Ivan Carvalho
// Solution to https://dmoj.ca/problem/coci08c2p4
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const ll INF = 2*1e9;

ll calcula(ll X,vector<ll> A,vector<ll> B){

	ll tot = 0;
	for(int i = 0;i<A.size();i++){
		if(A[i] > X) continue;
		tot++;
		tot += (X - A[i])/B[i];
	}

	return tot;

}

ll calcula_tempo(ll coco, vector<ll> A,vector<ll> B){

	ll ini = 1,fim = INF,meio,resp = INF;
	while(ini <= fim){
		meio = (ini+fim)/2;
		ll cand = calcula(meio,A,B);
		if(cand >= coco){
			resp = meio;
			fim = meio - 1;
		}
		else{
			ini = meio + 1;
		}
	}

	return resp;

}

ll checa(ll X,ll T,vector<ll> A,vector<ll> B, vector<ll> C,vector <ll> D){

	ll coco = calcula(X,A,B);
	ll tempo_abrir = calcula_tempo(coco,C,D); 

	return X + tempo_abrir >= T;

}

int main(){

	ll T;
	int N,M;
	vector<ll> A,B,C,D;

	cin >> T;
	cin >> N;
	for(int i = 0;i<N;i++){
		ll x,y;
		cin >> x >> y;
		A.push_back(x);
		B.push_back(y);
	}
	cin >> M;
	for(int i = 0;i<M;i++){
		ll x,y;
		cin >> x >> y;
		C.push_back(x);
		D.push_back(y);
	}

	ll ini = 1,fim = T, resp = T,meio;
	while(ini <= fim){
		meio = (ini+fim)/2;
		if(checa(meio,T,A,B,C,D)){
			resp = meio;
			fim = meio - 1;
		}
		else{
			ini = meio + 1;
		}
	}

	cout << resp << endl;

	return 0;

}