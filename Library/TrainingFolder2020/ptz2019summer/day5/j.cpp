#include<bits/stdc++.h>
#define sz(v) ((int)(v).size())
using namespace std;
const int MAXN = 3005;
const int mod = 1e9 + 7;
using lint = long long;
using pi = pair<int, int>;

int n, m;
char str[MAXN][MAXN];
bool good[MAXN][MAXN];

int main(){
	scanf("%d %d",&n,&m);
	for(int i=0; i<n; i++) scanf("%s", str[i]);
	for(int i=0; i<n-1; i++){
		for(int j=0; j<m-1; j++){
			if(str[i][j+1] == str[i+1][j]){
				good[i][j] = 1;
			}
		}
	}
	for(int i=0; i<n-1; i++){
		for(int j=0; j<m-1; j++){
			if(good[i][j] && good[i][j+1]){
				puts("YES");
				return 0;
			}
			if(good[i][j] && good[i+1][j]){
				puts("YES");
				return 0;
			}
		}
	}
	for(int i=n-1; i>=0; i--){
		for(int j=m-1; j>=0; j--){
			if(good[i + 1][j + 1] && good[i][j]){
				puts("YES");
				return 0;
			}
			good[i][j] |= (good[i+1][j] | good[i][j+1]);
		}
	}
	puts("NO");
}
