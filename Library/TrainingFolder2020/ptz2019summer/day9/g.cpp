#include <bits/stdc++.h>
using namespace std;
const int MAXN = 20;
using pi = pair<int, int>;
using lint = long long;
#define sz(v) ((int)(v).size())

int n;
lint A[1 << 20], B[1 << 20], D[1 << 20];

int main(){
	scanf("%d",&n);
	for(int i=0; i<(1<<n); i++) scanf("%lld",&A[i]);
	for(int i=0; i<(1<<n); i++) scanf("%lld",&B[i]);
	for(int i=0; i<n; i++){
		for(int j=0; j<(1<<n); j++){
			if((j >> i) & 1){
				A[j] += A[j ^ (1<<i)];
				B[j] += B[j ^ (1<<i)];
			}
		}
	}
	D[0] = min(A[0], B[0]);
	for(int i=1; i<(1<<n); i++){
		D[i] = 1e18;
		for(int j=0; j<n; j++){
			if((i >> j) & 1){
				D[i] = min(D[i], D[i ^ (1<<j)] + min(A[i] - A[i ^ (1 << j)], B[i] - B[i ^ (1 << j)]));
			}
		}
	}
	cout << D[(1<<n) - 1] << endl;
}
