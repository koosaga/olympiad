// Ivan Carvalho
// Solution to https://dmoj.ca/problem/dmpg17s1
#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>
using namespace std;
int main(){
	int N;
	cin >> N;
	vector<int> E(N);
	for(int i=0;i<N;i++) cin >> E[i];
	sort(E.begin(),E.end());
	int resp = abs(E[1] - E[0]);
	for(int i=2;i<N;i++){
		resp = min(resp, abs(E[i+1] - E[i]) );
	}
	cout << resp << endl;
	return 0;
}