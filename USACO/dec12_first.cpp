#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include <stack>
#include <queue>
#include <map>
#include <set>
#include <algorithm>
#include <string>
#include <functional>
#include <vector>
#include <numeric>
#include <deque>
#include <utility>
#include <bitset>
#include <iostream>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;
 
string a[30005];
int n;
 
int trie[300005][26], piv;
bool term[300005];
 
bool adj[26][26];
vector<string> str;
 
int main(){
    cin >> n;
    for(int i=0; i<n; i++){
        cin >> a[i];
        int p = 0;
        for(auto &j : a[i]){
            if(!trie[p][j - 'a']){
                trie[p][j - 'a'] = ++piv;
            }
            p = trie[p][j - 'a'];
        }
        term[p] = 1;
    }
    int cnt = 0;
    for(int i=0; i<n; i++){
        memset(adj,0,sizeof(adj));
        int p = 0;
        int fnd_term = 0;
        for(auto &j : a[i]){
            if(term[p]) fnd_term = 1;
            for(int k=0; k<26; k++){
                if(trie[p][k] && k != j - 'a'){
                    adj[j - 'a'][k] = 1; // j is better
                }
            }
            p = trie[p][j - 'a'];
        }
        if(fnd_term){
            continue;
        }
        for(int j=0; j<26; j++){
            for(int k=0; k<26; k++){
                for(int l=0; l<26; l++){
                    adj[k][l] |= (adj[k][j] & adj[j][l]);
                }
            }
        }
        bool bad = 1;
        for(int i=0; i<26; i++){
            if(adj[i][i]) bad = 0;
        }
        if(bad) str.push_back(a[i]);
    }
    printf("%d\n",str.size());
    for(auto &i : str){
        puts(i.c_str());
    }
}