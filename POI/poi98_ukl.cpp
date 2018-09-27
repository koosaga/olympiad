#include <bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
using lint = long long;
const int MAXN = 3005;

int n, p1[MAXN], p2[MAXN], op[MAXN], piv = 26;
int C[26], vis[MAXN];

void dfs(int x){
	if(x == -1) return;
	if(vis[x]) return;
	vis[x] = 1;
	dfs(p1[x]); dfs(p2[x]);
}

int main(){
	cin >> n;
	for(int i=0; i<26; i++){
		p1[i] = p2[i] = -1;
		C[i] = i; // current pointer
	}
	for(int i=0; i<n; i++){
		string s;
		cin >> s;
		int l = s[1] - 'a', r = s[2] - 'a';
		int found = 0;
		for(int j=0; j<piv; j++){
			if(make_tuple(op[j], p1[j], p2[j]) == 
					make_tuple(s[0], C[l], C[r])){
				C[s[3] - 'a'] = j;
				found = 1;
				break;
			}
		}
		if(!found){
			op[piv] = s[0];
			p1[piv] = C[l], p2[piv] = C[r];
			C[s[3] - 'a'] = piv;
			piv++;
		}
	}
	for(int i=0; i<26; i++){
		dfs(C[i]);
	}
	int cnt = 0;
	for(int i=26; i<piv; i++){
		if(vis[i]) cnt++;
	}cout<<cnt<<endl;
}
