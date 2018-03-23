#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

bool palin(string s){
    string t = s;
    reverse(t.begin(),t.end());
    return s == t;
}

void solve(){
    int n;
    string s[105];
    cin >> n;
    for (int i=0; i<n; i++) {
        cin >> s[i];
    }
    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++){
            if(i == j) continue;
            if(palin(s[i] + s[j])){
                cout << s[i] + s[j] << endl;
                return;
            }
        }
    }
    cout << 0 << endl;
}

int main(){
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}

