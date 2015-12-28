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
 
map<int, int> mx, my;
int n;
pi a[300005];
 
int main(){
    scanf("%d",&n);
    for(int i=0; i<n; i++){
        scanf("%d %d",&a[i].first, &a[i].second);
        mx[a[i].first]++;
        my[a[i].second]++;
    }
    lint ret = 0;
    for(int i=0; i<n; i++){
        ret += 1ll * (mx[a[i].first]-1) * (my[a[i].second]-1);
    }
    cout << ret;
}
