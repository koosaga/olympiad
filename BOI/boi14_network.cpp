#include <vector>
#include "network.h"
using namespace std;

vector<int> dist[1001];

void findRoute(int N, int a, int b){
    int l = ping(a,b) + 1;
    for(int i=1; i<=N; i++){
        if(b == i) continue;
        int l2 = ping(b,i) + 1;
        if(l <= l2) continue;
        dist[l - l2].push_back(i);
    }
    int p = a;
    for(int i=1; i<l; i++){
        for(int j=0; j<dist[i].size(); j++){
            if(ping(p,dist[i][j]) == 0){
                travelTo(dist[i][j]);
                p = dist[i][j];
                break;
            }
        }
    }
    travelTo(b);
}