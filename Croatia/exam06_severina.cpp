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
 
char str[300005];
int n;
 
int trie[400005][26], piv, term[400005];
int dp[300005];
 
int main(){
    scanf("%s",str+1);
    n = strlen(str+1);
    int q;
    scanf("%d",&q);
    while(q--){
        char str[105];
        scanf("%s",str);
        int l = strlen(str) - 1, p = 0;
        for(int i=l; i>=0; i--){
            if(!trie[p][str[i] - 'a']){
                trie[p][str[i] - 'a'] = ++piv;
            }
            p = trie[p][str[i] - 'a'];
        }
        term[p] = 1;
    }
    dp[0] = 1;
    for(int i=1; i<=n; i++){
        int p = 0;
        for(int j=i; j; j--){
            p = trie[p][str[j] - 'a'];
            if(term[p]) dp[i] += dp[j-1];
            if(p == 0) break;
        }
        dp[i] %= 1337377;
    }
    printf("%d",dp[n]);
}