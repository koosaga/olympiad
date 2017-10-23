#include <cstdio>
#include <set>
#include <cstring>
using namespace std;
 
int dp[22][22][22][22];
int n,m;
char str[22][22];
 
int solve(int sx, int ex, int sy, int ey){
    if(~dp[sx][ex][sy][ey]) return dp[sx][ex][sy][ey];
    set<int> s;
    for (int i=sx; i<=ex; i++) {
        for (int j=sy; j<=ey; j++) {
            if(str[i][j] == 'X') continue;
            int ret = solve(sx,i-1,sy,j-1) ^ solve(i+1,ex,sy,j-1) ^ solve(sx,i-1,j+1,ey) ^ solve(i+1,ex,j+1,ey);
            s.insert(ret);
        }
    }
    if(s.empty() || *s.begin() != 0){
        return dp[sx][ex][sy][ey] = 0; //
    }
    s.insert(1e9);
    auto it = ++s.begin();
    for (auto &i : s){
        if(*it - i != 1){
            return dp[sx][ex][sy][ey] = i + 1;
        }
        it++;
    }
    return -1;
}
 
int main(){
    memset(dp,-1,sizeof(dp));
    scanf("%d %d",&n,&m);
    for (int i=1; i<=n; i++) {
        scanf("%s",str[i]+1);
    }
    puts(solve(1,n,1,m)?"First":"Second");
}