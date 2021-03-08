#include<bits/stdc++.h>
#define rep(i,a,...) for(int i = (a)*(strlen(#__VA_ARGS__)!=0);i<(int)(strlen(#__VA_ARGS__)?__VA_ARGS__:(a));++i)
#define per(i,a,...) for(int i = (strlen(#__VA_ARGS__)?__VA_ARGS__:(a))-1;i>=(int)(strlen(#__VA_ARGS__)?(a):0);--i)
#define foreach(i, n) for(auto &i:(n))
#define all(x) (x).begin(), (x).end()
#define bit(x) (1ll << (x))
#define lambda(RES_TYPE, ...) (function<RES_TYPE(__VA_ARGS__)>)[&](__VA_ARGS__) -> RES_TYPE
#define method(FUNC_NAME, RES_TYPE, ...) function<RES_TYPE(__VA_ARGS__)> FUNC_NAME = lambda(RES_TYPE, __VA_ARGS__)
using namespace std;
using ll = long long;
using pii = pair<int,int>;
using pll = pair<ll,ll>;
//const ll MOD = (ll)1e9+7;
const ll MOD = 998244353;
const int INF = (ll)1e9+7;
const ll INFLL = (ll)1e18;
template<class t>
using vvector = vector<vector<t>>;
template<class t>
using vvvector = vector<vector<vector<t>>>;
template<class t>
using priority_queuer = priority_queue<t, vector<t>, greater<t>>;
template<class t, class u> bool chmax(t &a, u b){if(a<b){a=b;return true;}return false;}
template<class t, class u> bool chmin(t &a, u b){if(a>b){a=b;return true;}return false;}
#ifdef DEBUG
#define debug(x) cout<<"LINE "<<__LINE__<<": "<<#x<<" = "<<x<<endl;
#else
#define debug(x) (void)0
#endif


template<class T>
class binary_indexed_tree{
public:
    int n;
    vector<T> data;
    T init;
    binary_indexed_tree(int n,T init=T(0)):n(n+1),data(n+1,init),init(init){}

    void add(int p,T v){
        for(int i=p+1;i<=n;i+=(i&(-i))){
            data[i] = data[i] + v;
        }
    }

    T sum(int p){
        T res = init;
        for(int i=p;i>0;i-=(i&(-i))){
            res = res + data[i];
        }
        return res;
    }
};

namespace templates{
    ll modpow(ll x, ll b,ll mod=MOD){
        ll res = 1;
        while(b){
            if(b&1)res = res * x % mod;
            x = x * x % mod;
            b>>=1;
        }
        return res;
    }

    ll modinv(ll x){
        return modpow(x, MOD-2);
    }

    bool was_output = false;
    template<class t>
    void output(t a){
        if(was_output)cout << " ";
        cout << a;
        was_output = true;
    }
    void outendl(){
        was_output = false;
        cout << endl;
    }

    template<class t>
    istream& operator>>(istream&is, vector<t>&x){
        for(auto &i:x)is >> i;
        return is;
    }

    template<class t, class u>
    istream& operator>>(istream&is, pair<t, u>&x){
        is >> x.first >> x.second;
        return is;
    }

    template<class t>
    ostream& operator<<(ostream&os, vector<t> &v){
        os << "{";
        for(t &i:v){
            os << i << ", ";
        }
        os << "}";
        return os;
    }

    template<class t = long long>
    t in(){
        t res; cin >> res; return res;
    }

    template<class t>
    void out(t x){
        cout << x;
    }


    template<class t>
    vector<t> sorted(vector<t> line,function<bool(t,t)> comp=[](t a,t b){return a<b;}){
        sort(line.begin(),line.end(),comp);
        return line;
    }

    template<class t>
    vector<t> reversed(vector<t> line){
        reverse(line.begin(),line.end());
        return line;
    }
    string reversed(string str){
        reverse(str.begin(),str.end());
        return str;
    }

    long long gcd(long long a,long long b){
        while(b){
            a %= b;
            swap(a,b);
        }
        return a;
    }

    long long lcm(long long a,long long b){
        return a / gcd(a,b) * b;
    }
}

using namespace templates;


ll func(){
    int n = in();
    vector<int> line(n);
    foreach(i,line)i=in()-1;
    vector<int> table(n);
    rep(i,n){
        table[line[i]] = i;
    }
    ll res = 0;
    binary_indexed_tree<ll> bi(n);
    rep(i,n)bi.add(i,1);
    rep(i,n){
        bi.add(table[i],-1);
        res += min(bi.sum(table[i]),
                   bi.sum(n)-bi.sum(table[i]));
    }
    return res;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << func() << endl;
    return 0;
}
