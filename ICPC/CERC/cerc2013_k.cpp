#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;

bool adj[26][26], flo[26][26];
int tra[26][26];

string get(int s, int e){
	if(adj[s][e]){
		string st;
		st.push_back(s + 'a');
		st.push_back(e + 'a');
		return st;
	}
	string t = get(s, tra[s][e]);
	t.pop_back();
	t += get(tra[s][e], e);
	return t;
}

int dp[26];

int f(int x){
	if(~dp[x]) return dp[x];
	int ret = 0;
	for(int i=0; i<26; i++){
		if(adj[x][i]) ret = max(ret, f(i));
	}
	return dp[x] = ret + 1;
}

string trak(int x){
	string t;
	t.push_back(x + 'a');
	for(int i=0; i<26; i++){
		if(adj[x][i] &&f(x) == f(i) + 1){
			t += trak(i);
			break;
		}
	}
	return t;
}

void solve(){
	for(int i=0; i<26; i++){
		for(int j=0; j<26; j++){
			adj[i][j] = 1;
			flo[i][j] = 0;
		}
	}
	int e;
	cin >> e;
	while(e--){
		string s;
		cin >> s;
		s[0] -= 'a';
		s[1] -= 'a';
		adj[s[0]][s[1]] = 0;
	}
	for(int i=0; i<26; i++){
		for(int j=0; j<26; j++){
			flo[i][j] = adj[i][j];
			tra[i][j] = -1;
		}
	}
	for(int i=0; i<26; i++){
		for(int j=0; j<26; j++){
			for(int k=0; k<26; k++){
				if(flo[j][k]) continue;
				if(flo[j][i] & flo[i][k]){
					flo[j][k] = 1;
					tra[j][k] = i;
				}
			}
		}
	}
	for(int i=0; i<26; i++){
		if(flo[i][i]){
			string s = get(i, i);
			s.pop_back();
			for(int i=0; i<20; i++){
				for(int j=0; j<20; j++){
					putchar(s[(i+j)%s.size()]);
				}
				puts("");
			}
			return;
		}
	}
	memset(dp, -1, sizeof(dp));
	int p = -1, q = -1;
	for(int i=0; i<26; i++){
		if(p < f(i)){
			p = f(i);
			q = i;
		}
	}
	string s = trak(q);
	int l = (s.size() + 1) / 2;
	for(int i=0; i<l; i++){
		for(int j=0; j<l; j++){
			putchar(s[i+j]);
		}
		puts("");
	}
}

int main(){
	int t;
	cin >> t;
	while(t--){
		solve();
	}
}
