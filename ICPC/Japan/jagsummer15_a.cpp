#include <bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
using lint = long long;
const int MAXN = 10005;

int E[MAXN], W[MAXN];
char str[MAXN];

int main(){
	int m, n;
	scanf("%d %d",&n,&m);
	for(int i=0; i<m; i++){
		scanf("%s", str + 1);
		for(int j=1; j<=n; j++){
			if(str[j] == 'E') E[j]++;
			else W[j]++;
		}
	}
	for(int i=1; i<=n; i++) E[i] += E[i-1];
	for(int i=n; i; i--) W[i] += W[i+1];
	pi ret(1e9, 1e9);
	for(int i=0; i<=n; i++){
		ret = min(ret, pi(E[i] + W[i+1], i));
	}
	cout << ret.second << " " << ret.second + 1 << endl;
}

