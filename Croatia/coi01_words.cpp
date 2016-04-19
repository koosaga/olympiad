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
 
int n;
string s[17];
int dp[1<<16][16];
 
int f(int b, int x){
    if(~x && ~dp[b][x]) return dp[b][x];
    int ret = 0;
    for(int j=0; j<n; j++){
        if((b >> j) % 2 == 0 && (x == -1 || s[x].back() == s[j].front())){
            ret = max(ret, f(b|(1<<j), j) + (int)s[j].size());
        }
    }
    return dp[b][x] = ret;
}
 
int main(){
    cin >> n;
    for(int i=0; i<n; i++) cin >> s[i];
    memset(dp, -1, sizeof(dp));
    printf("%d",f(0, -1));
}