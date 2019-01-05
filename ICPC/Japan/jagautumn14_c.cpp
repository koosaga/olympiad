#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
using pi = pair<lint, lint>;
const int MAXN = 2505;

int n, m, q;
string s[MAXN], b[MAXN];

bool make_sense(int x, int y){
	for(int i=0; i<q; i++){
		if(s[i][y] != b[i][x]) return 0;
	}
	return 1;
}

int main(){
	while(true){
		cin >> n >> m >> q;
		if(n + m + q == 0) break;
		for(int i=0; i<q; i++){
			cin >> s[i] >> b[i];
		}
		for(int i=q-1; i>0; i--){
			for(int j=0; j<m; j++){
				if(b[i][j] != b[i-1][j]) b[i][j] = '1';
				else b[i][j] = '0';
			}
			//cout << s[i] << " " << b[i] << endl;
		}
		for(int i=0; i<m; i++){
			int cnt = 0, cnd = 0;
			for(int j=0; j<n; j++){
				if(make_sense(i, j)){
					cnt++;
					cnd = j;
				}
			}
			if(cnt != 1) putchar('?');
			else if(cnd < 10) putchar(cnd + '0');
			else putchar(cnd - 10 + 'A');
		}
		cout << endl;
	}
}
