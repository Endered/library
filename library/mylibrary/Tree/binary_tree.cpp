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
void output(t x){
	if(was_output)cout << " ";
	was_output = true;
	cout << x;
}

void outendl(){
	was_output = false;
	cout << endl;
}

class node{
public:
	int key;
	node *left;
	node *right;
	node *parent;
	node(int key):key(key), left(NULL), right(NULL), parent(NULL){}
};

class binary_tree{
public:
	node *root;
	binary_tree():root(NULL){}

	void insert(int key){
		node *z = new node(key);
		node *y = NULL;
		node *x = root;
		while(x!=NULL){
			y = x;
			if(z->key < x->key){
				x = x->left;
			}else{
				x = x->right;
			}
		}

		if(y==NULL){
			root = z;
			z->parent = NULL;
		}else if(z->key < y->key){
			y->left = z;
			z->parent = y;
		}else{
			y->right = z;
			z->parent = y;
		}
	}


	void inorder(){
		inorder(root);
	}

	void inorder(node *n){
		if(n==NULL)return;
		inorder(n->left);
		cout << " " << n->key;
		inorder(n->right);
	}


	void preorder(){
		preorder(root);
	}

	void preorder(node *n){
		if(n==NULL)return;
		cout << " " << n->key;
		preorder(n->left);
		preorder(n->right);
	}


	bool find(int key){
		return find(root, key);
	}

	bool find(node *n, int key){
		if(n==NULL)return false;
		if(key==n->key)return true;
		if(key < n->key)return find(n->left, key);
		return find(n->right, key);
	}

	node* getmostleft(node *n){
		if(n->left==NULL){
			return n;
		}
		return getmostleft(n->left);
	}

	void erase(int key){
		erase(root, key);
	}


	void erase(node* n, int key){
		if(n->key == key){
			int count = (n->right!=NULL) + (n->left!=NULL);
			if(count==0){
				if(n==root){
					delete root;
					return;
				}
				if(n==n->parent->right){
					n->parent->right = NULL;
				}else{
					n->parent->left = NULL;
				}
				delete n;
			}else if(count==1){
				if(n==root){
					if(n->right!=NULL){
						root = n->right;
					}else{
						root = n->left;
					}
					root->parent = NULL;
					delete n;
					return;
				}
				node *next;
				if(n->right!=NULL){
					next = n->right;
				}else{
					next = n->left;
				}
				if(n->parent->right==n){
					n->parent->right = next;
				}else{
					n->parent->left = next;
				}
				next->parent = n->parent;
				delete n;
			}else{
				node *next = getmostleft(n->right);
				n->key = next->key;
				erase(next, next->key);
			}
			return;
		}
		if(key < n->key) erase(n->left, key);
		else erase(n->right, key);
	}
};


int main(){
	binary_tree t;
	int time;
	cin >> time;
	rep(i, time){
		string op;
		cin >> op;
		if(op=="insert"){
			int num;
			cin >> num;
			t.insert(num);
		}else if(op=="print"){
			t.inorder();
			cout << endl;
			t.preorder();
			cout << endl;
		}else if(op=="find"){
			int num;
			cin >> num;
			cout << (t.find(num)?"yes":"no") << endl;
		}else if(op=="delete"){
			int num;
			cin >> num;
			t.erase(num);
		}
	}


	return 0;
}


