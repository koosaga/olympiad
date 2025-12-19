#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int n; ll m;
string str[200005];
ll cnt[200005][26];
ll tot[26];

int main(){
    #ifndef LOCAL
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    #endif
    
    cin >> n >> m;
    for(int i=1; i<=n; i++){
        cin >> str[i];
        for(char c: str[i]){
            cnt[i][c-'A']++;
            tot[c-'A']++;
        }
    }

    for(int i=1; i<=n; i++){
        ll ans = 1e18;
        for(int j=0; j<26; j++){
            ll a = tot[j] - cnt[i][j];
            ll b = cnt[i][j];
            
            ll mn = 1e18;
            if(a==0 && b>0) mn = -1;
            else if(a==0 && b==0) mn = 1e18;
            else if(m*a - b >= 0){
                mn = m - (a+b-1)/a;
            }
            else mn = -1;
            ans = min(ans, mn);
        }

        cout << (ans < 0 ? -1 : ans) << " ";
    }
}