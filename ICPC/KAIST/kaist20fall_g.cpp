#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXN = 200005;

int n, k, a[MAXN], b[6];

int main(){
	scanf("%d %d",&n,&k);
	for(int i=0; i<6; i++) scanf("%d",&b[i]);
	for(int i=0; i<n; i++){
		scanf("%d",&a[i]);
		a[i]--;
	}
	int dap = 0;
	for(int i=1; i<64; i++){
		int cur = k;
		int cnt = 0;
		for(int j=0; j<n; j++){
			if((i >> a[j]) % 2 == 1 && cur >= b[a[j]]){
				cur -= b[a[j]];
				cnt++;
			}
		}
		dap = max(dap, cnt);
	}
	cout << dap << endl;
}
