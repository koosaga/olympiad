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
typedef pair<int, int> pi;
 
int n;
pi a[200005];
 
int ccw(pi a, pi b){
    lint ret = 1ll * a.first * b.second - 1ll * b.first * a.second;
    return ret > 0 ? 1 : (ret == 0 ? 0 : -1);
}
 
bool outer3(pi a){
    return a.first < 0 || (a.first == 0 && a.second < 0);
}
 
int main(){
    scanf("%d",&n);
    for(int i=0; i<n; i++){
        scanf("%d %d",&a[i].first, &a[i].second);
    }
    sort(a, a+n, [&](const pi &a, const pi &b){
        if(outer3(a) != outer3(b)) return outer3(a) > outer3(b);
        return ccw(a, b) > 0;
    });
    for(int i=0; i<n; i++){
        a[i+n] = a[i];
    }
    lint ret = 1ll * n * (n-1) * (n-2) / 6;
    int e = 1;
    for(int i=0; i<n; i++){
        e = max(e, i+1);
        while(ccw(a[i], a[e]) >= 0) e++;
        ret -= (e - i - 1) * (e - i - 2) / 2;
    }
    for(int i=0; i<n; i++){
        if(outer3(a[i])){
            a[i].first *= -1;
            a[i].second *= -1;
        }
    }
    sort(a, a+n, [&](const pi &a, const pi &b){
        return ccw(a, b) > 0;
    });
    for(int i=0; i<n; ){
        int e = i;
        while(e < n && ccw(a[i], a[e]) == 0) e++;
        if(e - i >= 3) ret += 1ll * (e - i) * (e - i - 1) * (e - i - 2) / 6;
        i = e;
    }
    cout << ret;
}