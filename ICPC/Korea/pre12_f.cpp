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

int main(){
    int t;
    scanf("%d\n",&t);
    while(t--){
        int n, a[105], ret[105] = {};
        bool empty[105] = {};
        scanf("%d",&n);
        for(int i=0; i<n; i++){
            scanf("%d",&a[i]);
        }
        int bad = 0;
        for(int i=n-1; i>=0; i--){
            for(int j=1; j<=n; j++){
                if(!empty[j]){
                    if(a[i] == 0){
                        ret[i] = j;
                        empty[j] = 1;
                        break;
                    }
                    a[i]--;
                }
            }
            if(!ret[i]){
                bad = 1;
                puts("IMPOSSIBLE");
                break;
            }
        }
        for(int i=0; i<n; i++){
            if(!bad) printf("%d ",ret[i]);
        }
        if(!bad) puts("");
    }
}