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
 
int main(){
    scanf("%d",&n);
    int cnt = 0;
    for(int i=0; i<n; i++){
        lint t;
        scanf("%lld",&t);
        int q = (int)sqrt(t);
        while(1ll * (q+1) * (q+1) <= t) q++;
        if(1ll * q * q == t) printf("1 ");
        else printf("0 ");
    }
}