#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, double> pi;
const int MAXN = 205;

int adj[26][26];

int main(){
	while(true){
		memset(adj, 0, sizeof(adj));
		int n;
		cin >> n;
		if(!n) break;
		vector<string> v(n);
		for(auto &i : v) cin >> i;
		bool ans = 1;
		for(int i=1; i<n; i++){
			bool ok = 0;
			for(int j=0; j<v[i-1].size() && j<v[i].size(); j++){
				if(v[i][j] != v[i-1][j]){
					adj[v[i-1][j] - 'a'][v[i][j] - 'a'] = 1;
					ok = 1;
					break;
				}
			}
			if(!ok){
				if(v[i].size() < v[i-1].size()){
					ans = 0;
				}
			}
		}
		for(int i=0; i<26; i++){
			for(int j=0; j<26; j++){
				for(int k=0; k<26; k++){
					adj[j][k] |= (adj[j][i] & adj[i][k]);
				}
			}
		}
		for(int i=0; i<26; i++) if(adj[i][i]) ans = 0;
		puts(ans ? "yes" : "no");
	}
}
