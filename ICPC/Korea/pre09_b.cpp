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

lint x, k, t;

int main(){
    int t;
    scanf("%d",&t);
    while(t--){
        int n, a[10], b[10];
        scanf("%d",&n);
        for(int i=0; i<n; i++){
            scanf("%d",&a[i]);
            if(a[i] % 2 == 1) a[i]++;
        }
        int cnt = 0;
        while(1){
            if(*max_element(a,a+n) == *min_element(a,a+n)) break;
            memset(b,0,sizeof(b));
            for(int i=0; i<n; i++){
                b[(i+1)%n] += a[i] / 2;
                b[i] += (a[i] + 1) / 2;
            }
            for(int i=0; i<n; i++){
                if(b[i] % 2 == 1) b[i]++;
            }
            cnt++;
            memcpy(a, b, sizeof(a));
        }
        printf("%d\n",cnt);
    }
}