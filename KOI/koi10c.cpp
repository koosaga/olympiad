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
pi a[100005];
vector<int> vy;
vector<pi> l1, l2;
 
bool crs(pi a, pi b){
    return (a.first < b.first) != (a.second < b.second);
}
 
bool right(pi a, pi b){
    return a.first < b.first && a.second < b.second;
}
int solve(){
    int p1 = 0, p2 = 0, ret = 0;
    while(p1 < l1.size()){
        if(p1 != l1.size()) ret++; // 일단 p1에 한점
        if(p2 != l2.size()) ret++; // 현재 p2에 한점
        p1++;
        p2++;
        if(p2 < l2.size() && right(l1[p1], l2[p2])){
            while(p1 < l1.size() && !crs(l1[p1], l2[p2])) p1++;
            if(p1 == l1.size()) break;
        }
        else{
            p2--;
            while(p2 < l2.size() && !(crs(l1[p1], l2[p2]) && crs(l1[p1-1], l2[p2]))) p2++;
            if(p2 == l2.size()) break; // 못넘어감.
            p2++;
        }
    }
    return ret;
}
 
int main(){
    scanf("%d",&n);
    for(int i=0; i<n; i++){
        scanf("%d %d",&a[i].first, &a[i].second);
        vy.push_back(a[i].second);
    }
    sort(a, a+n);
    sort(vy.begin(), vy.end());
    for(int i=0; i<n; i++){
        a[i].first = i;
        a[i].second = lower_bound(vy.begin(), vy.end(), a[i].second) - vy.begin();
    }
    int cmax = -1;
    int e = 0, ret = 0;
    for(int i=0; i<n; i++){
        if(cmax < a[i].second){
            cmax = a[i].second;
            l1.push_back(a[i]);
        }
        else{
            l2.push_back(a[i]);
        }
        e = max(e, a[i].second);
        if(i == e){
            ret = max(ret, solve());
            swap(l1, l2);
            ret = max(ret, solve());
            l1.clear();
            l2.clear();
        }
    }
    cout << ret;
}