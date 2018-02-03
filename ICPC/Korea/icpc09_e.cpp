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
typedef pair<lint, int> pi;

int main(){
    int t;
    cin >> t;
    while(t--){
        int n, k;
        scanf("%d %d",&n,&k);
        for(int i=2; i>=0; i--){
            int lst = i;
            for(int j=i+1; j<=n; j++){
                lst = (lst + k) % j;
            }
            printf("%d ",lst + 1);
        }
        puts("");
    }
}