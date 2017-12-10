#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
const int MAXN = 4005;

int n, m;
pi a[MAXN], b[MAXN];
int mat[MAXN];
lint dp[2][MAXN];
int tra[MAXN][MAXN];

int main(){
    cin >> n;
    for(int i=1; i<=n; i++){
        cin >> a[i].first;
        a[i].second = i;
    }
    cin >> m;
    for(int i=1; i<=m; i++){
        cin >> b[i].first;
        b[i].second = i;
    }
    sort(a+1, a+n+1);
    sort(b+1, b+m+1);
    memset(dp, 0x3f, sizeof(dp));
    dp[0][0] = 0;
    for(int i=1; i<=n; i++){
        memset(dp[i%2], 0x3f, sizeof(dp[i%2]));
        for(int j=1; j<=m; j++){
            if(dp[i%2][j] > dp[(i-1)%2][j-1] + abs(a[i].first - b[j].first)){
                dp[i%2][j] = dp[(i-1)%2][j-1] + abs(a[i].first - b[j].first);
                tra[i][j] = 1;
            }
            if(dp[i%2][j] > dp[(i-1)%2][j] + abs(a[i].first - b[j].first)){
                dp[i%2][j] = dp[(i-1)%2][j] + abs(a[i].first - b[j].first);
                tra[i][j] = 2;
            }
        }
    }
    cout << dp[n%2][m] << endl;
    int pos = m;
    for(int j=n; j; j--){
        mat[a[j].second] = b[pos].second;
        if(tra[j][pos] == 1) pos--;
    }
    for(int i=1; i<=n; i++) cout << mat[i] << " ";
}
