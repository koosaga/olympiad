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
 
int n, x[1005], y[1005], l[1005];
 
struct interval{
    int hi, s, e;
}a[1005];
 
vector<pi> rads;
 
int dx[2005];
 
int main(){
    auto cmp = [&](const pi &a, const pi &b){
        return a.first * b.second > b.first * a.second;
    };
    auto same = [&](const pi &a, const pi &b){
        return a.first * b.second == b.first * a.second;
    };
    scanf("%d",&n);
    for(int i=0; i<n; i++){
        scanf("%d %d %d",&x[i],&y[i],&l[i]);
        rads.push_back(pi(x[i] + l[i], y[i]));
        rads.push_back(pi(x[i], y[i] + l[i]));
    }
    sort(rads.begin(), rads.end(), cmp);
    rads.resize(unique(rads.begin(), rads.end(), same) - rads.begin());
    for(int i=0; i<n; i++){
        a[i].hi = x[i] + y[i] + l[i];
        a[i].s = lower_bound(rads.begin(), rads.end(), pi(x[i] + l[i], y[i]), cmp) - rads.begin();
        a[i].e = lower_bound(rads.begin(), rads.end(), pi(x[i], y[i] + l[i]), cmp) - rads.begin();
    }
    sort(a, a+n, [&](const interval &a, const interval &b){
        return a.hi < b.hi;
    });
    int ret = 0;
    for(int i=0; i<n; i++){
        int empty = 0;
        for(int k=a[i].s; k<a[i].e; k++){
            if(dx[k] == 0) empty = 1;
            dx[k] = 1;
        }
        ret += empty;
    }
    printf("%d",ret);
}