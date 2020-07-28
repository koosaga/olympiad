// Ivan Carvalho
// Solution to https://dmoj.ca/problem/ioi02p4
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN = 1e4 + 10;
ll T[MAXN],F[MAXN],B[MAXN],N,S,somatorio1[MAXN],somatorio2[MAXN];
int main(){
	cin >> N >> S;
	for(int i = 1;i<=N;i++){
		cin >> T[i] >> F[i];
	}
	for(int i = N;i>=1;i--){
		somatorio1[i] = somatorio1[i+1] + T[i];
		somatorio2[i] = somatorio2[i+1] + F[i];
	}
	for(int i = N;i >= 1;i--){
		B[i] = 1e18;
		for(int j = N+1;j>i;j--){
			ll cand = (B[j] + (S + somatorio1[i] - somatorio1[j])*somatorio2[i]);
			if(cand < B[i]) B[i] = cand;
		}
	}
	cout << B[1] << endl;
	return 0;
}