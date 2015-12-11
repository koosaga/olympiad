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
#include <utility>
#include <bitset>
#include <iostream>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;
 
char s1[10005], s2[1005];
int fail[1005];
 
int dp[10005][1005];
int fail_lnk[1005][26];
 
int f(int x, int y){
    if(s2[y] == 0) return 1e9;
    if(s1[x] == 0) return 0;
    if(~dp[x][y]) return dp[x][y];
    int ret = f(x+1, y) + 1;
    if(s1[x] == s2[y]){
        ret = min(ret, f(x+1, y+1));
    }
    else{
        int nxt = fail_lnk[y][s1[x] - 'a'];
        if(s2[nxt] == s1[x]) ret = min(ret, f(x+1, nxt + 1));
        else ret = min(ret, f(x+1, 0));
    }
    return dp[x][y] = ret;
}
 
int main(){
    memset(dp,-1,sizeof(dp));
    scanf("%s %s",s1, s2);
    for(int i=1; s2[i]; i++){
        for(int j=0; s2[i+j]; j++){
            if(s2[i+j] != s2[j]) break;
            fail[i+j] = max(fail[i+j], j+1);
        }
    }
    for(int i=0; s2[i]; i++){
        for(int j=0; j<26; j++){
            int p = i;
            while(p && s2[p] != 'a' + j){
                p = fail[p-1];
            }
            fail_lnk[i][j] = p;
        }
    }
    printf("%d",f(0,0));
}