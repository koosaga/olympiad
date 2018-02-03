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

int dp[205][205][205];

int main(){
    for(int i=1; i<=200; i++){
        for(int j=1; j<=200; j++){
            for(int k=1; k<=200; k++){
                if(i == j && i == k){
                    dp[i][j][k] = 1;
                    continue;
                }
                dp[i][j][k] = 1e9;
                for(int l=1; 2*l<=i; l++){
                    dp[i][j][k] = min(dp[l][j][k] + dp[i-l][j][k], dp[i][j][k]);
                }
                for(int l=1; 2*l<=j; l++){
                    dp[i][j][k] = min(dp[i][l][k] + dp[i][j-l][k], dp[i][j][k]);
                }
                for(int l=1; 2*l<=k; l++){
                    dp[i][j][k] = min(dp[i][j][l] + dp[i][j][k-l], dp[i][j][k]);
                }
            }
        }
    }
    int t;
    scanf("%d",&t);
    while(t--){
        int a, b, c;
        scanf("%d %d %d",&a,&b,&c);
        printf("%d\n",dp[a][b][c]);
    }
}