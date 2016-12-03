#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<lint, lint> pi;

int n;
char a[1005][1005], b[1005][1005], c[1005][1005];

int main(){
	while(1){
		cin >> n;
		if(n == 0) break;
		for(int i=0; i<n; i++) scanf("%s",a[i]);
		for(int i=0; i<n; i++) scanf("%s",b[i]);
		string s;
		for(int i=0; i<4; i++){
			for(int j=0; j<n; j++){
				for(int k=0; k<n; k++){
					if(a[j][k] == 'O') s.push_back(b[j][k]);
				}
			}
			for(int j=0; j<n; j++){
				for(int k=0; k<n; k++){
					c[j][k] = a[n-1-k][j];
				}
			}
			for(int j=0; j<n; j++){
				for(int k=0; k<n; k++){
					a[j][k] = c[j][k];
				}
			}
		}
		puts(s.c_str());
	}
}
