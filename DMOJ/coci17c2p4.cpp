// Ivan Carvalho
// Solution to https://dmoj.ca/problem/coci17c2p4
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int MAXN = 50;

vector<int> compressao;
int H1[MAXN],H2[MAXN],NT,N,M;
vector<ll> possiveis[MAXN];
ll G1[MAXN],G2[MAXN],K,resposta;

int main(){

	cin >> NT >> K;
	N = NT/2;
	M = NT - N;

	compressao.push_back(0);
	
	for(int i = 1;i<=N;i++){
		cin >> H1[i] >> G1[i];
		compressao.push_back(H1[i]);
	}

	for(int i = 1;i<=M;i++){
		cin >> H2[i] >> G2[i];
		compressao.push_back(H2[i]);
	}

	sort(compressao.begin(),compressao.end());
	compressao.erase(unique(compressao.begin(),compressao.end()),compressao.end());
	
	for(int i = 1;i<=N;i++){
		H1[i] = lower_bound(compressao.begin(),compressao.end(),H1[i]) - compressao.begin();
	}
	
	for(int i = 1;i<=M;i++){
		H2[i] = lower_bound(compressao.begin(),compressao.end(),H2[i]) - compressao.begin();
	}
	
	for(int bitmask = 1;bitmask < (1 << N);bitmask++){
	
		int last = 0;
		ll total = 0;
		bool flag = false;
	
		for(int i = 0;i<N;i++){
			if(bitmask & (1 << i)){
				int j = i + 1;
				if(H1[last] > H1[j]) flag = true;
				last = j;
				total += G1[j];
			}
		}
	
		if(flag) continue;
		possiveis[H1[last]].push_back(total);
		if(total >= K) resposta++;
	
	}

	for(int i = 0;i<=compressao.size();i++) sort(possiveis[i].begin(),possiveis[i].end());

	for(int bitmask = 1;bitmask < (1 << M);bitmask++){

		int last = 0;
		int first = 0;
		ll total = 0;
		bool flag = false;

		for(int i = 0;i<M;i++){
			if(bitmask & (1 << i)){
				int j = i + 1;
				if(H2[last] > H2[j]) flag = true;
				if(first == 0) first = j;
				last = j;
				total += G2[j];
			}
		}

		if(flag) continue;
		if(total >= K) resposta++;

		for(int i = 0;i<=H2[first];i++){
			resposta += possiveis[i].end() - lower_bound(possiveis[i].begin(),possiveis[i].end(),K - total);
		}

	}

	cout << resposta << endl;

	return 0;
}