#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using pi = pair<int, int>;
using lint = long long;
const int MAXN = 200005;
const int mod = 998244353;

struct bit{
    int tree[MAXN];
    void add(int x, int v){
        for(int i=x; i<MAXN; i+=i&-i) tree[i] += v;
    }
    int query(int x){
        int ret = 0;
        for(int i=x; i; i-=i&-i) ret += tree[i];
        return ret;
    }
}bit;

int n, a[MAXN];

priority_queue<pi> pq;
vector<int> vec[MAXN];

int main(){
    scanf("%d",&n);
    for(int i=1; i<=n; i++){
        scanf("%d",&a[i]);
        vec[a[i]].push_back(i);
        bit.add(i, 1);
    }
    lint ret = 0;
    for(int i=n; i; i--){
        for(auto &j : vec[i]){
            pq.emplace(j, bit.query(j));
        }
        if(sz(pq) == 0){
            puts("-1");
            return 0;
        }
        ret += i - pq.top().second;
        bit.add(pq.top().first, -1);
        pq.pop();
    }
    cout << ret << endl;
}
