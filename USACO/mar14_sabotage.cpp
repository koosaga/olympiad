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
 
int n, a[100005];
int s[100005], e[100005];
 
bool trial(double x){
    double ret = -1e10;
    for(int i=n; i; i--){
        if(i + 2 <= n){
            ret = max(ret, -e[i+2] + x * (n - (i+2) + 1));
        }
        if(s[i] - x * i <= ret) return 1;
    }
    return 0;
}
int main(){
    scanf("%d",&n);
    for(int i=1; i<=n; i++){
        scanf("%d",&a[i]);
        s[i] = s[i-1] + a[i];
    }
    for(int i=n; i; i--){
        e[i] = e[i+1] + a[i];
    }
    double s = 0, e = 1e9;
    for(int i=0; i<50; i++){
        double m = (s+e)/2;
        if(trial(m)) e = m;
        else s = m;
    }
    printf("%.3f",s);
}