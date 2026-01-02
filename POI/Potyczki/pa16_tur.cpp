#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;

int n;
bool adj[505][505];

int main(){
	cin >> n;
	for(int i=0; i<n; i++){
		string s;
		cin >> s;
		for(int j=0; j<n; j++){
			if(s[j] == 'W') adj[i][j] = 1;
			if(s[j] == '?') adj[i][j] = 1;
		}
	}
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			for(int k=0; k<n; k++){
				adj[j][k] |= (adj[j][i] & adj[i][k]);
			}
		}
	}
	for(int i=0; i<n; i++){
		int cnt = 0;
		for(int j=0; j<n; j++){
			if(i != j && adj[i][j] == 1) cnt++;
		}
		if(cnt == n-1) printf("%d\n", i+1);
	}
}
