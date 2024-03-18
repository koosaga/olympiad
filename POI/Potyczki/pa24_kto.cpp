#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
using bs = bitset<640>;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    vector<vector<int>> a(2);
    for (int i = 0; i < 2; i++) {
        a[i].resize(12);
        for (int j = 0; j < 18; j++) {
            int x;
            cin >> x;
            a[i][0] += x;
            a[i][11 - x] += 1;
        }
    }
    if (a[0] > a[1])
        cout << "Algosia\n";
    else if (a[0] < a[1])
        cout << "Bajtek\n";
    else
        cout << "remis\n";
}