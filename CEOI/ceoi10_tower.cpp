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

int n, d;
vector<int> v;

int main(){
    scanf("%d %d",&n,&d);
    for(int i=0; i<n; i++){
        int t;
        scanf("%d",&t);
        v.push_back(t);
    }
    sort(v.begin(), v.end());
    lint ret = 1;
    for(int i=0; i<n; i++){
        ret *= (upper_bound(v.begin(), v.end(), v[i] + d) - v.begin() - i);
        ret %= 1000000009;
    }
    printf("%lld",ret);
}