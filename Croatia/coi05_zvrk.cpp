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
 
int main(){
    lint a, b;
    scanf("%lld %lld",&a,&b);
    lint prev = 0;
    lint ret = 0;
    for(int i=0; i<55; i++){
        lint cur = (1ll << i);
        ret += (cur - prev) * (b/cur - (a-1) / cur);
        prev = cur;
    }
    printf("%lld",ret);
}