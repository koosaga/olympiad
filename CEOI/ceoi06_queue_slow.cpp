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

struct seg{int s, e;};
bool operator<(seg a, seg b){
    return a.s == b.s ? (a.e < b.e) : (a.s < b.s);
}
bool operator!=(seg a, seg b){
    return a.s != b.s || a.e != b.e;
}
 
vector<seg> segments[500], sorted[500];
int length_sum[500];
 
vector<seg> combined;
 
void reinit(){
    combined.clear();
    for(int i=0; i<500; i++){
        for(auto &j : segments[i]){
            combined.push_back(j);
        }
        segments[i].clear();
        sorted[i].clear();
        length_sum[i] = 0;
    }
    int pt = 0;
    for(int i=0; i<500; i++){
        int quot = ((i+1) * combined.size()) / 500;
        while(pt < quot){
            segments[i].push_back(combined[pt]);
            sorted[i].push_back(combined[pt]);
            length_sum[i] += combined[pt].e - combined[pt].s + 1;
            pt++;
        }
        sort(sorted[i].begin(), sorted[i].end());
    }
}
 
pi l2p(int x){
    int ret = 0;
    for(int i=0; i<500; i++){
        auto p = lower_bound(sorted[i].begin(), sorted[i].end(), (seg){x, (int)2e9});
        if(p == sorted[i].begin()){
            ret += length_sum[i];
            continue;
        }
        p--;
        if(p->s <= x && x <= p->e){
            for(auto j=segments[i].begin(); *j != *p; j++){
                ret += j->e - j->s + 1;
            }
            ret += x - p->s + 1;
            return pi(ret, i);
        }
        else{
            ret += length_sum[i];
        }
    }
    return pi(-1,-1);
}
 
pi p2l(int x){
    for(int i=0; i<500; i++){
        if(x <= length_sum[i]){
            for(auto &j : segments[i]){
                if(x <= j.e - j.s + 1){
                    return pi(j.s - 1 + x, i);
                }
                x -= j.e - j.s + 1;
            }
        }
        x -= length_sum[i];
    }
    return pi(-1,-1);
}
 
void del(int l){
    int p = l2p(l).second;
    int q = 0;
    for(auto &i : segments[p]){
        if(i.s <= l && l <= i.e){
            break;
        }
        q++;
    }
    auto i = segments[p][q];
    segments[p].erase(segments[p].begin() + q);
    if(l+1 <= i.e) segments[p].insert(segments[p].begin() + q, {l+1, i.e});
    if(i.s <= l-1) segments[p].insert(segments[p].begin() + q, {i.s, l-1});
    sorted[p] = segments[p];
    sort(sorted[p].begin(), sorted[p].end());
}
 
void ins(int l, int v){
    int p = l2p(l).second;
    int q = 0;
    for(auto &i : segments[p]){
        if(i.s <= l && l <= i.e){
            break;
        }
        q++;
    }
    auto i = segments[p][q];
    segments[p].erase(segments[p].begin() + q);
    if(l <= i.e) segments[p].insert(segments[p].begin() + q, {l, i.e});
    segments[p].insert(segments[p].begin() + q, {v, v});
    if(i.s <= l-1) segments[p].insert(segments[p].begin() + q, {i.s, l-1});
    sorted[p] = segments[p];
    sort(sorted[p].begin(), sorted[p].end());
}
 
int main(){
    int n, q;
    scanf("%d",&n);
    segments[0].push_back({1, (int)1e9});
    sorted[0].push_back({1, (int)1e9});
    length_sum[0] = 1e9;
    for(int i=0; i<n; i++){
        int a, b;
        scanf("%d %d",&a,&b);
        del(a);
        ins(b, a);
        if(i % 500 == 499){
            reinit();
        }
    }
    reinit();
    scanf("%d",&q);
    while(q--){
        char p[5];
        int x;
        scanf("%s %d",p,&x);
        if(*p == 'P'){
            printf("%d\n",l2p(x).first);
        }
        else{
            printf("%d\n",p2l(x).first);
        }
    }
}