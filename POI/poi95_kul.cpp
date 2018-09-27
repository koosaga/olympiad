#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> pi;
const int MAXN = 1005;

vector<pi> v;

struct deque{
    vector<int> v;
    int fr = 0;
    void push(int x){ v.push_back(x); }
    void pop(){ fr++; }
    int query(){
        int ans = 0;
        for(int j=fr; j+1<v.size(); j+=2){
            ans += v[j+1] - v[j];
        }
        if(fr % 2 != v.size() % 2){
            int gamma = ans;
            for(int j=(int)v.size()-3; j>=fr; j-=2){
                gamma += v[j+2] - 2 * v[j + 1] + v[j];
                ans = min(ans, gamma);
            }
        }
        return ans;
    }
}ds[3 * MAXN];

int prv_ans[3 * MAXN];

int main(){
    int n;
    scanf("%d",&n);
    for(int i=0; i<n; i++){
        int k;
        scanf("%d",&k);
        while(k--) v.emplace_back(i, -1);
        v.emplace_back(i, +1);
    }
    v.resize(2 * v.size());
    copy(v.begin(), v.begin() + v.size() / 2, v.begin() + v.size() / 2);
    for(int i=v.size()/2; i<v.size(); i++) v[i].first += n;
    int f = n;
    for(auto &i : v){
        int assign_floor = max(f, f + i.second);
        f += i.second;
        i.second = assign_floor;
    }
    int ans = 1e9;
    int p1 = 0, p2 = 0, cur = 0;
    for(int i=0; i<n; i++){
        while(p2 < v.size() && v[p2].first < i+n){
            cur -= prv_ans[v[p2].second];
            ds[v[p2].second].push(v[p2].first);
            cur += (prv_ans[v[p2].second] = ds[v[p2].second].query());
            p2++;
        }
        while(p1 < v.size() && v[p1].first < i){
            cur -= prv_ans[v[p1].second];
            ds[v[p1].second].pop();
            cur += (prv_ans[v[p1].second] = ds[v[p1].second].query());
            p1++;
        }
        ans = min(ans, cur);
    }
    cout << ans << endl;
}

