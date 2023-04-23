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

lint n, m, k, q;
lint x[2005], y[2005];

struct sweep{
    int s, e, x, dx;
};

vector<sweep> sw1, sw2;
vector<int> posx,posy;

int arr1[8005], arr2[8005];

lint solve(){
    int p1 = 0, p2 = 0;
    lint ret = 0;
    for(int i=0; i<posx.size()-1; i++){
        while(p1 < sw1.size() && sw1[p1].x == posx[i]){
            for(int j=sw1[p1].s; j<sw1[p1].e; j++){
                arr1[j] += sw1[p1].dx;
            }
            p1++;
        }
        while(p2 < sw2.size() && sw2[p2].x == posx[i]){
            for(int j=sw2[p2].s; j<sw2[p2].e; j++){
                arr2[j] += sw2[p2].dx;
            }
            p2++;
        }
        for(int j=0; j<posy.size()-1; j++){
            if(!arr2[j] && arr1[j]){
                ret += 1ll * (posy[j+1] - posy[j]) * (posx[i+1] - posx[i]);
            }
        }
    }
    return ret;
}

int main(){
    cin >> n >> m >> k;
    for(int i=0; i<k; i++) cin >> x[i] >> y[i];
    cin >> q;
    for(int i=0; i<k; i++){
        int minx = (int)max(1ll, x[i] - q);
        int maxx = (int)min(n, x[i] + q);
        int miny = (int)max(1ll, y[i] - q);
        int maxy = (int)min(m, y[i] + q);
        sw1.push_back({minx, maxx+1, miny, 1});
        sw1.push_back({minx, maxx+1, maxy+1, -1});
        if(q > 0){
            q--;
            int minx = (int)max(1ll, x[i] - q);
            int maxx = (int)min(n, x[i] + q);
            int miny = (int)max(1ll, y[i] - q);
            int maxy = (int)min(m, y[i] + q);
            q++;
            sw2.push_back({minx, maxx+1, miny, 1});
            sw2.push_back({minx, maxx+1, maxy+1, -1});
        }
    }
    sort(sw1.begin(), sw1.end(), [&](const sweep &a, const sweep &b){
        return a.x < b.x;
    });
    sort(sw2.begin(), sw2.end(), [&](const sweep &a, const sweep &b){
        return a.x < b.x;
    });
    for(auto &i : sw1){
        posx.push_back(i.x);
        posy.push_back(i.s);
        posy.push_back(i.e);
    }
    for(auto &i : sw2){
        posx.push_back(i.x);
        posy.push_back(i.s);
        posy.push_back(i.e);
    }
    sort(posx.begin(), posx.end());
    sort(posy.begin(), posy.end());
    posx.resize(unique(posx.begin(), posx.end()) - posx.begin());
    posy.resize(unique(posy.begin(), posy.end()) - posy.begin());
    for(auto &i : sw1){
        i.s = lower_bound(posy.begin(), posy.end(), i.s) - posy.begin();
        i.e = lower_bound(posy.begin(), posy.end(), i.e) - posy.begin();
    }
    for(auto &i : sw2){
        i.s = lower_bound(posy.begin(), posy.end(), i.s) - posy.begin();
        i.e = lower_bound(posy.begin(), posy.end(), i.e) - posy.begin();
    }
    cout << solve();
}