#include<bits/stdc++.h>
#define ll long long
#define rep(i, n) for(int i=0;i<(n);++i)
#define per(i, n) for(int i=(n)-1;i>=0;--i)
#define repa(i, n) for(int i=1;i<(n);++i)
#define foreach(i, n) for(auto &i:(n))
#define pii pair<int, int>
#define pll pair<long long, long long>
#define all(x) (x).begin(), (x).end()
#define bit(x) (1ll << (x))
const ll MOD = (ll)1e9+7;
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

class minimum_spanning_tree{
public:
	int n;
	vvector<pll> edges;
	minimum_spanning_tree(int N):n(N){
		edges.resize(n);
	}

	void add_edge(int from, int to, ll cost){
		edges[from].emplace_back(to, cost);
	}

	ll solve(){
		ll res = 0;
		priority_queuer<pll> pq;
		pq.emplace(0, 0);
		vector<bool> used(n, false);
		while(pq.size()){
			pll d = pq.top();
			pq.pop();
			if(used[d.second]){
				continue;
			}
			used[d.second] = true;
			res += d.first;
			foreach(i, edges[d.second]){
				if(used[i.first])continue;
				pq.emplace(i.second, i.first);
			}
		}
		return res;
	}
};


int main(){
	int n;
	cin >> n;
	minimum_spanning_tree msp(n);
	rep(i, n){
		rep(j, n){
			int cost;
			cin >> cost;
			if(cost==-1)continue;
			msp.add_edge(i, j, cost);
		}
	}
	cout << msp.solve() << endl;
	return 0;
}
