#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXN = 505;

int n;
bitset<MAXN> bs[505], basis[505], hoobo[505];

int main(){
	scanf("%d",&n);
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			int x; scanf("%d",&x);
			if(x) bs[j][i] = 1;
		}
	}
	for(int i=0; i<n; i++){
		bitset<MAXN> v = bs[i];
		bitset<MAXN> w;
		w[i] = 1;
		bool good = 0;
		for(int j=0; j<n; j++){
			if(v[j]){
				if(!basis[j][j]){
					basis[j] = v;
					hoobo[j] = w;
					good = 1;
					break;
				}
				else{
					v ^= basis[j];
					w ^= hoobo[j];
				}
			}
		}
		if(!good){
			puts("-1");
			return 0;
		}
	}
	for(int i=n-1; i>=0; i--){
		for(int j=i+1; j<n; j++){
			if(basis[i][j]){
				basis[i] ^= basis[j];
				hoobo[i] ^= hoobo[j];
			}
		}
	}
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			if(hoobo[j][i]) printf("%d ", j + 1);
		}
		puts("");
	}
}
