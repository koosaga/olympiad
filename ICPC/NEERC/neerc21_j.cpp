#include <bits/stdc++.h>
using namespace std;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using lint = long long;
using pi = pair<lint, lint>;
 
typedef long long ll;
typedef pair<int,int> pii;
const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3f;
 
int N;
ll C[210][210];
ll S[210][210];
ll D[210][210];
int via[210][210];
int par[210];
 
ll c(int i, int j, int k) {
	return S[j][N]-S[k][N]-(S[j][j]-S[k][j]-S[j][k]+S[k][k])
	+S[k-1][N]-S[i-1][N]-(S[k-1][k-1]-S[i-1][k-1]-S[k-1][i-1]+S[i-1][i-1]);
}
 
void track(int i, int j, int p) {
	if (i>j) return;
	if (i==j) {
		par[i] = p;
		return;
	}
	int k = via[i][j];
	par[k] = p;
	track(i,k-1,k);track(k+1,j,k);
}
 
int main(){
	scanf("%d",&N);
	for (int i=1;i<=N;i++) {
		for (int j=1;j<=N;j++) scanf("%lld",&C[i][j]);
	}
	for (int i=1;i<=N;i++) {
		for (int j=1;j<=N;j++) {
			S[i][j] = C[i][j]+S[i-1][j]+S[i][j-1]-S[i-1][j-1];
		}
	}
	for (int l=0;l<N;l++) {
		for (int i=1;i+l<=N;i++) {
			int j = i+l;
			D[i][j] = LINF;
			for (int k=i;k<=j;k++) {
				ll val = D[i][k-1]+D[k+1][j]+c(i,j,k);
				if (D[i][j]>val) {
					D[i][j]=val;
					via[i][j] = k;
				}
			}
//			printf("%d, %d: %lld\n",i,j,D[i][j]);
		}
	}
	track(1,N,0);
	for (int i=1;i<=N;i++) {
		printf("%d ",par[i]);
	}
	puts("");
 
	return 0;
}