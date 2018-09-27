#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> pi;
const int MAXN = 1005;

vector<pi> v;

struct level_structure{
    vector<int> v;
    int fr = 0;
    int sum_odd = 0, sum_even = 0;
    int current_odd_gamma = 0;
    int removed_odd_gamma = 0;
    int current_even_gamma = 0;
    int removed_even_gamma = 0;
    priority_queue<pi, vector<pi>, greater<pi> > pqOdd, pqEven; // valid till fr <= i.second
    void push(int x){
        if(v.size() & 1){
            sum_odd += x;
            if(v.size() >= 2){
                current_odd_gamma += 2 * v[v.size() - 1] - x - v[v.size() - 2];
                pqOdd.emplace(current_odd_gamma, v.size() - 2);
            }
        }
        else{
            sum_even += x;
            if(v.size() >= 2){
                current_even_gamma += 2 * v[v.size()-1] - x - v[v.size() - 2];
                pqEven.emplace(current_even_gamma, v.size() - 2);
            }
        }
        v.push_back(x);
    }
    void pop(){
        if(fr & 1){
            sum_odd -= v[fr];
            if(fr + 2 < v.size()) removed_odd_gamma += 2 * v[fr+1] - v[fr+2] - v[fr]; 
        }
        else{
            sum_even -= v[fr];
            if(fr + 2 < v.size()) removed_even_gamma += 2 * v[fr+1] - v[fr+2] - v[fr]; 
        }
        while(!pqOdd.empty() && pqOdd.top().second < fr) pqOdd.pop();
        while(!pqEven.empty() && pqEven.top().second < fr) pqEven.pop();
        fr++; 
    }
    int query(){
        if(fr % 2 == v.size() % 2) return abs(sum_even - sum_odd);
        int ans = 0;
        if(v.size() & 1) ans = sum_even - sum_odd - v[fr];
        else ans = sum_odd - sum_even - v[fr];
        if(fr & 1){
            if(!pqOdd.empty()) ans += min(0, pqOdd.top().first - removed_odd_gamma);
        }
        else{
            if(!pqEven.empty()) ans += min(0, pqEven.top().first - removed_even_gamma);
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



