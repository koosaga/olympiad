//qwerasdfzxcl
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
constexpr int MX = 1e6;
char buf[101010];
vector<string> buf2;
map<string, char> mp;
int Lx = 0, Rx = MX, Ly = 0, Ry = MX;

int px, py;
void query(int x, int y, bool no = 0){
    px = x, py = y;
    printf("%d %d\n", x, y);
    fflush(stdout);

    cin >> ws;
    string ret;
    getline(cin, ret);
    if (ret.back()=='!') exit(0);

    if (no) return;
    buf2.push_back(ret);

    mp[ret] = 0;
}

char Q(int x, int y){
    if (px==x && py==y) return 's';
    else px = x, py = y;
    printf("%d %d\n", x, y);
    fflush(stdout);

    cin >> ws;
    string ret;
    getline(cin, ret);
    if (ret.back()=='!') exit(0);

    if (mp.find(ret)!=mp.end()) return mp[ret];
    return 's';
}

void find_what(){
    query(2, 2, 1);
    query(1, 2);
    query(0, 2);
    query(0, 1);
    if (mp.size()==1){
        query(2, 2);
        mp[buf2[0]] = 'f';
        mp[buf2[3]] = 'c';

        Lx = 2, Ly = 2;
        return;
    }
    query(0, 0);

    assert(mp.size()==2);

    string b;
    for (int i=0;i<4;i++) b.push_back(buf2[i]==buf2[0]?'A':'B');

    if (b=="AABB"){ ///case 1, 5, 9
        query(MX-1, 0, 1);
        query(MX, 0);
        if (buf2[4]==buf2[0]){ ///case 5, 9
            mp[buf2[0]] = 'f';
            mp[buf2[3]] = 'c';

            Lx = 2;
            Ry = 0;
            return;
        }
        else{ ///case 1
            mp[buf2[0]] = 'c';
            mp[buf2[4]] = 'f';

            Rx = 0;
            Ly = 2;
            return;
        }
    }

    else if (b=="ABBB"){ ///case 2
        mp[buf2[0]] = 'c';
        mp[buf2[1]] = 'f';
    }
    else if (b=="AAAA"){ ///case 3
        mp[buf2[0]] = 'f';
        assert(buf2[0] != buf2[4]);
        mp[buf2[4]] = 'c';
    }
    else if (b=="AABA"){ ///case 4, 7
        mp[buf2[0]] = 'f';
        mp[buf2[2]] = 'c';
    }
    else if (b=="ABAB"){ ///case 6
        mp[buf2[0]] = 'c';
        mp[buf2[1]] = 'f';
    }
    else if (b=="ABAA"){ ///case 8
        mp[buf2[0]] = 'c';
        mp[buf2[1]] = 'f';
    }
    else{
        exit(3); /// <- fucked
    }

}

int main(){
    find_what();
    //for (auto &[s, t]:mp) cout << s << ' ' << t << '\n';

    while(Lx<=Rx && Ly<=Ry){
        //printf("%d %d / %d %d\n", Lx, Rx, Ly, Ry);
        int lenx = Rx-Lx, leny = Ry-Ly;

        int nlx, nrx;
        if (lenx%2==1) nlx = Lx + lenx/2, nrx = Lx + lenx/2+1;
        else nlx = Lx + lenx/2-1, nrx = Lx + lenx/2+1;

        int nly, nry;
        if (leny%2==1) nly = Ly + leny/2, nry = Ly + leny/2+1;
        else nly = Ly + leny/2-1, nry = Ly + leny/2+1;

        string tmp;
        char tmp2 = Q(Lx, Ly);

        if (Lx==Rx && Ly==Ry) Q(0, 0);

        if (Lx < Rx) tmp += Q(Rx, Ly);
        else tmp += 's';
        if (Ly < Ry) tmp += Q(Rx, Ry);
        else tmp += 's';


        if (tmp[0]=='f') Rx = nlx;
        else if (tmp[0]=='c') Lx = nrx;
        else{
            assert(tmp[0]=='s');
            assert(lenx%2==0);
            int midx = Lx + lenx/2;
            Lx = Rx = midx;
        }

        if (tmp[1]=='f') Ry = nly;
        else if (tmp[1]=='c') Ly = nry;
        else{
            assert(tmp[1]=='s');
            assert(leny%2==0);
            int midy = Ly + leny/2;
            Ly = Ry = midy;
        }
    }

    printf("WTF???\n");
    return 0;
}
