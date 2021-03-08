#include <bits/stdc++.h>
using namespace std;

template<class value_type>
class my_list{
public:
  class node{
  public:
    value_type value;
    node* front;
    node* back;
    node(value_type value_):value(value_),front(nullptr),back(nullptr){}
  };
  int n;
  node* front_;
  node* back_;
  my_list():n(0){
    front_ =
      back_ = new node(-1);
  }

  class iterator{
  public:
    node* current;
    iterator(node* current_):current(current_){}
    iterator():current(nullptr){}
    iterator& operator++(){
      current = current->back;
      return *this;
    }
    iterator& operator--(){
      current = current->front;
      return *this;
    }
    bool operator!=(iterator const& other){
      return current != other.current;
    }
    value_type& operator*(){
      return current->value;
    }
  };

  iterator insert(iterator itr,value_type value){
    ++n;
    node* add = new node(value);
    node* front = itr.current->front;
    node* back = itr.current;
    if(front!=nullptr){
      add->front = front;
      front->back = add;
    }else{
      front_ = add;
    }
    if(back!=nullptr){
      add->back = back;
      back->front = add;
    }
    return iterator(add);
  }

  iterator erase(iterator itr){
    --n;
    node* front = itr.current->front;
    node* back = itr.current->back;
    if(front!=nullptr){
      front->back = back;
    }else{
      front_ = back;
    }
    if(back!=nullptr){
      back->front = front;
    }
    delete itr.current;
    return iterator(back);
  }

  iterator begin(){
    return iterator(front_);
  }
  iterator end(){
    return iterator(back_);
  }
};


int main(){
  int q;
  my_list<int> li;
  my_list<int>::iterator itr = li.end();
  cin >> q;
  for(int i=0;i<q;++i){
    int kind;
    cin >> kind;
    if(kind==0){
      int x;
      cin >> x;
      itr = li.insert(itr,x);
    }else if(kind==1){
      int d;
      cin >> d;
      while(d){
        if(d>0){
          ++itr;
          --d;
        }else{
          --itr;
          ++d;
        }
      }
    }else{
      itr = li.erase(itr);
    }
  }
  for(auto&i:li){
    cout << i << endl;
  }
}
