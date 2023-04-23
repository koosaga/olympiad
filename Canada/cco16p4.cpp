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

int n, g;

map<string, int> ls;

int main(){
    cin >> n >> g;
    for(int i=0; i<g; i++){
        string s[15];
        for(int j=0; j<n; j++){
            cin >> s[j];
        }
        for(int j=n-1; j; j--){
            for(int k=n-1; k; k--){
                if(s[j][k] == 'R'){
                    s[j][k] = 'W';
                    s[j-1][k] = 'R' + 'W' - s[j-1][k];
                    s[j-1][k-1] = 'R' + 'W' - s[j-1][k-1];
                    s[j][k-1] = 'R' + 'W' - s[j][k-1];
                }
            }
        }
        string t;
        for(int i=0; i<n; i++){
            t.push_back(s[0][i]);
            t.push_back(s[i][0]);
        }
        ls[t]++;
    }
    lint ret = 0;
    for(auto &i : ls){
        ret += 1ll * (i.second) * (i.second- 1) / 2;
    }
    cout << ret;
}