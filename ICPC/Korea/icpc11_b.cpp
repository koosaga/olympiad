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

int t;

int main(){
    int t;
    cin >> t;
    while(t--){
        int a, b, c, ab, bc, ca;
        cin >> a >> b >> c >> ab >> bc >> ca;
        int ret= 0;
        for(int i=0; i<=a; i++){
            // ab
            for(int j=0; j+i<=b; j++){
                // bc
                int k = min(c - j, a - i); // ca
                if(k < 0) continue;
                ret = max(ret, i * ab + j * bc + k * ca);
            }
        }
        cout << ret << endl;
    }
}