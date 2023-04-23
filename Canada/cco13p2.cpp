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

struct rmq{
    pi tree[1<<21];
    int lim;
    void init(int n, int *a){
        lim = (1 << n);
        for(int i=0; i<lim; i++){
            tree[i + lim] = pi(a[i], i);
        }
        for(int i=lim-1; i; i--){
            tree[i] = max(tree[2*i], tree[2*i+1]);
        }
    }
    void upd(int x, int v){
        x += lim;
        tree[x] = pi(v, x - lim);
        while(x > 1){
            x >>= 1;
            tree[x] = max(tree[2*x], tree[2*x+1]);
        }
    }
}rmq;

int n, m, a[1<<20];

int main(){
    scanf("%d %d",&n,&m);
    for(int i=0; i<(1<<n); i++){
        scanf("%d",&a[i]);
    }
    rmq.init(n, a);
    while(m--){
        char str[5];
        scanf("%s",str);
        if(str[0] == 'W'){
            printf("%d\n",1 + rmq.tree[1].second);
        }
        else if(str[0] == 'R'){
            int a, b;
            scanf("%d %d",&a,&b);
            a--;
            rmq.upd(a, b);
        }
        else{
            int x;
            scanf("%d",&x);
            x--;
            int cnt = 0;
            x += (1<<n);
            pi cmp = rmq.tree[x];
            while(x > 1){
                x >>= 1;
                if(rmq.tree[x] == cmp) cnt++;
                else break;
            }
            printf("%d\n",cnt);
        }
    }
}