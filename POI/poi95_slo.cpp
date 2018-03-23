#include <bits/stdc++.h>
using namespace std;
const int MAXN = 222;
const int inf = 1e6;

int n, dp[MAXN][MAXN];
string s, t[MAXN];

int main(){
    cin >> s >> n;
    dp[0][0] = 1;
    for(int i=1; i<=n; i++){
        cin >> t[i];
        for(int j=0; j+t[i].size() <= s.size(); j++){
            if(s.substr(j, t[i].size()) == t[i]){
                dp[i][j + t[i].size()] += dp[i-1][j];
            }
        }
        for(int j=0; j<=s.size(); j++) dp[i][j] = min(dp[i-1][j] + dp[i][j], inf);
    }
    if(dp[n][s.size()] == 0){
        puts("NIE");
        return 0;
    }
    cout << dp[n][s.size()] << endl;
    int pos = s.size();
    vector<int> v;
    for(int j=n; j; j--){
        if(t[j].size() <= pos && dp[j-1][pos - t[j].size()] && s.substr(pos - t[j].size(), t[j].size()) == t[j]){
            pos -= t[j].size();
            v.push_back(j);
        }
    }
    reverse(v.begin(), v.end());
    for(auto &i : v) cout << i << endl;
}

