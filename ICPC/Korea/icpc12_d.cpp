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

int arr[305][305], piv;
pi toi[50005];

int main(){
    for(int i=2; i<300; i++){
        for(int j=1; j<i; j++){
            arr[j][i-j] = ++piv;
            toi[piv] = pi(j,i-j);
        }
    }
    int t;
    scanf("%d",&t);
    while(t--){
        int x, y;
        scanf("%d %d",&x,&y);
        int px = toi[x].first + toi[y].first;
        int py = toi[x].second + toi[y].second;
        printf("%d\n",arr[px][py]);
    }
}