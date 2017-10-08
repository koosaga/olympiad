#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <limits.h>
#include <math.h>
#include <time.h>
#include <iostream>
#include <functional>
#include <numeric>
#include <algorithm>
#include <stack>
#include <queue>
#include <deque>
#include <vector>
#include <string>
#include <bitset>
#include <map>
#include <set>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;

int n, k;
int a[22];

set<vector<int>> ret;
vector<int> trav;

void solve(vector<int> &cnd){
    int fst = -1;
    vector<int> l, r;
    for(auto &i : cnd){
        if(fst == -1){
            fst = i;
        }
        else if(a[fst] < a[i]){
            r.push_back(i);
        }
        else{
            l.push_back(i);
        }
    }
    if(l.size()){
        trav.push_back(-1);
        solve(l);
        trav.push_back(1);
    }
    if(r.size()){
        trav.push_back(-2);
        solve(r);
        trav.push_back(2);
    }
}

int main(){
    cin >> n >> k;
    for(int i=1; i<=n; i++){
        trav.clear();
        vector<int> cnd;
        for(int j=0; j<k; j++){
            cin >> a[j];
            cnd.push_back(j);
        }
        solve(cnd);
        ret.insert(trav);
    }
    cout << ret.size();
}