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
int a[100005], c[100005];

lint trial(int p){
    lint ret = 0;
    for(int i=0; i<n; i++){
        ret += 1ll * c[i] * abs(p - a[i]);
    }
    return ret;
}

int main(){
    int t;
    scanf("%d",&t);
    while(t--){
        scanf("%d",&n);
        for(int i=0; i<n; i++){
            scanf("%d",&a[i]);
        }
        for(int i=0; i<n; i++){
            scanf("%d",&c[i]);
        }
        int s = 0, e = 1e8;
        while(s != e){
            int m = (s+e)/2;
            if(trial(m) <= trial(m+1)) e = m;
            else s = m+1;
        }
        printf("%d\n",s);
    }
}