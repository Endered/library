#include<bits/stdc++.h>
using namespace std;
#define foreach(i,n) for(auto&i:(n))
#define all(x) (x).begin(),(x).end()
using ll = long long;

template<class t>
auto collect(int n,t f){
    vector<decltype(f())> res(n);
    for(auto &i:res){
        i = f();
    }
    return res;
}

template<class t,class f>
auto mapcar(t x,f func){
    int n = x.size();
    vector<typename t::value_type> res(n);
    auto itr = res.begin();
    for(auto &i:x){
        *itr = func(i);
        ++itr;
    }
    return res;
}
template<class t,class f>
void mapc(t x,f func){
    for(auto &i:x){
        func(i);
    }
}
template<class t,class u>
auto sellect(t x,u f){
    vector<typename t::value_type> res;
    for(auto &i:x){
        if(f(i)){
            res.push_back(i);
        }
    }
    return res;
}

ll in(){
    ll res;
    scanf("%lld",&res);
    return res;
}

template<class t>
t in(){
  t res;
  cin >> res;
  return res;
}

int main(){
    ll n;
    ll k;
    n = in();
    k = in();
    vector<ll> health = collect(n,in<ll>);
    sort(all(health),greater<ll>());
    cout << accumulate(min(n,k)+all(health),0LL) << endl;
    return 0;
}
