#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;

char str[1000005];
int s[1000005][3], n;

bool ok(int l, int r){
	int v[3];
	for(int i=0; i<3; i++){
		v[i] = s[r][i] - s[l-1][i];
	}
	for(int i=0; i<3; i++){
		for(int j=0; j<i; j++){
			if(v[i] == v[j] && v[i]) return false;
		}
	}
	return true;
}

int main(){
	scanf("%d %s",&n,str+1);
	for(int i=1; i<=n; i++){
		for(int j=0; j<3; j++) s[i][j] = s[i-1][j];
		if(str[i] == 'C') s[i][0]++;
		if(str[i] == 'B') s[i][1]++;
		if(str[i] == 'S') s[i][2]++;
	}
	int ans = 0;
	for(int i=1; i<=min(3, n); i++){
		for(int j=n; j>=i; j--){
			if(ok(i, j)){
				ans = max(ans, j - i + 1);
				break;
			}
		}
	}
	for(int j=max(n-2, 1); j<=n; j++){
		for(int i=1; i<=j; i++){
			if(ok(i, j)){
				ans = max(ans, j - i + 1);
				break;
			}
		}
	}
	cout << ans << endl;
}
