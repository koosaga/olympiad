#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include <stack>
#include <queue>
#include <map>
#include <set>
#include <algorithm>
#include <string>
#include <functional>
#include <vector>
#include <numeric>
#include <deque>
#include <bitset>
#include <iostream>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;
const int mod = 1e9 + 9;
 
char s1[1000005], s2[1000005], s3[1000005];
lint p1[1000005], p2[1000005], p3[1000005];
lint dp[1000005][2][2];
 
inline int c2(int x){
	return x * (x-1) / 2;
}
 
inline int up(char a, char b){
	if(a == '?' && b == '?') return 325;
	if(a == '?') return b - 'a';
	if(b == '?') return 'z' - a;
	return a < b ? 1 : 0;
}
 
inline int same(char a, char b){
	if(a == '?' && b == '?') return 26;
	return a == '?' || b == '?' || a == b;
}
 
inline int same3(char a, char b, char c){
	set<int> s;
	s.insert(a); s.insert(b); s.insert(c); s.erase('?');
	if(s.size() == 0) return 26;
	if(s.size() == 1) return 1;
	return 0;
}
 
inline int up3(char a, char b, char c){
	if(b == '?'){
		if(a == '?' && c == '?') return 2600;
		if(a == '?' && c != '?') return c2(c - 'a');
		if(a != '?' && c == '?') return c2('z' - a);
		return max(c - a - 1, 0);
	}
	else{
		return up(a, b) * up(b, c);
	}
}
 
void solve(){
	scanf("%s %s %s",s1, s2, s3);
	int l1 = strlen(s1), l2 = strlen(s2), l3 = strlen(s3);
	int n = max(l1, max(l2, l3));
	for(int i=l1; i<n; i++){
		s1[i] = 'a' - 1;
	}
	for(int i=l2; i<n; i++){
		s2[i] = 'a' - 1;
	}
	for(int i=l3; i<n; i++){
		s3[i] = 'a' - 1;
	}
	for(int i=0; i<=n; i++){
		for(int j=0; j<4; j++){
			dp[i][j/2][j%2] = 0;
		}
	}
	p1[n] = p2[n] = p3[n] = 1;
	for(int i=n-1; i>=0; i--){
		p1[i] = p1[i+1];
		p2[i] = p2[i+1];
		p3[i] = p3[i+1];
		if(s1[i] == '?') p1[i] = (p1[i] * 26) % mod;
		if(s2[i] == '?') p2[i] = (p2[i] * 26) % mod;
		if(s3[i] == '?') p3[i] = (p3[i] * 26) % mod;
	}
	dp[n][0][0] = 1;
	for(int i=n-1; i>=0; i--){
		dp[i][0][0] = p2[i];
		if(s3[i] != 0){
			dp[i][0][1] += 1ll * same(s2[i], s3[i]) * dp[i+1][0][1];
			dp[i][0][1] += 1ll * up(s2[i], s3[i]) * (p2[i+1] * p3[i+1] % mod);
			dp[i][0][1] %= mod;
		}
		if(s1[i] != 0){
			dp[i][1][0] += 1ll * same(s1[i], s2[i]) * dp[i+1][1][0];
			dp[i][1][0] += 1ll * up(s1[i], s2[i]) * (p1[i+1] * p2[i+1] % mod);
			dp[i][1][0] %= mod;
		}
		if(s1[i] != 0 && s3[i] != 0){
			dp[i][1][1] += 1ll * same3(s1[i], s2[i], s3[i]) * dp[i+1][1][1];
			dp[i][1][1] += 1ll * up3(s1[i], s2[i], s3[i]) * ((p1[i+1] * p2[i+1] % mod) * p3[i+1] % mod);
			char rep = -1;
			if(s2[i] == '?' && s1[i] == '?') rep = '?';
			else if(s2[i] == '?' || s1[i] == '?' || s1[i] == s2[i]){
				if(s1[i] != '?') rep = s1[i];
				else rep = s2[i];
			}
			if(rep != -1){
				dp[i][1][1] += 1ll * up(rep, s3[i]) * (dp[i+1][1][0] * p3[i+1] % mod);
			}
			rep = -1;
			if(s2[i] == '?' && s3[i] == '?') rep = '?';
			else if(s2[i] == '?' || s3[i] == '?' || s3[i] == s2[i]){
				if(s3[i] != '?') rep = s3[i];
				else rep = s2[i];
			}
			if(rep != -1){
				dp[i][1][1] += 1ll * up(s1[i], rep) * (dp[i+1][0][1] * p1[i+1] % mod);
			}
			dp[i][1][1] %= mod;
		}
	}
	printf("%lld\n",dp[0][1][1]);
}
 
int main(){
	int t;
	scanf("%d",&t);
	while(t--){
		solve();
	}
}