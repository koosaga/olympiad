// Ivan Carvalho
// Solution to https://dmoj.ca/problem/dpd
#include <bits/stdc++.h>
using namespace std;

const int MAXW = 1e5 + 10;

long long knapsack[MAXW];
int N,W;

int main(){

	cin >> N >> W;

	for(int item = 1;item<=N;item++){
		int w,v;
		cin >> w >> v;
		for(int i = W;i>=w;i--) knapsack[i] = max(knapsack[i-w] + v,knapsack[i]);
	}

	long long best = 0;
	for(int i = 0;i<=W;i++) best = max(best,knapsack[i]);
	cout << best << endl;

	return 0;

}