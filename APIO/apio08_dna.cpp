#include <cstdio>
#include <cstring>
typedef long long lint;
 
char str[50005], mpp[5] = "ACGT";
int mp[128],n,k;
lint r, dp[50005][4][10];
 
lint f(int x, int c, int t){
    if(t >= k) return 0;
    if(x >= n) return 1;
    if(~dp[x][c][t]) return dp[x][c][t];
    if(str[x] != 'N'){
        return dp[x][c][t] = f(x+1,mp[str[x]],t + (c > mp[str[x]]));
    }
    else{
        lint r = 0;
        for (int i=0; i<4; i++) {
            r += f(x+1,i,t + (c > i));
        }
        return dp[x][c][t] = r;
    }
}
 
void track(int x, int c, int t, lint r){
    if(x >= n || t >= k) return;
    if(str[x] != 'N'){
        putchar(str[x]);
        track(x+1,mp[str[x]],t + (c > mp[str[x]]),r);
    }
    else{
        lint tra = 0, btra = 0;
        for (int i=0; i<4; i++) {
            tra += f(x+1,i,t+(c>i));
            if(tra >= r){
                putchar(mpp[i]);
                track(x+1,i,t+(c>i),r-btra);
                break;
            }
            btra = tra;
        }
    }
}
 
 
int main(){
    memset(dp,-1,sizeof(dp));
    mp['A'] = 0;
    mp['C'] = 1;
    mp['G'] = 2;
    mp['T'] = 3;
    scanf("%d %d %lld %s",&n,&k,&r,str);
    if(str[0] != 'N') track(0,mp[str[0]],0,r);
    else track(0,0,0,r);
}