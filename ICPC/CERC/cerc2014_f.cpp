#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using llf = long double;
using pi = pair<int, int>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXN = 1000005;
const int mod = 1e9 + 9;
 
char s1[MAXN], s2[MAXN], s3[MAXN];
lint p1[MAXN], p2[MAXN], p3[MAXN];
lint dp[MAXN][2][2];
 
inline int up(char a, char b){
    if(a == '?' && b == '?') return 325;
    if(a == '?') return max(0, b - 'a');
    if(b == '?') return 'z' - a;
    return a < b ? 1 : 0;
}
 
inline int same(char a, char b){
    if(a == '?' && b == '?') return 26;
    if(a == 'a' - 1 && b == '?') return 0;
    if(b == 'a' - 1 && a == '?') return 0;
    return a == '?' || b == '?' || a == b;
}
 
inline int same3(char a, char b, char c){
    set<int> s;
    s.insert(a); s.insert(b); s.insert(c);
    if(s.count('?')){
    	if(sz(s) >= 3) return 0;
    	if(sz(s) == 1) return 26;
    	if(s.count('a' - 1)) return 0;
    	return 1;
	}
	return sz(s) == 1;
}
 
inline int up3(char a, char b, char c){
    if(b == '?'){
    	int ret = 0;
    	for(int b = 'a'; b <= 'z'; b++){
    		ret += up(a, b) * up(b, c);
		}
		return ret;
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
    s1[n] = s2[n] = s3[n] = 0;
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
    for(int i=n-1; i>=0; i--){
        {
            dp[i][0][1] += 1ll * same(s2[i], s3[i]) * dp[i+1][0][1];
            dp[i][0][1] += 1ll * up(s2[i], s3[i]) * (p2[i+1] * p3[i+1] % mod);
            dp[i][0][1] %= mod;
        }
        {
            dp[i][1][0] += 1ll * same(s1[i], s2[i]) * dp[i+1][1][0];
            dp[i][1][0] += 1ll * up(s1[i], s2[i]) * (p1[i+1] * p2[i+1] % mod);
            dp[i][1][0] %= mod;
        }
        {
            dp[i][1][1] += 1ll * same3(s1[i], s2[i], s3[i]) * dp[i+1][1][1];
            dp[i][1][1] += 1ll * up3(s1[i], s2[i], s3[i]) * ((p1[i+1] * p2[i+1] % mod) * p3[i+1] % mod);
            char rep = -1;
            if(s2[i] == '?' && s1[i] == '?') rep = '?';
            else if(s2[i] == '?' || s1[i] == '?' || s1[i] == s2[i]){
                if(s1[i] != '?') rep = s1[i];
                else rep = s2[i];
            }
            if(rep != -1 && rep != 'a' - 1){
                dp[i][1][1] += 1ll * up(rep, s3[i]) * (dp[i+1][1][0] * p3[i+1] % mod);
            }
            rep = -1;
            if(s2[i] == '?' && s3[i] == '?') rep = '?';
            else if(s2[i] == '?' || s3[i] == '?' || s3[i] == s2[i]){
                if(s3[i] != '?') rep = s3[i];
                else rep = s2[i];
            }
            if(rep != -1 && rep != 'a' - 1){
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
