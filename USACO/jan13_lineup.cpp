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
 
int n, k, a[100005];
vector<int> v;
 
int cnt[100005];
multiset<int> s;
 
int main(){
    scanf("%d %d",&n,&k);
    for(int i=0; i<n; i++){
        scanf("%d",&a[i]);
        v.push_back(a[i]);
    }
    sort(v.begin(), v.end());
    v.resize(unique(v.begin(), v.end()) - v.begin());
    for(int i=0; i<n; i++){
        a[i] = lower_bound(v.begin(), v.end(), a[i]) - v.begin();
    }
    int ret = 0;
    int pt = 0;
    for(int i=0; i<n; i++){
        while(pt < n){
            if(cnt[a[pt]]){
                s.erase(s.find(cnt[a[pt]]));
                s.insert(cnt[a[pt]] + 1);
            }
            else{
                if(s.size() >= k+1) break;
                s.insert(1);
            }
            cnt[a[pt]]++;
            pt++;
        }
        ret = max(ret, *s.rbegin());
        s.erase(s.find(cnt[a[i]]));
        cnt[a[i]]--;
        if(cnt[a[i]]) s.insert(cnt[a[i]]);
    }
    printf("%d",ret);
}