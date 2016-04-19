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
 
int n, a[5005], b[5005];
 
double trial(double x){
    double ret = -1e9;
    for(int i=0; i<n-1; i++){
        double m = 1.0 * (b[i+1] - b[i]) / (a[i+1] - a[i]);
        double y = (b[i] - m * a[i]);
        ret = max(ret, m * x + y);
    }
    return ret;
}
int main(){
    scanf("%d",&n);
    for(int i=0; i<n; i++){
        scanf("%d %d",&a[i],&b[i]);
    }
    double s = 0, e = 1e6;
    for(int i=0; i<100; i++){
        double m1 = (2 * s + e) / 3;
        double m2 = (s + 2 * e) / 3;
        if(trial(m1) <= trial(m2)) e = m2;
        else s = m1;
    }
    printf("%.2f",trial(s));
}