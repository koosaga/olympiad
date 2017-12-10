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
#include <bitset>
#include <iostream>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;

int n;
char str[10000005];
bool vis[10000005];
int main(){
    scanf("%d",&n);
    for(int i=0; i<n; i++){
        char buf[4];
        scanf("%s",buf);
        str[i] = *buf;
    }
    for(int i=1; i<7; i++){
        for(int j=0; j+i-1<n; j++){
            int t = 0;
            for(int k=0; k<i; k++){
                t = 10 * t + (str[j+k] - '0');
            }
            vis[t] = 1;
        }
    }
    for(int i=0; ; i++){
        if(!vis[i]){
            printf("%d",i);
            return 0;
        }
    }
}