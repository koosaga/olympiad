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
 
int n, k;
 
string p[10005], q[10005];
 
int lcp(string &s1, string &s2){
    for(int i=0; i<k; i++){
        if(s1[i] != s2[i]) return i;
    }
    return k;
}
 
int main(){
    cin >> n >> k;
    for(int i=0; i<n; i++){
        string s;
        cin >> s;
        p[i] = s.substr(0, k);
        reverse(s.begin(), s.end());
        q[i] = s.substr(0, k);
    }
    sort(p, p+n);
    sort(q, q+n);
    int ret = n * k * 2;
    for(int i=0; i<n-1; i++){
        ret -= lcp(p[i], p[i+1]) + lcp(q[i], q[i+1]);
    }
    cout << ret;
}