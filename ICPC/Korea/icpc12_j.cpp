#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
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

vector<pi> pack(vector<pi> &a, vector<pi> &b){
    vector<pi> ret;
    int p = 0, cmin = 1e9;
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    for(auto &i : a){
        while(p < b.size() && b[p].first <= i.first){
            cmin = min(cmin, b[p].second);
            p++;
        }
        if(cmin < 1e9) ret.emplace_back(i.first, i.second + cmin);
    }
    p = 0, cmin = 1e9;
    for(auto &i : b){
        while(p < a.size() && a[p].first <= i.first){
            cmin = min(cmin, a[p].second);
            p++;
        }
        if(cmin < 1e9) ret.emplace_back(i.first, i.second + cmin);
    }
    return ret;
}

int n, w[1005], v[1005], a[2005];

vector<pi> dfs(int s, int e){
    if(s == e){
        vector<pi> ret;
        ret.emplace_back(w[a[s]], v[a[s]]);
        ret.emplace_back(v[a[s]], w[a[s]]);
        return ret;
    }
    int leaf = 0, nleaf = 0, cutp = -1;
    for(int j=e-1; j>=s; j--){
        if(a[j] < 0) nleaf++;
        else leaf++;
        if(leaf - 1 == nleaf){
            cutp = j;
            break;
        }
    }
    vector<pi> p1 = dfs(s, cutp-1);
    vector<pi> p2 = dfs(cutp, e-1);
    if(a[e] == -2){
        for(auto &i : p1){
            swap(i.first, i.second);
        }
        for(auto &i : p2){
            swap(i.first, i.second);
        }
    }
    vector<pi> ret = pack(p1, p2);
    if(a[e] == -2){
        for(auto &i : ret){
            swap(i.first, i.second);
        }
    }
    return ret;
}

int main(){
    int t;
    scanf("%d",&t);
    while(t--){
        int n;
        scanf("%d",&n);
        for(int i=1; i<=n; i++){
            scanf("%d %d",&w[i], &v[i]);
            if(w[i] > v[i]) swap(w[i], v[i]);
        }
        char buf[11];
        for(int i=1; i<=2*n-1; i++){
            scanf("%s",buf);
            if(buf[0] == 'V'){
                a[i] = -2;
            }
            else if(buf[0] == 'H'){
                a[i] = -1;
            }
            else{
                sscanf(buf, "%d", &a[i]);
            }
        }
        vector<pi> sol = dfs(1, 2*n-1);
        lint ret = 1e18;
        for(auto &i : sol){
            ret = min(ret, 1ll * i.first * i.second);
        }
        printf("%lld\n",ret);
    }
}