#include "koala.h"
#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
const int MAXN = 105;
int B[MAXN], R[MAXN];
 
int minValue(int N, int W) {
	B[0] = 1;
	playRound(B, R);
	if(count(R, R + N, 0) == 0) return 0;
	return find(R, R + N, 0) - R;
}
 
bool good[MAXN];
 
int maxValue(int N, int W) {
	fill(good, good + N, 1);
	for(int i=0; i<N; i++) B[i] = 1;
	playRound(B, R);
	for(int i=0; i<N; i++){
		if(R[i] > B[i]) good[i] = 1;
		else good[i] = 0;
	}
	for(int i=0; i<N; i++){
		if(good[i]) B[i] = 2;
		else B[i] = 0;
	}
	playRound(B, R);
	vector<int> up1, up2;
	for(int i=0; i<N; i++){
		if(!good[i]) continue;
		if(B[i] < R[i]) up1.push_back(i);
		else up2.push_back(i);
	}
	memset(B, 0, sizeof(B));
	for(auto &i : up1) B[i] = 3;
	for(auto &i : up2) B[i] = 1;
	playRound(B, R);
	memset(good, 0, sizeof(good));
	memset(B, 0, sizeof(B));
	for(auto &i : up1){
		if(3 < R[i]) B[i] = 16;
	}
	playRound(B, R);
	for(auto &i : up1){
		if(B[i] == 16 && R[i] > B[i]) return i;
	}
	assert(0);
}
 
int greaterValue(int N, int W) {
	vector<int> v = {1, 2, 4, 8, 15};
	int s = 0, e = sz(v) - 1;
	while(s <= e){
		int m = (s + e) / 2;
		B[0] = B[1] = v[m];
		playRound(B, R);
		if(R[0] != R[1]){
			return R[0] < R[1];
		}
		else if(R[0] == 0) e = m - 1;
		else s = m + 1;
	}
	assert(0);
}
 
struct node{
	int cost, profit, isSpecial;
};
 
const int inf = 1e9;
 
bool canReachExtreme(vector<node> v, int desired){
	vector<tuple<int, int, int>> dp(105);
	// verify if all special is possible
	for(auto &x : v){
		for(int j = 104; j >= x.cost; j--){
			auto [prof, cnt, special] = dp[j - x.cost];
			dp[j] = max(dp[j], make_tuple(prof + x.profit, cnt + 1, special + x.isSpecial));
		}
	}
	if(get<2>(dp[100]) == desired) return true;
	fill(all(dp), make_tuple(0, 0, 0));
	for(auto &x : v){
		for(int j = 104; j >= x.cost; j--){
			auto [prof, cnt, special] = dp[j - x.cost];
			dp[j] = max(dp[j], make_tuple(prof + x.profit, cnt + 1, special - x.isSpecial));
		}
	}
	if(get<2>(dp[100]) == 0) return true;
	return false;
}
 
int RR[MAXN];
void solve(int L, int R, vector<int> which, int *P){
	if(L + 1 == R){
		P[which[0]] = L;
		return;
	}
	for(int i = 1; i <= 100 / (R - L); i++){
		vector<node> v;
		for(int j = 1; j <= 100; j++){
			if(L <= j && j < R) v.push_back({i + 1, j, 1});
			else v.push_back({1, j, 0});
		}
		if(canReachExtreme(v, R - L)) continue;
		for(auto &pos : which) B[pos] = i; 
		playRound(B, RR);
		vector<int> up, dn;
		for(auto &pos : which){
			if(B[pos] < RR[pos]) up.push_back(pos);
			else dn.push_back(pos);
		}
		for(auto &pos : which) B[pos] = 0;
		assert(sz(up) && sz(dn));
		solve(L, L + sz(dn), dn, P);
		solve(L + sz(dn), R, up, P);
		return;
	}
	assert(0);
}
 
void allValues(int N, int W, int *P) {
	if (W == 2*N) {
		auto cmp = [&](int x, int y){
			memset(B, 0, sizeof(B));
			B[x] = B[y] = 100;
			playRound(B, R);
			if(R[y] > B[y]) return true;
			return false;
		};
		vector<int> v;
		for(int i = 0; i < N; i++){
			int s = 0, e = sz(v);
			while(s != e){
				int m = (s + e) / 2;
				if(cmp(v[m], i)) s = m + 1;
				else e = m;
			}
			v.insert(v.begin() + s, i);
		}
		for(int i = 0; i < N; i++) P[v[i]] = i + 1;
	} else {
		vector<int> which(N);
		iota(all(which), 0);
		solve(1, N + 1, which, P);
	}
}
 
