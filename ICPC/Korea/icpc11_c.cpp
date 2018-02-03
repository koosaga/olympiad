#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int inf = 1e9;

char s1[5005], s2[5005];

int low1[26], high1[26], low2[26], high2[26], mp[256];
int dp[2][5005];

void solve(){
    memset(low1,0x3f,sizeof(low1));
    memset(low2,0x3f,sizeof(low2));
    memset(high1,0,sizeof(high1));
    memset(high2,0,sizeof(high2));
    scanf("%s %s",s1+1,s2+1);
    for (int i=1; s1[i]; i++) {
        low1[s1[i]-'A'] = min(low1[s1[i]-'A'],i);
        high1[s1[i]-'A'] = max(high1[s1[i]-'A'],i);
    }
    for (int i=1; s2[i]; i++) {
        low2[s2[i]-'A'] = min(low2[s2[i]-'A'],i);
        high2[s2[i]-'A'] = max(high2[s2[i]-'A'],i);
    }
    dp[0][0] = 0;
    for (int i=0; i == 0 || s1[i]; i++) {
        for (int j=0; j == 0 || s2[j]; j++) {
            int ret = 0;
            for (int k=0; k<26; k++) {
                if((low1[k] <= i || low2[k] <= j) && (i < high1[k] || j < high2[k])){
                    ret++;
                }
            }
            if(i == 0 && j == 0) continue;
            else dp[i%2][j] = min(j?dp[i%2][j-1]:inf,i?dp[(i-1)%2][j]:inf) + ret;
        }
    }
    printf("%d\n",dp[(int)strlen(s1+1)%2][(int)strlen(s2+1)]);
}

int main(){
    int t;
    scanf("%d",&t);
    while (t--) {
        solve();
    }
}