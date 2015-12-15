#include <cstdio>
#include <vector>
#include <cstdlib>
#include <algorithm>
using namespace std;
  
void one(vector<int> &s){
    s.push_back(0);
}
  
void two(vector<int> &s){
    s.push_back(1);
}
  
void l(vector<int> &s){
    s.back()--;
}
  
void r(vector<int> &s){
    s.back()++;
}
  
void u(vector<int> &s){
    int r = s.back();
    s.pop_back();
    if(r >= 0){
        s.back() += r/2;
        r %= 2;
    }
    else{
        s.back() += r/2;
        r -= r/2 * 2;
        while(r < 0) s.back()--, r += 2;
    }
}
  
void norm(vector<int> &v){
    for (int i=(int)v.size()-1; i; i--) {
        int r = v[i];
        if(r >= 0){
            v[i-1] += v[i]/2;
            v[i] %= 2;
        }
        else{
            v[i-1] += v[i]/2;
            v[i] -= v[i]/2 * 2;
            while(v[i] < 0) v[i-1]--, v[i] += 2;
        }
    }
}
  
int main(){
    char str1[100005], str2[100005];
    scanf("%s %s",str1,str2);
    vector<int> r1,r2;
    r1.push_back(1);
    r2.push_back(1);
    for (int i=0; str1[i]; i++) {
        if(str1[i] == '1') one(r1);
        if(str1[i] == '2') two(r1);
        if(str1[i] == 'L') l(r1);
        if(str1[i] == 'R') r(r1);
        if(str1[i] == 'U') u(r1);
    }
    for (int i=0; str2[i]; i++) {
        if(str2[i] == '1') one(r2);
        if(str2[i] == '2') two(r2);
        if(str2[i] == 'L') l(r2);
        if(str2[i] == 'R') r(r2);
        if(str2[i] == 'U') u(r2);
    }
    norm(r1);
    norm(r2);
    int res = (int)(r1.size() + r2.size());
    int rr = res;
    int dist = 0;
    for (int i=0; i<r1.size() && i<r2.size() && abs(dist) < 10000000; i++) {
        dist <<= 1;
        dist += r2[i] - r1[i];
        res -= 2;
        rr = min(rr,res + abs(dist));
    }
    printf("%d",rr);
}