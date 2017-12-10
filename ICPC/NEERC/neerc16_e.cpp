#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;
const int mod = 1e9 + 7;
const int MAXN = 100005;
const int offset = 50000;

map<int, int> mp;
vector<pi> v, query;
lint loc[MAXN], lod[MAXN];

void add_rect(int s, int e, lint x){
    s *= -1;
    e *= -1;
    auto l = lower_bound(query.begin(), query.end(), pi(s, -1)) - query.begin();
    auto r = lower_bound(query.begin(), query.end(), pi(e, -1)) - query.begin();
    loc[0] += x * (e - s);
    loc[l] -= x * (e - s);
    loc[l] += x * e;
    loc[r] -= x * e;
    lod[l] -= x;
    lod[r] += x;
}

void get_event(){
    stack<pi> stk;
    int cur = 0;
    for(int i=0; i<v.size(); i++){
        if(v[i].second > 0){
            while(v[i].second > 0 && !stk.empty()){
                auto tp = stk.top();
                stk.pop();
                if(tp.second >= v[i].second){
                    add_rect(cur + v[i].second, cur, v[i].first - tp.first);
                    tp.second -= v[i].second;
                    cur += v[i].second;
                    v[i].second = 0;
                    if(tp.second) stk.push(tp);
                }
                else{
                    v[i].second -= tp.second;
                    add_rect(cur + tp.second, cur, v[i].first - tp.first);
                    cur += tp.second;
                }
            }
            cur += v[i].second;
        }
        else{
            cur += v[i].second; 
            int upd = -v[i].second;
            upd = min(upd, -cur);
            if(upd > 0) stk.push(pi(v[i].first, upd));
        }
    }
}

int main(){
    freopen("expect.in", "r", stdin);
    freopen("expect.out", "w", stdout);
    int n, q;
    char buf[5];
    scanf("%d %d",&n,&q);
    for(int i=0; i<n; i++){
        int x, y;
        scanf("%s %d %d",buf,&x,&y);
        if(*buf == '-') mp[x] -= y;
        else mp[x] += y;
    }
    int tot = 0;
    for(auto &i : mp){
        if(i.second != 0) v.push_back(pi(i.first, i.second));
        tot += i.second;
    }
    mp.clear();
    tot = min(tot, 0);
    if(tot < 0){
        v.insert(v.begin(), pi(0, -tot));
    }
    query.resize(q);
    for(int i=0; i<q; i++){
        scanf("%d",&query[i].first);
        query[i].second = i;
        query[i].first += tot;
    }   
    sort(query.begin(), query.end());
    get_event();
    int fuck[MAXN];
    for(int i=0; i<query.size(); i++){
        fuck[query[i].second] = i;
    }
    sort(query.begin(), query.end(), [&](const pi &a, const pi &b){
        return a.second < b.second;
    });
    for(int i=1; i<query.size(); i++){
        loc[i] += loc[i-1];
        lod[i] += lod[i-1];
    }
    for(auto &i : query){
        if(i.first < 0) puts("INFINITY");
        else printf("%lld\n", loc[fuck[i.second]] + lod[fuck[i.second]] * i.first);
    }
}
