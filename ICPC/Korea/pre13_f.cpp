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

int score[105][105];
int submit[105];
int last_submit[105];

void solve(){
    int n, k, t, q;
    scanf("%d %d %d %d",&n,&k,&t,&q);
    memset(score,0,sizeof(score));
    memset(submit,0,sizeof(submit));
    memset(last_submit,0x3f,sizeof(last_submit));
    while(q--){
        int i, j, s;
        scanf("%d %d %d",&i,&j,&s);
        score[i][j] = max(score[i][j], s);
        submit[i]++;
        last_submit[i] = q;
    }
    int cnt = 0;
    for(int i=1; i<=n; i++){
        for(int j=2; j<=k; j++){
            score[i][1] += score[i][j];
        }
    }
    for(int i=1; i<=n; i++){
        if(score[i][1] > score[t][1]){
            cnt++;
        }
        else if(score[i][1] == score[t][1]){
            if(submit[i] < submit[t]){
                cnt++;
            }
            else if(submit[i] == submit[t]){
                if(last_submit[i] >= last_submit[t]){
                    cnt++;
                }
            }
        }
    }
    printf("%d\n",cnt);
}

int main(){
    int t;
    scanf("%d",&t);
    while(t--){
        solve();
    }
}