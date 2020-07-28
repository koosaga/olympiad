// Ivan Carvalho
// Solution to https://dmoj.ca/problem/coci06c3p1
#include <bits/stdc++.h>
using namespace std;
int V[10],tot;
int main(){
	for(int i=0;i<9;i++){
		cin >> V[i];
		tot += V[i];
	}
	for(int i=0;i<9;i++){
		for(int j = i + 1;j<9;j++){
			if(tot - V[i] - V[j] == 100){
				for(int k=0;k<9;k++){
					if(k != i && k != j){
						cout << V[k] << endl;
					}
				}
				return 0;
			}
		}
	}
	return 0;
}