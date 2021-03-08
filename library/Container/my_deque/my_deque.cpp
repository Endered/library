#include<bits/stdc++.h>

using namespace std;

template<class value_type>
class my_deque{
public:
  int imag_size;
  int real_size;
  value_type *array;
  int front_position;
  int back_position;
  my_deque(){
    imag_size = 1;
    real_size = 0;
    array = new value_type[imag_size];
    front_position =
      back_position = 0;
  }

  inline int index(int p){
    p%=imag_size;
    p+=imag_size;
    p%=imag_size;
    return p;
  }

  value_type &front(){
    return array[front_position];
  }
  value_type &back(){
    return array[index(back_position-1)];
  }

  void push_back(value_type value){
    if(imag_size==real_size){
      value_type *next = new value_type[imag_size<<1];
      for(int i=0,j=front_position;i<imag_size;++i,j=index(j+1)){
        next[i] = array[j];
      }
      delete[] array;
      front_position = 0;
      back_position = imag_size;
      imag_size <<= 1;
      array = next;
    }
    ++real_size;
    array[back_position] = value;
    back_position = index(back_position+1);
  }

  void push_front(value_type value){
    if (imag_size == real_size) {
      value_type *next = new value_type[imag_size<<1];
      for (int i=0,j=front_position;i<imag_size;++i,j=index(j+1)) {
        next[i] = array[j];
      }
      delete[] array;
      front_position = 0;
      back_position = imag_size;
      imag_size <<= 1;
      array = next;
    }
    ++real_size;
    front_position = index(front_position-1);
    array[front_position] = value;
  }

  value_type pop_back(){
    --real_size;
    back_position = index(back_position-1);
    return array[back_position];
  }
  value_type pop_front(){
    --real_size;
    value_type res = array[front_position];
    front_position = index(front_position+1);
    return res;
  }

  value_type& operator[](int p){
    return array[index(front_position+p)];
  }
};

int main(){
  my_deque<int> dq;
  int q;
  cin >> q;
  for(int i=0;i<q;++i){
    int kind;
    cin >> kind;
    if(kind==0 or kind==2){
      int dir;
      cin >> dir;
      if(kind==0){
        int value;
        cin >> value;
        if(dir==0){
          dq.push_front(value);
        }else{
          dq.push_back(value);
        }
      }else{
        if(dir==0){
          dq.pop_front();
        }else{
          dq.pop_back();
        }
      }
    }else{
      int p;
      cin >> p;
      cout << dq[p] << endl;
    }
  }
  return 0;
}
