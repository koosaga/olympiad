#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;
const int MAXN = 1050000;

int n;
char s[MAXN], t[MAXN];
int nxt[MAXN][26][2][2];

int main(){
    scanf("%s", s);
    n = strlen(s);
    for(int i=0; i<104; i++){
        nxt[n][i/4][(i&2)>>1][i%2] = n;
    }
    for(int i=n-1; i>=0; i--){
        for(int j=0; j<26; j++){
            for(int k=0; k<2; k++){
                nxt[i][j][k][0] = nxt[i+1][j][k][0];
                nxt[i][j][k][1] = nxt[i+1][j][k][1];
                char ch = (k ? 'A' : 'a') + j;
                if(s[i] == ch){
                    nxt[i][j][k][i%2] = i;
                }
            }
        }
    }
    int q; scanf("%d",&q);
    while(q--){
        scanf("%s", t);
        int l = strlen(t);
        int dp[2][2][2];
        memset(dp, 0x3f, sizeof(dp));
        dp[0][0][0] = 0;
        for(int i=0; i<l; i++){
            memset(dp[(i+1)%2], 0x3f, sizeof(dp[(i+1)%2]));
            int b1 = !!isupper(t[i]);
            int b2 = (b1 ? (t[i] - 'A') : (t[i] - 'a'));
            for(int j=0; j<2; j++){
                for(int k=0; k<2; k++){
                    int qq = dp[i%2][j][k];
                    if(qq > 1e9) continue;
                    // case 1. next update not changes caps
                    {
                        int pos = nxt[qq][b2][(b1+j)%2][qq%2];
                        if(pos < n) dp[(i+1)%2][j][k] = min(dp[(i+1)%2][j][k], pos + 1);
                    }
                    // case 2. next update change caps
                    {
                        int pos = nxt[qq][b2][(b1+j+1)%2][(qq+1)%2];
                        if(pos < n) dp[(i+1)%2][1-j][k] = min(dp[(i+1)%2][1-j][k], pos + 1);
                    }
                }
            }
        }
        bool ok = 0;
        for(int i=0; i<4; i++){
            if(dp[l%2][i/2][i%2] <= n) ok = 1;
        }
        puts(ok ? "YES" : "NO");
    }
}
