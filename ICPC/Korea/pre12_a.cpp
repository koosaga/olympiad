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

int n, m;
int a[1000005], b[1000005];
vector<int> v;

bool trial(int x, int y){
    long long ret = 0;
    for(int i=0; i<n; i++){
        ret += 1ll * m * abs(x - a[i]);
        ret -= 1ll * m * abs(y - a[i]);
    }
    for(int i=0; i<m; i++){
        ret += 1ll * n * abs(x - b[i]);
        ret -= 1ll * n * abs(y - b[i]);
    }
    return ret <= 0;
}

int main(){
    int t;
    scanf("%d",&t);
    while(t--){
        scanf("%d %d",&n,&m);
        for(int i=0; i<n; i++){
            scanf("%d",&a[i]);
            v.push_back(a[i]);
        }
        for(int i=0; i<m; i++){
            scanf("%d",&b[i]);
            v.push_back(b[i]);
        }
        sort(v.begin(), v.end());
        int s = 0, e = v.size() - 1;
        while(s != e){
            int m = (s+e)/2;
            if(trial(v[m],v[m+1])) e = m;
            else s = m+1;
        }
        printf("%d.0\n",v[s]);
        v.clear();
    }
}