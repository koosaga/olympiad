// Ivan Carvalho
// Solution to https://dmoj.ca/problem/dpe
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXV = 1e5 + 10;
const int MAXN = 1e3 + 10;
const ll INF = 1e13;

ll dp[MAXV];
int N,W,V,wi[MAXN],vi[MAXN];

int main(){

	cin >> N >> W;
	for(int i = 1;i<=N;i++){
		cin >> wi[i] >> vi[i];
		V += vi[i];
	}

	for(int i = 1;i<=V;i++) dp[i] = INF;
	dp[0] = 0;
	
	for(int item = 1;item<=N;item++){
		int w = wi[item], v = vi[item];
		for(int i = V;i>=v;i--){
			dp[i] = min(dp[i],dp[i - v] + w);
		}
	}

	for(int i = V;i>=0;i--){
		if(dp[i] <= W){
			cout << i << endl;
			break;
		}
	}

	return 0;

}