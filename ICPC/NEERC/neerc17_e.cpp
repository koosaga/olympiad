#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
const int MAXN = 100005;

int main(){
    multiset<int> s;
    vector<int> w;
    int n;
    cin >> n;
    int cnt = 0;
    for(int i=1; i<=n; i++){
        int x;
        cin >> x;
        if(x > 0) s.insert(x);
        else if(x == 0) cnt++;
        else{
            x = -x;
            if(s.find(x) != s.end()) s.erase(s.find(x));
            else{
                cnt--;
                w.push_back(x);
            }
            if(cnt < 0){
                puts("No");
                return 0;
            }
        }
    }
    for(int i=0; i<cnt; i++) w.push_back(1);
    puts("Yes");
    for(auto &i : w) printf("%d ", i);
}

