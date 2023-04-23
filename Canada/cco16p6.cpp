#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<lint, int> pi;
const int B = 1000;

int n; lint k;
pi v[1005][2005];
int sz[1005], cnt[1005];
lint offset, sum[1005];

pi tmp[1000005];
int ts, maxgrp;

void renew(){
    ts = 0;
    for(int i=0; i<maxgrp; i++){
        for(int j=0; j<sz[i]; j++){
            v[i][j].first += offset;
            if(ts && tmp[ts-1].first == v[i][j].first){
                tmp[ts-1].second += v[i][j].second;
            }
            else tmp[ts++] = v[i][j];
        }
    }
    offset = 0;
    memset(sz, 0, sizeof(sz));
    memset(cnt, 0, sizeof(cnt));
    memset(sum, 0, sizeof(sum));
    int p = 0;
    maxgrp = 0;
    for(int i=0; p < ts; i++){
        for(int j=0; j<B && p < ts; j++){
            cnt[i] += tmp[p].second;
            sum[i] += tmp[p].first * tmp[p].second;
            v[i][sz[i]++] = tmp[p++];
        }
        maxgrp = i+1;
    }
}

void ins(lint x, int c){
    int lst = 0;
    if(maxgrp > 0){
        int s = 0, e = maxgrp-1;
        while(s != e){
            int m = (s+e+1)/2;
            if(v[m][0].first <= x - offset){
                s = m;
            }
            else e = m-1;
        }
        lst = s;
    }
    if(maxgrp < 1000 && (maxgrp == 0 || 
        v[maxgrp-1][sz[maxgrp-1]-1].first <= x - offset)){
        v[maxgrp][0] = pi(x-offset, c);
        sz[maxgrp]++;
        cnt[maxgrp] += c;
        sum[maxgrp] += (x - offset) * c;
        maxgrp++;
        return;
    }
    auto p = lower_bound(v[lst], v[lst] + sz[lst], pi(x - offset, c)) - v[lst];
    for(int j=sz[lst]; j>p; j--){
        v[lst][j] = v[lst][j-1];
    }
    v[lst][p] = pi(x - offset, c);
    sz[lst]++;
    cnt[lst] += c;
    sum[lst] += (x - offset) * c;
    if(sz[lst] > 2000) renew();
}

void add_all(){
    offset++;
}

lint suma(int p){
    lint ret = 0;
    for(int i=0; p; i++){
        if(p >= cnt[i]){
            ret += sum[i] + offset * cnt[i];
            p -= cnt[i];
        }
        else{
            for(int j=0; j<sz[i]; j++){
                ret += (v[i][j].first + offset) * min(p, v[i][j].second);
                p = max(0, p - v[i][j].second);
                if(p == 0) break;
            }
        }
    }
    return ret;
}

void del(int p){
    for(int i=maxgrp-1; p; i--){
        if(p >= cnt[i]){
            p -= cnt[i];
            sz[i] = 0;
            cnt[i] = 0;
            sum[i] = 0;
            maxgrp--;
        }
        else{
            cnt[i] -= p;
            while(p){
                if(p >= v[i][sz[i]-1].second){
                    sum[i] -= v[i][sz[i]-1].first * v[i][sz[i]-1].second;
                    p -= v[i][sz[i]-1].second;
                    sz[i]--;
                }
                else{
                    sum[i] -= v[i][sz[i]-1].first * p;
                    v[i][sz[i]-1].second -= p;
                    p = 0;
                }
            }
        }
    }
}

int main(){
    cin >> n >> k;
    for(int i=1; i<=n; i++){
        int x;
        scanf("%d",&x);
        lint ret = x-1 + suma(x-1);
        lint dp = 0;
        if(ret <= k){
            del(i-x);
            add_all();
            ins(0, i-x);
            dp = k - ret;
        }
        else dp = -1;
        printf("%lld\n", dp);
        ins(dp, 1);
    }
}

