// Ivan Carvalho
// Solution to https://dmoj.ca/problem/coci08c2p2
#include <bits/stdc++.h>
using namespace std;
int crivo[10000],n,k;
int main(){
	cin >> n >> k;
	for(int i=2;i<=n;i++){
		if(crivo[i]) continue;
		for(int j =i;j<=n;j+=i){
			if(crivo[j] == 0){
				k--;
				crivo[j] = 1;
				if(k == 0){
					cout << j << endl;
					return 0;
				}
			}
		}
	}
	return 0;
}