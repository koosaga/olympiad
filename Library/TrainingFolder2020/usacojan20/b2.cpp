#include<bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXN = 1005;

int n, a[MAXN];
int p[MAXN];

bool xopowo(){
	bool chk[MAXN] = {};
	for(int i=1; i<=n; i++){
		if(p[i] <= 0 || p[i] > n) return 0;
		if(chk[p[i]]) return 0;
		chk[p[i]] = 1;
	}
	return 1;
}

int main(){
	freopen("photo.in", "r", stdin);
	freopen("photo.out", "w", stdout);
	cin >> n;
	for(int i=2; i<=n; i++) cin >> a[i];
	for(int i=1; i<=n; i++){
		p[1] = i;
		for(int j=2; j<=n; j++){
			p[j] = a[j] - p[j - 1];
		}
		if(xopowo()){
			for(int i=1; i<=n; i++){
				if(i < n) printf("%d ", p[i]);
				else printf("%d\n", p[i]);
			}
			return 0;
		}
	}
}
