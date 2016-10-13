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
  
int n, m;
int arr[2005][2005];
  
int main(){
    scanf("%d\n",&n);
    m =n;
    for(int i=0; i<n; i++){
        char buf[4005];
        fgets(buf, 4005, stdin);
        for(int j=0; j<m; j++){
            if(buf[2*j] == '1') arr[i][j] = 0;
            else arr[i][j] = 1;
        }
    }
    int tmp[2005] = {}, ret = 0;
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            if(arr[i][j]) tmp[j]++;
            else tmp[j] = 0;
        }
        stack<int> stk;
        for(int j=0; j<=m; j++){
            while(!stk.empty() && tmp[stk.top()] >= tmp[j]){
                int t = stk.top();
                stk.pop();
                ret = max(ret, (j - 1 - (stk.empty() ? -1 : stk.top())) * tmp[t]);
            }
            stk.push(j);
        }
    }
    printf("%d\n",ret);
}