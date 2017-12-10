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

char str[100];
bool vis[51];
int n;

int getlim(int x){
    if(x <= 9) return x;
    return (x - 9) / 2 + 9;
}

int rnum(int s, int e){
    if(!str[e]) return 1e8;
    if(s == e) return str[s] - '0';
    return 10 * (str[s] - '0') + str[e] - '0';
}
void dfs(int x, int c, int *stk){
    if(c == n){
        for(int i=0; i<c; i++){
            printf("%d ",stk[i]);
        }
        exit(0);
    }
    int num = rnum(x, x);
    if(num && num <= n && !vis[num]){
        vis[num] =1;
        stk[c] = num;
        dfs(x+1, c+1, stk);
        vis[num] = 0;
    }
    num = rnum(x, x+1);
    if(num && num <= n && !vis[num]){
        vis[num] =1;
        stk[c] = num;
        dfs(x+2, c+1, stk);
        vis[num] = 0;
    }
}


int main(){
    scanf("%s",str);
    n = getlim(strlen(str));
    int stk[100] = {};
    dfs(0, 0, stk);
}