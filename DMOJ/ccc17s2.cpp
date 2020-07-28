// Ivan Carvalho
// Solution to https://dmoj.ca/problem/ccc17s2
#include <bits/stdc++.h>
using namespace std;
int main(){
	int n;
	cin >> n;
	vector<int> E(n);
	for(int i=0;i<n;i++) cin >> E[i];
	sort(E.begin(),E.end());
	int ini_lo = (n + 1)/2 - 1;
	int ini_hi = ini_lo + 1;
	while(true){
		if(ini_lo < 0 && ini_hi >= n) break;
		if(ini_lo >= 0){
			cout << E[ini_lo] << " ";
			ini_lo--;
		}
		if(ini_hi < n){
			cout << E[ini_hi] << " ";
			ini_hi++;
		}
	}
	cout << endl;
 	return 0;
}