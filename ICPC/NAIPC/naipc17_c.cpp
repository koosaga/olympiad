#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;
const int mod = 1e9 + 7;


int gcd(int x, int y){
	return y ? gcd(y, x%y) : x;
}

lint d1[305][305], d2[305][305];
int n, a[305];
bool adj[305][305];

int main(){
	cin >> n;
	for(int i=0; i<n; i++) cin >> a[i];
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			adj[i][j] = (gcd(a[i], a[j]) != 1);
			if(i == j) adj[i][j] = 0;
		}
	}
	for(int i=0; i<n; i++){
		d2[i][i] = 1;
	}
	for(int i=1; i<n; i++){
		for(int j=0; j+i<n; j++){
			int s = j, e = j+i;
			for(int k=s+1; k<=e; k++){
				if(adj[k][e]) d1[s][e] += d1[s][k] * d1[k][e] % mod;
			}
			d1[s][e] += d2[s][e-1];
			d1[s][e] %= mod;
		}
		for(int j=0; j+i<n; j++){
			int s = j, e = j+i;
			for(int k=s+1; k<=e; k++){
				if(adj[s][k]) d2[s][e] += d1[s][k] * d2[k][e] % mod;
			}
			d2[s][e] %= mod;
		}
	}
	cout << d2[0][n-1];
}
