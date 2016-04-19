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
const int B = 200;
 
int nxt[100005], nxtb[100005], pv[100005];
int a[100005], n, q;
 
int find(int x){
    int p = 0;
    for(int i=0; i<x/B; i++){
        p = nxtb[p];
    }
    for(int i=0; i<x%B; i++){
        p = nxt[p];
    }
    return p;
}
 
int stk[205], sz;
void update(int x){
    for(int i=x; sz < B && i>=0; i=pv[i]){
        stk[sz++] = i;
    }
    for(int i=0; i<B-sz; i++){
        x = nxt[x];
    }
    for(int i=nxt[x]; sz; i=nxt[i]){
        nxtb[stk[--sz]] = i;
    }
}
 
int main(){
    scanf("%d %d",&n,&q);
    for(int i=1; i<=n; i++){
        scanf("%d",&a[i]);
        nxt[i-1] = i;
        pv[i] = i-1;
        if(i >= B) nxtb[i-B] = i;
    }
    pv[0] = -1;
    for(int i=0; i<=n+1; i++){
        nxtb[i] = min(i+B, n+1);
    }
    nxt[n] = n+1;
    nxt[n+1] = n+1;
    pv[n+1] = n;
    while(q--){
        char t[4];
        scanf("%s",t);
        if(*t == 'L'){
            int s, e, x;
            scanf("%d %d %d",&s,&e,&x);
            int p1 = find(s-1);
            int p2 = find(s+x-1);
            int p3 = find(e);
            int n1 = nxt[p1], n2 = nxt[p2], n3 = nxt[p3];
            nxt[p1] = n2;
            nxt[p2] = n3;
            nxt[p3] = n1;
            pv[n1] = p3;
            pv[n2] = p1;
            pv[n3] = p2;
            update(p1);
            update(p2);
            update(p3);
        }
        if(*t == 'R'){
            int s, e, x;
            scanf("%d %d %d",&s,&e,&x);
            x = e - s + 1 - x;
            int p1 = find(s-1);
            int p2 = find(s+x-1);
            int p3 = find(e);
            int n1 = nxt[p1], n2 = nxt[p2], n3 = nxt[p3];
            nxt[p1] = n2;
            nxt[p2] = n3;
            nxt[p3] = n1;
            pv[n1] = p3;
            pv[n2] = p1;
            pv[n3] = p2;
            update(p1);
            update(p2);
            update(p3);
        }
        if(*t == 'P'){
            int k;
            scanf("%d",&k);
            printf("%d\n",a[find(k)]);
        }
    }
}