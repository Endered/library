#include<bits/stdc++.h>
#define rep(i, n) for(int i=0;i<(n);++i)
#define per(i, n) for(int i=(n)-1;i>=0;--i)
#define repa(i, n) for(int i=1;i<(n);++i)
#define foreach(i, n) for(auto &i:(n))
#define pii pair<int, int>
#define pll pair<long long, long long>
#define all(x) (x).begin(), (x).end()
#define bit(x) (1ll << (x))
using namespace std;
using ll = long long;
const ll MOD = (ll)1e9+7;
//const ll MOD = 998244353;
//const ll MOD = 924844033;
const int INF = (ll)1e9+7;
const ll INFLL = (ll)1e18;
const double EPS = 1e-5;
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
#define OUTPUT(x) (output(x), outendl())
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

class articulation_points{
	private:
		vector<int> number;
		vector<int> least;
		vvector<int> cedges;
		vvector<int> redges;
		const int root = 0;
		int get_next_number(){
			static int x = 0;
			return ++x;
		}
		void set_number(int p,int parent){
			number[p] = get_next_number();
			for(int i:edges[p]){
				if(i==parent)continue;
				if(number[i]<0){
					set_number(i,p);
					cedges[p].push_back(i);
				}else{
					redges[p].push_back(i);
				}
			}
		}

		int set_least(int p){
			if(least[p]>=0)return least[p];
			int res = number[p];
			for(int i:cedges[p]){
				res = min(res,set_least(i));
			}
			for(int i:redges[p]){
				res = min(res, number[i]);
			}
			least[p] = res;
			return res;
		}

		bool check_root(){
			stack<int> st;
			int start = edges[root].front();
			vector<bool> used(n,false);
			used[start] = true;
			st.push(start);
			int cnt = 2;
			while(st.size()){
				int d = st.top();
				st.pop();
				for(int i:edges[d]){
					if(i==root)continue;
					if(used[i])continue;
					used[i] = true;
					++cnt;
					st.push(i);
				}
			}
			return cnt != n; 
		}

	public:
		int n;
		vector<vector<int>> edges;
		articulation_points(int n_){
			n = n_;
			edges.resize(n);
			number.resize(n,-1);
			least.resize(n,-1);
			cedges.resize(n);
			redges.resize(n);
		}

		void add_edge(int a,int b){
			edges[a].push_back(b);
			edges[b].push_back(a);
		}


		vector<int> solve(){
			if(n<=2)return vector<int>();
			set_number(root,-1);
			set_least(root);
			vector<int> res;
			if(check_root()){
				res.push_back(root);
			}
			rep(i,n){
				if(i==root)continue;
				bool flag = false;
				for(int j:cedges[i]){
					if(least[j]>=number[i]){
						flag = true;
						break;
					}
				}
				if(flag){
					res.push_back(i);
				}
			}
			return res;
		}
};


int main(){
	int n,m;
	cin >> n >> m;
	articulation_points art(n);
	rep(i,m){
		int a,b;
		cin >> a >> b;
		art.add_edge(a,b);
	}
	vector<int> ans = art.solve();
	sort(all(ans));
	foreach(i,ans){
		cout << i << endl;
	}
	return 0;
}
