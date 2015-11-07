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

int a[100005], rev[100005], n;

struct bit{
    int tree[100005], lim;
    void init(int n){
        lim = n;
    }
    void add(int x, int v){
        while(x <= lim){
            tree[x] += v;
            x += x & -x;
        }
    }
    int q(int x){
        int ret = 0;
        while(x){
            ret += tree[x];
            x -= x & -x;
        }
        return ret;
    }
}bit;

int main(){
    scanf("%d",&n);
    for(int i=1; i<=n; i++){
        scanf("%d",&a[i]);
        rev[a[i]] = i;
    }
    lint cur = 0;
    bit.init(n);
    for(int i=1; i<=n; i++){
        bit.add(a[i], 1);
        cur += i - bit.q(a[i]);
    }
    lint ret = cur;
    for(int i=n; i; i--){
        cur -= n + 1 - 2 * rev[i];
        ret = min(ret, cur);
    }
    printf("%lld",ret);
}