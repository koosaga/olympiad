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
const int maxv = 1000000;
 
int n;
vector<pi> ph, pg;
 
struct bit{
    int tree[1025], lim = (1<<10);
    void init(){memset(tree,0,sizeof(tree));}
    void add(int x, int v){
        x+=5;
        while(x <= lim){
            tree[x] += v;
            x += x & -x;
        }
    }
    int q(int x){
        x+=5;
        int ret = 0;
        while(x){
            ret += tree[x];
            x -= x & -x;
        }
        return ret;
    }
    int sum(int s, int e){
        return q(e) - q(s-1);
    }
}bit;
 
int main(){
    scanf("%d",&n);
    for(int i=0; i<n; i++){
        int x, y;
        char buf[4];
        scanf("%d %d %s",&x,&y,buf);
        if(buf[0] == 'H'){
            ph.push_back(pi(x,y));
        }
        else{
            pg.push_back(pi(x,y));
        }
    }
    sort(ph.begin(), ph.end());
    sort(pg.begin(), pg.end());
    pi ret(0, -1e9);
    for(int i=0; i<ph.size(); ){
        int e = i, pt = 0, stt = ph[i].first;
        set<int> s1, s2;
        s2.insert(-1);
        s2.insert(1001);
        bit.init();
        while(e < ph.size() && ph[e].first == ph[i].first) e++;
        while(pt < pg.size() && pg[pt].first < ph[i].first) pt++;
        for(int j=i; j<ph.size();){
            int f = j;
            vector<int> vect;
            while(pt < pg.size() && pg[pt].first <= ph[j].first){
                s2.insert(pg[pt++].second);
            }
            while(f < ph.size() && ph[f].first == ph[j].first){
                s1.insert(ph[f].second);
                vect.push_back(ph[f].second);
                bit.add(ph[f].second, 1);
                f++;
            }
            for(auto &i : vect){
                if(s2.find(i) != s2.end()) continue;
                int lowpoint = *--s2.upper_bound(i) + 1;
                int highpoint = *s2.lower_bound(i) - 1;
                //printf("%d, [%d, %d]\n",ph[j].first, lowpoint, highpoint);
                int lowpoint2 = *s1.lower_bound(lowpoint);
                int highpoint2 = *--s1.upper_bound(highpoint);
                //printf("%d, [%d, %d]\n",ph[j].first, lowpoint2,highpoint2);
                ret = max(ret, pi(bit.sum(lowpoint2, highpoint2), -(highpoint2 - lowpoint2) * (ph[j].first - stt)));
                // lowpoint + 1. uppoint - 1 해서 solve.
            }
            j = f;
        }
        i = e;
    }
    printf("%d\n%d",ret.first, -ret.second);
}