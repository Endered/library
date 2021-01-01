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
  ll in(){
    ll res;
    cin >> res;
    return res;
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
}

using namespace templates;

template<class type,int size>
class functional_array{
    type initial_value;
    class node{
        public:
        array<node*,size> *childs;
        type value;
        node(type initial_value):value(initial_value),childs(nullptr){ }

        node& operator=(node& other){
            value = other.value;
            if(other.childs!=nullptr){
                childs = new array<node*,size>;
                *childs = *other.childs;
            }else{
                childs = nullptr;
            }
            return *this;
        }

        node*& operator[](int p){
            if(childs==nullptr){
                childs = new array<node*,size>;
            }
            return (*childs)[p];
        }
    };
    node *root;
    public:

    functional_array(type initial_value):initial_value(initial_value),root(nullptr){}

    type get_value(size_t p){
        if(root==nullptr){
            root = new node(initial_value);
        }
        node *n = root;
        while(p){
            if(n->childs==nullptr){
                return initial_value;
            }
            size_t div = p / size;
            size_t rem = p % size;
            node *next = (*n)[rem];
            if(next==nullptr){
                return initial_value;
            }
            n = next;
            p = div;
        }
        return n->value;
    }

    functional_array change_value(size_t p, type value){
        functional_array res(initial_value);
        res.root = new node(initial_value);
        if(root!=nullptr){
            *res.root = *root;
        }
        node *to_n = res.root;
        node *from_n = root;
        while(p){
            size_t div = p / size;
            size_t rem = p % size;
            (*to_n)[rem] = new node(initial_value);
            to_n = (*to_n)[rem];
            if(from_n!=nullptr and (*from_n)[rem] != nullptr){
                from_n = (*from_n)[rem];
                *to_n = *from_n;
            }
            p = div;
        }
        to_n->value = value;
        return res;
    }

    functional_array map(function<type(type)> f){
        functional_array res(f(initial_value));
        res.root = map(f,root);
        return res;
    }
    node* map(function<type(type)> f,node *n){
        if(n==nullptr)return nullptr;
        node *res = new node(f(n->value));
        for(size_t i=0;i<size;++i){
            (*res)[i] = map(f, (*n)[i]);
        }
        return res;
    }
};

int main(){
    functional_array<int,2> x(0);
    using fa = functional_array<int,2>;
    int n = 10;
    fa initial(0);
    rep(i,n){
        initial = initial.change_value(i,i);
    }
    rep(i,n){
        output(initial.get_value(i));
    }
    outendl();
    fa next = initial.map(lambda(int,int x){return x + 3;});

    rep(i,n){
        output(initial.get_value(i));
    }
    outendl();
    rep(i,n){
        output(next.get_value(i));
    }
    rep(i,n,n+10){
        output(next.get_value(i));
    }
    outendl();
  return 0;
}
