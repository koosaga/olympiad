#include <bits/stdc++.h>
using namespace std;
const int MAXN = 4005;
const int mod = 1e9 + 7;
using lint = long long;
using pi = pair<lint, lint>;
int adj[26][26];

vector<string> trace;
int main(){
	freopen("javanese.in", "r", stdin);
	freopen("javanese.out", "w", stdout);
	string s;
	while(cin >> s){
		trace.push_back(s);
		for(int i=1; i<s.size(); i++){
			int l = s[i-1] - 'A';
			int r = s[i] - 'A';
			adj[l][r] = adj[r][l] = 1;
		}
	}					
	string vow, con;
	for(int i = 'A'; i <= 'Z'; i++){
		if(i == 'A' || i == 'E' || i == 'I' || i == 'O' || i == 'U'){
			vow.push_back(i);
		}
		else con.push_back(i);
	}
	for(int i=0; i<26; i++){
		for(int j=i+1; j<26; j++){
			for(int k=j+1; k<26; k++){
				for(int l=k+1; l<26; l++){
					for(int m=l+1; m<26; m++){
						int mark[26] = {};
						mark[i] = mark[j] = mark[k] = mark[l] = mark[m] = 1;
						bool fail = 0;
						for(int x = 0; x < 26; x++){
							for(int y = 0; y < 26; y++){
								if(adj[x][y] && mark[x] == mark[y]){
									fail = 1;
								}
							}
						}
						if(!fail){
							int match[256] = {};
							int p1 = 0, p2 = 0;
							for(int i=0; i<26; i++){
								if(mark[i]){
									match[i + 'A'] = vow[p1++];
								}
								else match[i + 'A'] = con[p2++];
							}
							for(auto &i : trace){
								for(auto &j : i) putchar(match[j]);
								putchar(' ');
							}
							return 0;
						}
					}
				}
			}
		}
	}
	puts("impossible");
}

