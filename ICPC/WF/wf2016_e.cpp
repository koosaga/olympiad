#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>
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

lint y, b;

bool check(lint x){
    vector<lint> v, w;
    for(lint i = y; i; i /= x){
        v.push_back(i % x);
    }
    for(lint i = b; i; i /= 10){
        w.push_back(i % 10);
    }
    reverse(v.begin(), v.end());
    reverse(w.begin(), w.end());
    if(v.size() < w.size()) return 0;
    if(v.size() > w.size()) return 1;
    return v >= w;
}

lint get_bound(){
    lint s = 10, e = 2e18;
    while(s != e){
        lint m = (s+e+1)/2;
        if(check(m)) s = m;
        else e = m-1;
    }   
    return s;
}

bool ok(lint a, lint b){
    return log(a) + log(b) < log(2) + 18 * log(10);
}

lint trial(vector<int> &v, lint x){
    lint base = 1;
    lint ret = 0;
    for(int i=0; i<v.size(); i++){
        if(ok(v[i], base)){
            ret+= 1ll * v[i] * base;
        }
        else return 2e18;
        if(i == (int)v.size() - 1 || ok(base, x)) base *= x;
        else return 2e18;
    }
    return ret;
}

lint check2(int x){
    vector<int> poly;
    for(int i=x; i; i/=10){
        poly.push_back(i % 10);
    }
    if(poly.size() == 2){
        lint p = (y - poly[0]);
        if(p < 0 || p % poly[1] != 0){
            return -1;
        }
        p /= poly[1];
        if(p < 10) return -1;
        return p;
    }
    int s = 0, e = 1e9 + 10000;
    while(s != e){
        int m = (s+e)/2;
        if(trial(poly, m) >= y) e = m;
        else s = m+1;
    }
    if(trial(poly, s) != y) return -1;
    if(s < 10) return -1;
    return s;
}

int main(){
    cin >> y >> b;
    lint t = get_bound();
    lint ret = 10;
    for(int i=10; i<=50000 && i <= t; i++){
        bool bad = 0;
        for(lint j=y; j; j/=i){
            if(j%i >= 10){
                bad = 1;
                break;
            }
        }
        if(!bad){
            ret = i;
        }
    }
    for(lint i=b; i<10000; i++){
        lint calc = check2(i);
        if(calc != -1 || calc <= t){
            ret = max(ret, calc);
        }
    }
    cout << ret;
}