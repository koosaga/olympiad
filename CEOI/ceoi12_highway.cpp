#include "office.h"
#include <set>
#include <vector>
#include <tuple>
using namespace std;
  
int main(){
    int n = GetN();
    if(isOnLine(1, 2, 3)){
        vector<int> ret;
        for(int i=4; i<=n; i+=2){
            if(i == n) ret.push_back(i);
            else if(!isOnLine(1, i, i+1)){
                ret.push_back(i);
                ret.push_back(i+1);
                if(ret.size() == 4) break;
            }
        }
        if(ret.size() == 2){
            Answer(1, 2, ret[0], ret[1]);
        }
        else if(ret.size() == 3){
            vector<int> q;
            for(auto &i : ret){
                if(!isOnLine(1, 2, i)){
                    q.push_back(i);
                    if(q.size() == 2) break;
                }
            }
            Answer(1, 2, q[0], q[1]);
        }
        else{
            vector<int> q;
            if(isOnLine(1, 2, ret[0])){
                q.push_back(ret[1]);
            }
            else q.push_back(ret[0]);
            if(isOnLine(1, 2, ret[2])){
                q.push_back(ret[3]);
            }
            else q.push_back(ret[2]);
            Answer(1, 2, q[0], q[1]);
        }
    }
    else if(isOnLine(4, 5, 6)){
        vector<int> ret, q;
        ret.push_back(1);
        ret.push_back(2);
        for(int i=7; i<=n; i+=2){
            if(i == n) ret.push_back(i);
            else if(!isOnLine(4, i, i+1)){
                ret.push_back(i);
                ret.push_back(i+1);
                break;
            }
        }
        // N / 2 + 3
        for(auto &i : ret){
            if(!isOnLine(4, 5, i)){
                q.push_back(i);
                if(q.size() == 2) break;
            }
        }
        Answer(4, 5, q[0], q[1]);
    }
    else{
        int p1 = -1, p2, p3;
        for(int i=1; i<=4; i++){
            for(int j=i+1; j<=5; j++){
                for(int k=j+1; k<=6; k++){
                    if(isOnLine(i, j, k)){
                        tie(p1, p2, p3) = make_tuple(i, j, k);
                    }
                    if(p1 > 0) break;
                }
                if(p1 > 0) break;
            }
            if(p1 > 0) break;
        }
        vector<int> q;
        for(int i=1; i<=6; i++){
            if(i == p1 || i == p2 || i == p3) continue;
            if(!isOnLine(p1, p2, i)){
                q.push_back(i);
                if(q.size() == 2) break;
            }
        }
        Answer(p1, p2, q[0], q[1]);
    }
}