// Ivan Carvalho
// Solution to https://dmoj.ca/problem/dmopc15c3p5
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
vector<ll> A,B;
map<ll,int> freq;
int n,m,meio;
ll resp;
int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> n >> m;
	meio = (n + m)/2;
	for(int i=0;i<meio;i++){
		ll val;
		cin >> val;
		if(i >= n) val *= -1;
		A.push_back(val);
	}
	for(int i=meio;i<n+m;i++){
		ll val;
		cin >> val;
		if(i >= n) val *= -1;
		B.push_back(val);
	}
	n = A.size();
	m = B.size();
	for(int bitmask=1;bitmask< (1 << n);bitmask++){
		ll soma = 0;
		for(int i=0;i<n;i++) if(bitmask & (1 << i)) soma += A[i];
		freq[soma]++;
		if(soma == 0) resp++;
	}
	for(int bitmask=1;bitmask< (1 << m);bitmask++){
		ll soma = 0;
		for(int i=0;i<m;i++) if(bitmask & (1 << i)) soma += B[i];
		if(freq.count(-soma)) resp += 1LL*freq[-soma];
		if(soma == 0) resp++;
	}
	cout << resp << endl;
	return 0;
}