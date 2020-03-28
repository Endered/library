#include<bits/stdc++.h>
#define rep(i, n) for(int i=0;i<(n);++i)
#define per(i, n) for(int i=(n)-1;i>=0;--i)
#define repa(i, n) for(int i=1;i<(n);++i)
#define foreach(i, n) for(auto &i:(n))
#define pii pair<int, int>
#define pll pair<long long, long long>
#define all(x) (x).begin(), (x).end()
#define bit(x) (1ll << (x))
using ll = long long;
//const ll MOD = (ll)1e9+7;
const ll MOD = 998244353;
const int INF = (ll)1e9+7;
const ll INFLL = (ll)1e18;
using namespace std;
template<class t>
using vvector = vector<vector<t>>;
template<class t>
using vvvector = vector<vector<vector<t>>>;
template<class t>
using priority_queuer = priority_queue<t, vector<t>, greater<t>>;
template<class t, class u> bool chmax(t &a, u b){if(a<b){a=b;return true;}return false;}
template<class t, class u> bool chmin(t &a, u b){if(a>b){a=b;return true;}return false;}
#ifdef DEBUG
#define OUTPUT(x) (output(x), output("\n"))
#else
#define OUTPUT(x) (void)0
#endif

ll modpow(ll x, ll b){
    ll res = 1;
    while(b){
        if(b&1)res = res * x % MOD;
        x = x * x % MOD;
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

template<class T,class U>
class segment_tree{
public:
  using F = function<T(T,T)>;
  using G = function<T(T,U)>;
  F f;
  G g;
  int n;
  vector<T> v;
  T init;
  segment_tree(int n_,T init_,F f_,G g_){
    n=1;
    while(n<n_)n<<=1;
    n<<=1;
    init = init_;
    v.resize(n,init);
    f = f_;
    g = g_;
  }

  void update(int t,U x){
    update(0,n,1,t,x);
  }

  void update(int lp,int rp,int p,int t,U x){
    if(t<lp||rp<=t)return;
    v[p] = g(v[p],x);
    int mid = (lp+rp)>>1;
    if(lp==mid)return;
    update(lp,mid,p*2,t,x);
    update(mid,rp,p*2+1,t,x);
  }

  T query(int l,int r){
    return query(l,r,0,n,1);
  }

  T query(int l,int r,int lp,int rp,int p){
    if(r<lp||rp<=l)return init;
    T res = init;
    int mid = (lp+rp)>>1;
    if(l<=lp&&rp<=r)res = v[p];
    if(lp==mid)return res;
    res = f(res,query(l,r,lp,mid,p*2));
    res = f(res,query(l,r,mid,rp,p*2+1));
    return res;
  }
};



int main(){
  int n;
  cin >> n;
  segment_tree<pii,int> tree(n,pii(INF,INF),
			     [](pii a,pii b){
			       if(a.first<b.first)return a;
			       return b;
			     },
			     [](pii a,int x){
			       if(a.first>x)a.first = x;
			       return a;
			     });
  
  return 0;
}
