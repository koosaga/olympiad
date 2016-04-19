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
 
struct disj{
    int pa[200000];
    void init(){
        for(int i=0; i<200000; i++) pa[i] = i;
    }
    int find(int x){
        return pa[x] = (pa[x] == x ? x : find(pa[x]));
    }
    bool uni(int p, int q){
        p = find(p);
        q = find(q);
        if(p == q) return 0;
        if(p > q) swap(p, q);
        pa[q] = p; return 1;
    }
}disj;
 
vector<string> ls;
 
bool cmp(string a, string b){
    if(a.size() != b.size()) return a.size() < b.size();
    return a < b;
}
 
int compress(string &s){
    int ret = 0;
    for(auto &i : s){
        ret <<= 2;
        if(i == 'C') ret += 1;
        if(i == 'G') ret += 2;
        if(i == 'T') ret += 3;
    }
    for(int i=s.size()-1; i>=1; i--){
        ret += (1 << (2*i));
    }
    return ret;
}
 
char t[5] = "ACGT";
 
string get(char t){
    if(t == 'A') return "TC";
    if(t == 'C') return "AG";
    if(t == 'G') return "CT";
    return "GA";
}
 
void bktk(string s){
    if(s.size() > 8) return;
    if(s.size() > 0) ls.push_back(s);
    for(int i=0; i<4; i++){
        s.push_back(t[i]);
        bktk(s);
        s.pop_back();
    }
}
 
int code[105];
 
int main(){
    bktk("");
    sort(ls.begin(), ls.end(), cmp);
    disj.init();
    int piv = 0;
    for(auto &i : ls){
        piv++;
        if(i.size() > 7) continue;
        for(int j=0; j<i.size(); j++){
            string nxt = i.substr(0, j) + get(i[j]) + i.substr(j+1, i.size()-j-1);
            int u = compress(nxt);
            disj.uni(piv-1, u);
        }
    }
    int n;
    cin >> n;
    for(int i=0; i<n; i++){
        string s;
        cin >> s;
        string stk;
        for(auto &i : s){
            stk.push_back(i);
            int u = compress(stk);
            stk = ls[disj.find(u)];
        }
        code[i] = compress(stk);
    }
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(disj.find(code[i]) == disj.find(code[j])){
                printf("1");
            }
            else printf("0");
        }
        puts("");
    }
}