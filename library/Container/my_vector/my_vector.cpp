#include<bits/stdc++.h>

using namespace std;

template<class value_type>
class my_vector{
public:
  int imag_size;
  int real_size;
  value_type *array;
  my_vector(int n_){
    real_size = n_;
    imag_size = 1;
    while(real_size>imag_size)imag_size<<=1;
    array = new value_type[imag_size];
  }
  my_vector(int n_,value_type init_value){
    real_size = n_;
    imag_size = 1;
    while(real_size>imag_size)imag_size<<=1;
    array = new value_type[imag_size];
    for(int i=0;i<real_size;++i){
      array[i] = init_value;
    }
  }
  my_vector():my_vector(0){}

  void push_back(value_type x){
    if(real_size==imag_size){
      imag_size <<= 1;
      value_type *next = new value_type[imag_size];
      for(int i=0;i<real_size;++i){
        next[i] = array[i];
      }
      delete[] array;
      array = next;
    }
    array[real_size++] = x;
  }

  value_type pop_back(){
    if(real_size==0){
      cout << "my_vector::pop_back() invalid data size" << endl;
      exit(1);
    }
    return array[--real_size];
  }

  value_type& operator[](int p){
    return array[p];
  }

  void clear(){
    delete[] array;
    imag_size = 1;
    real_size = 0;
    array = new value_type[1];
  }

  class iterator{
  public:
    value_type* current;
    iterator():current(nullptr){}
    iterator(value_type *current_):current(current_){}
    iterator operator++(){
      ++current;
      return *this;
    }
    iterator operator--(){
      --current;
      return *this;
    }
    value_type& operator*(){
      return *current;
    }
    bool operator!=(iterator const &other){
      return current != other.current;
    }
  };

  iterator begin(){
    return iterator(array);
  }
  iterator end(){
    return iterator(array+real_size);
  }


};

int main(){
  int n;
  int q;
  cin >> n;
  cin >> q;
  my_vector<my_vector<int>> lines(n);
  for(int i=0;i<q;++i){
    int kind;
    cin >> kind;
    if(kind==0){
      int t;
      cin >> t;
      int value;
      cin >> value;
      lines[t].push_back(value);
    }else if(kind==1){
      int t;
      cin >> t;
      bool flag = false;
      for(auto &i:lines[t]){
        if(flag)cout << " ";
        cout << i;
        flag = true;
      }
      cout << endl;
    }else{
      int t;
      cin >> t;
      lines[t].clear();
    }
  }
  return 0;
}
