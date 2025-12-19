#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int n;
int sz[100005];
ll L[100005], R[100005];
vector<ll> doors[100005];
vector<pair<ll, ll> > interval[100005];

int cur[100005];
set<pair<ll, int> > rightEnds, leftEnds;

int main(){
    #ifndef LOCAL
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    #endif
    
    cin >> n;
    for(int i=1; i<=n; i++){
        cin >> sz[i] >> L[i] >> R[i];
        for(int j=0; j<sz[i]; j++){
            ll x; cin >> x;
            doors[i].push_back(x);
        }
        sz[i]++;
    }

    for(int i=1; i<=n; i++){
        ll l = L[i], r = R[i];
        for(ll d: doors[i]) r -= d;
        interval[i].push_back({l, r});
        for(ll d: doors[i]){
            l += d, r += d;
            interval[i].push_back({l, r});
        }

        leftEnds.insert({interval[i][0].first, i});
        rightEnds.insert({interval[i][0].second, i});
        cur[i] = 0;
    }

    ll ans = 0;
    while(true){
        {
            ll l = leftEnds.rbegin()->first, r = rightEnds.begin()->first;
            ans = max(ans, r-l);

            // cout << "Current gap: " << l << " " << r << "\n";
            // for(int i=1; i<=n; i++){
            //     cout << "Interval " << i << ": " << interval[i][cur[i]].first << " " << interval[i][cur[i]].second << '\n';
            // }
        }

        // 다음 구간으로 넘어간다
        int idx = rightEnds.begin()->second;
        rightEnds.erase(rightEnds.begin());
        leftEnds.erase({interval[idx][cur[idx]].first, idx});

        cur[idx]++;
        if(cur[idx] == sz[idx]) break;

        leftEnds.insert({interval[idx][cur[idx]].first, idx});
        rightEnds.insert({interval[idx][cur[idx]].second, idx});
    }

    cout << ans;
}