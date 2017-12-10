#include <bits/stdc++.h>
using namespace std;
typedef long long lint;

int n;
char str[333333];

int code(char t){
    if(t <= 'Z' && t >= 'A') return t - 'A';
    return t - 'a' + 26;
}

unordered_map<lint, int> cnt;

int main(){
    cin >> n;
    cin >> str;
    lint msk = 0;
    lint ret = 0;
    for(int i=0; i<n; i++){
        cnt[msk]++;
        msk ^= (1ll << code(str[i]));
        ret += cnt[msk];
        for(int j=0; j<52; j++){
            if(cnt.find(msk ^ (1ll << j)) == cnt.end()) continue;
            ret += cnt[msk ^ (1ll << j)];
        }
    }
    cout << ret;
}
