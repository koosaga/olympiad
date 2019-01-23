#include <bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
using lint = long long;
const int mod = 1e9 + 7;
const int MAXN = 100005;

char str[MAXN];
vector<int> stk;

int main(){
    cin >> str;
    int ret = 0;
    for(int i=0; str[i]; i++){
        if(str[i] == '('){
            stk.push_back(i);
        }
        if(str[i] == ')'){
            int l = stk.back();
            stk.pop_back();
            if(count(str + l, str + i + 1, '*')){
                ret++;
            }
        }
    }
    cout << ret << endl;
}
