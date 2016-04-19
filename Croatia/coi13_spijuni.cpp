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
typedef pair<int,int> pi;
const int mod = 1e9 + 7;
 
struct edg{
    int s, e, x;
    bool operator<(const edg &b)const{
        return x < b.x;
    }
};
 
struct disj{
    int pa[1005];
    void init(int n){
        for(int i=0; i<=n; i++){
            pa[i] = i;
        }
    }
    int find(int x){
        return pa[x]= (pa[x] == x ? x : find(pa[x]));
    }
    bool uni(int p, int q){
        p = find(p), q = find(q);
        if(p == q) return 0;
        pa[q] = p; return 1;
    }
}disj;
 
int n;
vector<edg> v;
 
int main(){
    scanf("%d",&n);
    for(int i=1; i<=n; i++){
        for(int j=1; j<=n; j++){
            int t;
            scanf("%d",&t);
            if(i < j) v.push_back({i, j, t});
        }
    }
    for(int i=1; i<=n; i++){
        int t;
        scanf("%d",&t);
        v.push_back({0, i, t});
    }
    sort(v.begin(), v.end());
    disj.init(n);
    int ret = 0;
    for(auto &i : v){
        if(disj.uni(i.s, i.e)){
            ret += i.x;
        }
    }
    cout << ret;
}