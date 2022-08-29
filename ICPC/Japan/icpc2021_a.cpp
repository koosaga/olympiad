#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<int, int>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int mod = 1e9 + 7;

int main(){ 
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n; double r;
    cin >> n >> r;
    double ret = n * (4.0 / 3 * acos(-1) * r * r * r);
    vector<double> x(n), y(n), z(n);
    for(int i = 0; i < n; i++){
        cin >> x[i] >> y[i] >> z[i];
    }
    for(int i = 0; i < n; i++){
        double dx = x[(i + 1) % n] - x[i];
        double dy = y[(i + 1) % n] - y[i];
        double dz = z[(i + 1) % n] - z[i];
        double d = sqrt(dx*dx+dy*dy+dz*dz);
        ret -= 2.0 / 3 * acos(-1) * (r - d/2) * (r - d/2) * (2*r+d/2);
    }
    cout << setprecision(69) << ret << endl;
}
