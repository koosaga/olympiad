#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;

int t, n, a[1005];

int main(){
    cin >> t;
    while(t--){
        cin >> n;
        int cnt = 0;
        for(int i=0; i<n; i++){
            cin >> a[i];
            for(int j=0; j<i; j++){
                if(a[j] <= a[i]) cnt++;
            }
        }
        cout << cnt << endl;
    }
}
