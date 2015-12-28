#include <cstdio>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
using namespace std;
typedef long long lint;
typedef pair<int,lint> pi;
 
int n;
 
vector<int> graph[200005];
int deg[200005];
 
int piv;
int cycle_num[200005];
int get_cycle[200005];
int vis[200005];
pi cycle_ret[200005];
 
long long freq[200005];
 
void label_graph(){
    queue<int> q;
    for (int i=1; i<=n; i++) {
        if(deg[i] == 1){
            q.push(i);
        }
    }
    while (!q.empty()) {
        int x = q.front();
        q.pop();
        deg[x] = 0;
        for (int &i : graph[x]){
            if(deg[i]){
                deg[i]--;
                if(deg[i] == 1){
                    q.push(i);
                }
            }
        }
    }
    for (int i=1; i<=n; i++) {
        if(deg[i]){
            q.push(i);
            break;
        }
    }
    while (!q.empty()) {
        int x = q.front();
        q.pop();
        cycle_num[x] = ++piv;
        get_cycle[cycle_num[x]] = x;
        for (int &i : graph[x]){
            if(deg[i] && !cycle_num[i]){
                q.push(i);
                break;
            }
        }
    }
    for (int i=1; i<=n; i++) {
        if(cycle_num[i]){
            q.push(i);
            vis[i] = 1;
            while (!q.empty()) {
                int x = q.front();
                q.pop();
                for (int &i : graph[x]){
                    if(!vis[i]){
                        vis[i] = 1;
                        q.push(i);
                    }
                }
            }
        }
    }
}
 
bool cmp(pi a, pi b){
    return a.first > b.first;
}
 
pi f(int x, int pa){
    vector<pi> sub;
    for (int &i : graph[x]){
        if(i == pa) continue;
        if(cycle_num[i]) continue;
        pi t = f(i,x);
        t.first++;
        sub.push_back(t);
    }
    sort(sub.begin(),sub.end(),cmp);
    if(sub.size() == 0) return pi(0,1);
    if(sub.size() == 1){
        freq[sub[0].first] += sub[0].second;
        return sub[0];
    }
    if(sub[0].first == sub[1].first){
        pi t(sub[0].first,0);
        for (int i=0; i<sub.size(); i++) {
            if(sub[0].first == sub[i].first) t.second += sub[i].second;
        }
        long long sum = 1ll * t.second * t.second;
        for (int i=0; i<sub.size(); i++) {
            if(sub[0].first == sub[i].first) sum -= 1ll * sub[i].second * sub[i].second;
        }
        sum /= 2;
        freq[t.first * 2] += sum;
        return t;
    }
    int low_sub = 0;
    for (int i=1; i<sub.size(); i++) {
        if(sub[1].first == sub[i].first) low_sub += sub[i].second;
    }
    freq[sub[0].first + sub[1].first] += 1ll * low_sub * sub[0].second;
    return sub[0];
}
 
map<int,long long> mp;
 
int main(){
    scanf("%d",&n);
    for (int i=0; i<n; i++) {
        int s,e;
        scanf("%d %d",&s,&e);
        graph[s].push_back(e);
        graph[e].push_back(s);
        deg[s]++;
        deg[e]++;
    }
    label_graph();
    for (int i=1; i<=n; i++) {
        if(cycle_num[i]){
            pi t = f(i,0);
            cycle_ret[cycle_num[i]] = t;
            freq[t.first] += t.second;
        }
    }
    for (int j=2; j<=piv/2; j++) {
        int lng = cycle_ret[j].first + j;
        mp[lng] += cycle_ret[j].second;
    }
    for (int i=1; i<=piv; i++) {
        if(i + piv/2 <= piv){
            int j = i + piv / 2;
            int lng = cycle_ret[j].first + j;
            mp[lng] += cycle_ret[j].second;
        }
        if(mp.empty()) continue;
        auto x = mp.rbegin();
        freq[cycle_ret[i].first - i + (x->first)] += (x -> second) * cycle_ret[i].second;
        int lng = cycle_ret[i+1].first + i+1;
        mp[lng] -= cycle_ret[i+1].second;
        if(mp[lng] == 0) mp.erase(lng);
    }
    mp.clear();
    for (int j=1 + (piv+1)/2; j<=piv; j++) {
        int lng = cycle_ret[j].first + piv - j;
        mp[lng] += cycle_ret[j].second;
    }
    for (int i=1; i<=piv && !mp.empty(); i++) {
        auto x = mp.rbegin();
        freq[cycle_ret[i].first + i + (x->first)] += (x->second) * cycle_ret[i].second;
        int j = i + (piv + 1)/2;
        int lng = cycle_ret[j].first + piv - j;
        mp[lng] -= cycle_ret[j].second;
        if(mp[lng] == 0) mp.erase(lng);
    }
    for (int i=n; i; i--) {
        if(freq[i]){
            printf("%lld",freq[i]);
            return 0;
        }
    }
}