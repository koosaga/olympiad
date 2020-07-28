// Ivan Carvalho
// Solution to https://dmoj.ca/problem/coci14c4p3
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main(){
	
	vector<int> V;
	ll sum = 0;
	int N;

	cin >> N;
	for(int i = 0;i<N;i++){
		int x;
		cin >> x;
		sum += x;
		V.push_back(x);
	}

	sort(V.begin(),V.end());

	printf("%lld\n",max(2LL*V[N-1],sum));

	return 0;

}