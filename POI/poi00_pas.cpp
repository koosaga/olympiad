#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;

int a[3];
int dp[1005];

int main(){
	for(int i=0; i<3; i++) cin >> a[i];
	for(int i=1; i<=1000; i++){
		set<int> s;
		for(int j=0; j<i; j++){
			for(int k=0; k<3; k++){
				if(a[k] + j <= i){
					s.insert(dp[j] ^ dp[i-j-a[k]]);
				}
			}
		}
		for(int j=0; ; j++){
			if(s.find(j) == s.end()){
				dp[i] = j;
				break;
			}
		}
	}
	int q;
	cin >> q;
	while(q--){
		int x;
		cin >> x;
		if(dp[x]) puts("1");
		else puts("2");
	}
}
