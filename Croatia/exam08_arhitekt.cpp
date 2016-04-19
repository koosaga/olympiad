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
 
int n;
char str[100005];
 
int dx[8] = {0, 1, 1, 1, 0, -1, -1, -1};
int dy[8] = {1, 1, 0, -1, -1, -1, 0, 1};
vector<pi> point;
int main(){
    scanf("%d %s",&n,str);
    int px = 0, py = 0;
    point.push_back(pi(px, py));
    for(int i=0; i<n; i++){
        for(int j=0; j<2; j++){
            px += dx[str[i] - '0'];
            py += dy[str[i] - '0'];    
            point.push_back(pi(px, py));
        }
    }
    set<pi> vertex;
    set<pair<pi, pi>> edge;
    for(int i=0; i<point.size() - 1; i++){
        vertex.insert(point[i]);
        auto t = make_pair(point[i], point[i+1]);
        if(t.first < t.second){
            swap(t.first, t.second);
        }
        if(i != point.size() - 1) edge.insert(t);
    }
    vertex.insert(point.back());
    printf("%d",1 + edge.size() - (int)vertex.size());
}