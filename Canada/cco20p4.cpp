#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using llf = long double;
using pi = pair<int, int>;
const int MAXN = 2005;

int n;
char str[MAXN][MAXN];

void solve(vector<int> v){
    deque<int> dq;
    for(auto &i : v){
        if(sz(dq) < 2){
            dq.push_back(i);
            continue;
        }
        if(str[i][dq[0]] == 'R'){
            dq.push_front(i);
            if(str[dq.back()][dq.front()] == 'R'){
                int w = dq.back();
                dq.pop_back();
                dq.push_front(w);
            }
        }
        else{
            {
                int w = dq.front();
                dq.push_back(w);
                dq.pop_front();
            }
            dq.push_back(i);
            if(str[dq.back()][dq.front()] == 'R'){
                dq.pop_back();
                dq.push_front(i);
            }
        }
    }
    if(dq.back() == v.back()) reverse(all(dq));
    if(dq[1] == v.back()) rotate(dq.begin(), dq.begin() + 1, dq.end());
    printf("%d\n", n);
    for(auto &i : dq) printf("%d ", i + 1);
    puts("");
}

int main(){
    scanf("%d",&n);
    for(int i=1; i<n; i++) scanf("%s", str[i]);
    for(int i=0; i<n; i++){
        for(int j=i+1; j<n; j++) str[i][j] = str[j][i];
    }
    for(int i=0; i<n; i++){
        vector<int> v(n);
        iota(all(v), 0);
        swap(v[i], v[n - 1]);
        solve(v);
    }
}
