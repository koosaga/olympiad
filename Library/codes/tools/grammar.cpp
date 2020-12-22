// vimrc : set nu sc ci si ai sw=4 ts=4 bs=2  mouse=a syntax on
// options : -fsanitize=address -Wfatal-errors

struct StupidGCCCantEvenCompileThisSimpleCode{
	pair<int, int> array[1000000];
}; // https://gcc.gnu.org/bugzilla/show_bug.cgi?id=68203

//####################################
//        random 
//####################################
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int randint(int lb, int ub){ return uniform_int_distribution<int>(lb, ub)(rng); }

//####################################
//        comparator overload
//####################################
auto cmp = [](seg a, seg b){ return a.func() < b.func(); };
set<seg, decltype(cmp)> s(cmp);
map<seg, int, decltype(cmp)> mp(cmp);
priority_queue<seg, vector<seg>, decltype(cmp)> pq(cmp); // max heap

//####################################
//        hash function overload
//####################################
struct point{
    int x, y;
    bool operator==(const point &p)const{ return x == p.x && y == p.y; }
};
struct hasher {
    size_t operator()(const point &p)const{ return p.x * 2 + p.y * 3; }
};
unordered_map<point, int, hasher> hsh;

struct chash {
    static uint64_t splitmix64(uint64_t x) {
        // http://xorshift.di.unimi.it/splitmix64.c
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

//####################################
//        counting iterator
//####################################

template<typename T>
struct counting_iterator: public iterator<random_access_iterator_tag, bool>{
    T value = 0;
    counting_iterator(const T &value): value(value){}
    counting_iterator(const counting_iterator &it): value(it.value){}
    counting_iterator(){}
    typename iterator_traits<counting_iterator>::difference_type operator-(const counting_iterator &it) const{ return value - it.value; }
    counting_iterator &operator++(){ return *this += 1; }
    counting_iterator &operator--(){ return *this += -1; }
    counting_iterator &operator+=(typename iterator_traits<counting_iterator>::difference_type n){ value += n; return *this; }
    bool operator!=(const counting_iterator &it) const{ return value != it.value; }
    T &operator*(){ return value; }
};
template<typename T>
using cnt_it = counting_iterator<T>;
