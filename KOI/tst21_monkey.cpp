#include "monkey.h"
#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<int, int>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXN = 400005;
const int mod = 1e9 + 7;

long long max_bananas(std::vector<int> A, std::vector<int> B,
            std::vector<std::pair<int, int> > P){
    int m = sz(P);
    for(auto &[x, y] : P){
    	x--;
    	y--;
	}
    vector<int> nxtX(m, -1);
    vector<int> nxtY(m, -1);
    vector<int> ord(m); iota(all(ord), 0);
    sort(all(P));
	for(int i = 0; i < m - 1; i++){
		if(P[ord[i]].first == P[ord[i + 1]].first) nxtX[ord[i]] = ord[i + 1];
	}
	for(auto &[x, y] : P) swap(x, y);
    sort(all(ord), [&](const int &a, const int &b){
    	return P[a] < P[b];
	});
	for(int i = 0; i < m - 1; i++){
		if(P[ord[i]].first == P[ord[i + 1]].first) nxtY[ord[i]] = ord[i + 1];
	}
	for(auto &[x, y] : P) swap(x, y);
	vector<lint> dp(m);
	for(int i = m - 1; i >= 0; i--){
		dp[i] = A[P[i].first] + B[P[i].second];
		if(~nxtX[i]) dp[i] = max(dp[i], dp[nxtX[i]] + B[P[i].second]);
		if(~nxtY[i]) dp[i] = max(dp[i], dp[nxtY[i]] + A[P[i].first]);
	}
	return *max_element(all(dp));
}
