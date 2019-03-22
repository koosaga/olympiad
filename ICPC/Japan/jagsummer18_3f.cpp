#include <bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;

int xorz(vector<int> v){
	int ret = 0;
	for(auto &i : v) ret ^= i;
	return ret;
}

bool only_even(vector<int> v){
	for(auto &i : v) if(i%2 == 1) return 0;
	return 1;
}

int main(){
	int n; cin >> n;
	vector<int> v(n);
	for(auto &i : v) scanf("%d",&i);
	if(xorz(v) > 1){
		puts("Alice");
	}
	else if(xorz(v) == 1){
		puts("Bob");
	}
	else{
		if(only_even(v)) puts("Bob");
		else puts("Alice");
	}
}
