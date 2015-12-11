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
typedef pair<int, lint> pi;
 
int n, t;
pi a[100005];
 
multiset<lint> s;
 
int main(){
    scanf("%d %d",&n,&t);
    for(int i=0; i<n; i++){
        int x, y;
        scanf("%d %d",&x,&y);
        a[i] = pi(x, 1ll * y * t + x);
    }
    sort(a, a+n);
    for(int i=0; i<n; i++){
        int e = i;
        while(e < n && a[i].first == a[e].first) e++;
        for(int j=e-1; j>=i; j--){
            auto t = s.lower_bound(a[j].second);
            if(t != s.begin()){
                t--;
                s.erase(t);
            }
        }
        for(int j=i; j<e; j++){
            s.insert(a[j].second);
        }
        i = e-1;
    }
    printf("%d",s.size());
}