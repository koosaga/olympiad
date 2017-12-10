#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;
const int mod = 1e9 + 513;

int trie[150005][26], num[150005], piv, term[150005];
int nxt[150005];
char str[55];

lint h(vector<int> &nxt){
    lint ret = 0;
    for(auto &i : nxt) ret = mod * ret + i;
    return ret;
}

int main(){
    int n;
    scanf("%d",&n);
    for(int i=0; i<n; i++){
        scanf("%s", str);
        int p = 0;
        for(int j=0; str[j]; j++){
            if(!trie[p][str[j] - 'a']){
                trie[p][str[j] - 'a'] = ++piv;
            }
            p = trie[p][str[j] - 'a'];
        }
        term[p] = 1;
    }
    for(int i=0; i<=piv; i++) num[i] = i+1;
    int prv = -1, p2 = -1;
    while(1){
        prv = p2;
        p2 = 0;
        map<lint, int> mp;
        for(int i=0; i<=piv; i++){
            vector<int> nxt;
            for(int j=0; j<26; j++){
                if(trie[i][j]) nxt.push_back(num[trie[i][j]]);
                else nxt.push_back(-1);
            }
            nxt.push_back(term[i]);
            lint p = h(nxt);
            if(mp.find(p) == mp.end()) mp[p] = ++p2;
            ::nxt[i] = mp[p];
        }
        if(prv == p2) break;
        memcpy(num, nxt, sizeof(nxt));
    }
    cout << prv;
}
