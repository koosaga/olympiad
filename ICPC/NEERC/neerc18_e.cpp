#include <bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;

void print(pi p){
	printf("%c%d ", p.first + 'a', p.second + 1);
}

void REDUCE(vector<pi> &v, vector<pi> imp, int n){
	int ptr = v.size() - 1;
	while(v.size() > n){
		if(find(imp.begin(), imp.end(), v[ptr]) == imp.end()){
			v.erase(v.begin() + ptr);
		}
		ptr--;
	}
}

int main(){
	int n;
	cin >> n;
	n++;
	vector<pi> v, imp;
	if(n <= 15){
		imp.emplace_back(0, 0);
		imp.emplace_back(0, 7);
		imp.emplace_back(7, 7);
		for(int i=0; i<8; i++){
			v.emplace_back(0, i);
		}
		for(int i=1; i<8; i++){
			v.emplace_back(i, 7);
		}
		REDUCE(v, imp, n);
		for(auto &i : v) print(i);
	}
	else if(n <= 57){
		for(int i=0; i<6; i+=2){
			imp.emplace_back(i, 0);
			imp.emplace_back(i, 7);
			imp.emplace_back(i+1, 7);
			imp.emplace_back(i+1, 0);
			for(int j=0; j<8; j++) v.emplace_back(i, j);
			for(int j=0; j<8; j++) v.emplace_back(i+1, 7-j);
		}
		imp.emplace_back(6, 0);
		imp.emplace_back(6, 7);
		imp.emplace_back(7, 7);
		for(int j=0; j<8; j++) v.emplace_back(6, j);
		v.emplace_back(7, 7);
		REDUCE(v, imp, n);
		for(auto &i : v) print(i);
	}
	else{
		for(int i=0; i<6; i+=2){
			imp.emplace_back(i, 0);
			imp.emplace_back(i, 7);
			imp.emplace_back(i+1, 7);
			imp.emplace_back(i+1, 0);
			for(int j=0; j<8; j++) v.emplace_back(i, j);
			for(int j=0; j<8; j++) v.emplace_back(i+1, 7-j);
		}
		for(int i=0; i<7; i++){
			v.emplace_back(7, i);
			imp.emplace_back(7, i);
		}
		for(int i=6; i>=0; i--){
			v.emplace_back(6, i);
			imp.emplace_back(6, i);
		}
		v.emplace_back(6, 7);
		imp.emplace_back(6, 7);
		v.emplace_back(7, 7);
		imp.emplace_back(7, 7);
		REDUCE(v, imp, n);
		for(auto &i : v) print(i);
	}
}
