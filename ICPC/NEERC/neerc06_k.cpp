#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pi;

int main(){
    string s, t;
    cin >> s >> t;
    int ret = s.size() + t.size();
    for(int i=1-(int)t.size(); i<(int)s.size(); i++){
        int ok = 1;
        for(int j=0; j<t.size(); j++){
            if(i + j < s.size() && i + j >= 0){
                if(s[i+j] - '0' + t[j] - '0' > 3){
                    ok = 0;
                }
            }
        }
        if(ok){
            int e = max(t.size() + i, s.size());
            int s = min(i, 0);
            ret = min(ret, e - s);
        }
    }
    cout << ret;
}
