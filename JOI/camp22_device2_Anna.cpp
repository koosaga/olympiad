#include "Anna.h"
#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<lint, lint>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
 
namespace {
	lint dp[155];
	void init(){
		for(int i = 1; i < 155; i++){
			// [1] 2 3 2 3 3 .... [0+]
			dp[i] = 1 + (i >= 3 ? dp[i - 2] : 0) + (i >= 4 ? dp[i - 3] : 0);
		}
	}
	vector<int> encode(lint X){
		for(int i = 1; ; i++){
			if(X < dp[i]){
				vector<int> v;
				for(int k = i; ; ){
					if(X == 0){
						v.push_back(-k);
						break;
					}
					X--;
					if(X < dp[k - 2]){
						v.push_back(2);
						k -= 2;
					}
					else{
						X -= dp[k - 2];
						v.push_back(3);
						k -= 3;
					}
				}
				return v;
			}
			X -= dp[i];
		}
	}
}
 
int Declare() {
  return 140;
}
 
std::pair<std::vector<int>, std::vector<int> > Anna(long long A) {
	init();
	auto v = encode(A / 2);
	int f = 1;
	vector<int> X, Y;
	X.push_back(1);
	cout << A % 2 << " ";
	for(int i = 0; i < sz(v); i++) cout << v[i] << " ";
	cout << endl;
	for(int i = 0; i < sz(v); i++){
		if(v[i] == 3 || v[i] <= 0) f ^= 1;
		int it = (v[i] > 0 ? v[i] : (abs(v[i]) - 1));
		for(int j = 0; j < it; j++){
			X.push_back(f);
			if(v[i] < 0) f ^= 1;
		}
	}
	Y.resize(sz(X));
	for(int i = 0; i < sz(X); i++){
		Y[i] = (i + 1) % 2;
	}
	if(A & 1){
		for(auto &i : X) i ^= 1;
		for(auto &i : Y) i ^= 1;
	}
	return make_pair(X, Y);
}

