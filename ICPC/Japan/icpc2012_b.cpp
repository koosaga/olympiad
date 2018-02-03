#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<lint, int> pi;
typedef long long lint;
const int MAXN = 42;

int main(){
	while(true){
		int n, m;
		cin >> n >> m;
		if(!n) break;
		int tab[21][21][21] = {};
		for(int i=1; i<=20; i++){
			for(int j=1; j<=20; j++){
				for(int k=1; k<=20; k++){
					tab[i][j][k] = 1;
				}
			}
		}
		int cr = 0, cc = 0, cs = 0;
		while(n--){
			string s;
			cin >> s;
			int cnt = 0;
			while(!s.empty() && s[0] == '.') s = s.substr(1, s.size()-1), cnt++;
			for(int i=1; i<=20; i++){
				for(int j=1; j<=20; j++){
					for(int k=1; k<=20; k++){
						if(cnt != i * cr + j * cc + k * cs){
							tab[i][j][k] = 0;
						}
					}
				}
			}
			for(auto &i : s){
				if(i == '(') cr++;
				if(i == ')') cr--;
				if(i == '{') cc++;
				if(i == '}') cc--;
				if(i == '[') cs++;
				if(i == ']') cs--;
			}
		}
		cr = cc = cs = 0;
		while(m--){
			string s;
			cin >> s;
			set<int> cand;
			for(int i=1; i<=20; i++){
				for(int j=1; j<=20; j++){
					for(int k=1; k<=20; k++){
						if(tab[i][j][k]) cand.insert(cr * i + cc * j + cs * k);
					}
				}
			}
			if(cand.size() != 1) printf("-1 ");
			else printf("%d ", *cand.begin());
			for(auto &i : s){
				if(i == '(') cr++;
				if(i == ')') cr--;
				if(i == '{') cc++;
				if(i == '}') cc--;
				if(i == '[') cs++;
				if(i == ']') cs--;
			}
		}
		puts("");
	}
}
