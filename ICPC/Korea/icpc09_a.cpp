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

void manip(vector<int> &ducci){
    vector<int> v;
    for(int i=0; i<ducci.size(); i++){
        v.push_back(abs(ducci[i] - ducci[(i + 1) % ducci.size()]));
    }
    ducci = v;
}

int main(){
    int t;
    scanf("%d",&t);
    while(t--){
        int n;
        set<vector<int> > s;
        vector<int> ducci;
        scanf("%d",&n);
        while(n--){
            int t;
            scanf("%d",&t);
            ducci.push_back(t);
        }
        while(1){
            if(s.find(ducci) != s.end()){
                puts("LOOP");
                break;
            }
            if(count(ducci.begin(), ducci.end(), 0) == ducci.size()){
                puts("ZERO");
                break;
            }
            s.insert(ducci);
            manip(ducci);
        }
    }
}