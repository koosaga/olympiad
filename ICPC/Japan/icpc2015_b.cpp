#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;

int n, a[505];
double pos[505];

int main(){
    cin >> n;
    double dap = 0;
    for(int i=1; i<=n; i++){
        cin >> a[i];
        pos[i] = a[i];
        for(int j=1; j<i; j++){
            pos[i] = max(pos[i], pos[j] + sqrt(4 * a[i] * a[j]));
        }
        dap = max(dap, pos[i] + a[i]);
    }
    printf("%.10f", dap);
}