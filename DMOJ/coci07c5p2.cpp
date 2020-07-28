// Ivan Carvalho
// Solution to https://dmoj.ca/problem/coci07c5p2
#include <bits/stdc++.h>
using namespace std;
int main(){
	int n;
	scanf("%d",&n);
	if(n == 1){
		printf("0\n");
		return 0;
	}
	vector<int> divisores;
	vector<int> candidatos;
	for(int j1 = 1;(j1-1)*(j1-1)<=n;j1++){
		if(j1*j1 == n){
			divisores.push_back(j1);
		}
		else if(n % j1 == 0){
			divisores.push_back(j1);
			divisores.push_back(n/j1);
		}
	}
	for(int i : divisores){
		//printf("I %d N-I %d\n",i,n-i);
		candidatos.push_back(n - i);
	}
	sort(candidatos.begin(),candidatos.end());
	for(int i : candidatos){
		if(i == 0) continue;
		if(i % (n - i) == 0){
			printf("%d\n",i);
			return 0;
		}
	}
	return 0;
}