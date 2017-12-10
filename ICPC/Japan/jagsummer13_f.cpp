#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
const int mod = 2;
const int MAXN = 300;
 
int n;
 
struct mat{
	int a[MAXN][MAXN];
	mat(int x){
		memset(a, 0, sizeof(a));
		for(int i=0; i<n; i++) a[i][i] = x;
	}
};
 
mat mul(mat A, mat B){
	mat ret(0);
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			for(int k=0; k<n; k++){
				ret.a[i][j] ^= (A.a[i][k] & B.a[k][j]);
			}
		}
	}
	return ret;
}
 
lint m;
int cnt[MAXN], v[MAXN];
int a[MAXN][MAXN], ans[MAXN];
 
int main(){
	cin >> n;
	mat E(1), A(0);
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			scanf("%d",&A.a[i][j]);
		}
	}
	for(int i=0; i<n; i++) cin >> v[i];
	cin >> m;
	while(m){
		if(m & 1) E = mul(E, A);
		A = mul(A, A);
		m >>= 1;
	}
	bool ambig = 0, wrong = 0;
	for(int i=0; i<n; i++){
		int ok = 0;
		int w = v[i];
		for(int j=0; j<n; j++){
			if(E.a[i][j] && a[j][j]){
				for(int k=0; k<n; k++){
					E.a[i][k] ^= a[j][k];
				}
				w ^= ans[j];
			}
			if(E.a[i][j]){
				for(int k=0; k<n; k++) a[j][k] = E.a[i][k];
				ans[j] = w;
				ok = 1;
				break;
			}
		}
		if(!ok){
			ambig = 1;
			if(w) wrong = 1;
		}
	}
	if(ambig && wrong) puts("none");
	else if(ambig) puts("ambiguous");
	else{
		for(int i=n-1; i>=0; i--){
			for(int j=i+1; j<n; j++){
				ans[i] ^= ans[j] * a[i][j];
			}
		}
		for(int i=0; i<n; i++){
			printf("%d", ans[i]);
if(i + 1 < n) printf(" ");
else puts("");
		}
	}
}