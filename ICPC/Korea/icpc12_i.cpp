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
typedef pair<int, int> pi;

int n;
string s[15];

void solve(){
    cin >> n;
    int cwin = (1<<n) - 1;
    for(int i=0; i<n; i++){
        cin >> s[i];
    }
    for(int i=0; i<s[0].size(); i++){
        set<int> st;
        for(int j=0; j<n; j++){
            if((cwin >> j) & 1){
                st.insert(s[j][i]);
            }
        }
        if(st.size() == 1 || st.size() == 3) continue;
        if(*st.begin() == 'R'){
            for(int j=0; j<n; j++){
                if((cwin >> j) % 2 && s[j][i] == 'S'){
                    cwin ^= (1<<j);
                }
            }
        }
        else if(*st.rbegin() == 'R'){
            for(int j=0; j<n; j++){
                if((cwin >> j) % 2 && s[j][i] == 'R'){
                    cwin ^= (1<<j);
                }
            }
        }
        else{
            for(int j=0; j<n; j++){
                if((cwin >> j) % 2 && s[j][i] == 'P'){
                    cwin ^= (1<<j);
                }
            }
        }
    }
    set<int> ret;
    for(int i=0; i<n; i++){
        if((cwin >> i) & 1) ret.insert(i+1);
    }
    if(ret.size() == 1) cout << *ret.begin() << endl;
    else puts("0");
}

int main(){
    int t;
    cin >> t;
    while(t--){
        solve();
    }
}