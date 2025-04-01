#include <iostream>
using namespace std;

template <class T, int MAXSIZE>
class MStack{
    private:
    T elem[MAXSIZE];
    int top;
    public:
    MStack(){ top = 0; };
    void push(T e);
    T pop();
    bool empty() {
        if (top <= -1)
            return 1;
        else
            return 0;
    }
    void setEmpty() { top = -1; }
    bool full() {
        if (top >= MAXSIZE - 1) {
            return 1;
        } else
            return 0;
    }
};

template <class T, int MAXSIZE>
void MStack<T, MAXSIZE>::push(T e){
    if (full()){
        cout << "full.can not push" << endl;
    } else {
        elem[++top] = e;
    }
}

template <class T, int MAXSIZE>
T MStack<T, MAXSIZE>::pop(){
    if (empty()){
        cout << "empty.can not pop" << endl;
        return -1;
    } else {
        return elem[top--];
    }
}


int main(int argc, char const *argv[]) {
  //类模板实例化
  MStack<int, 10> iStack;
  MStack<char, 10> cStack;
  iStack.setEmpty();
  cStack.setEmpty();
  cout << "-------intStack----\n";
  int i;
  for (i = 1; i < 11; i++){
      iStack.push(i);
  }

  for (i = 1; i < 11; i++)
    cout << iStack.pop() << "\t";
  cout << "\n\n-------charStack----\n";
  cStack.push('A');
  cStack.push('B');
  cStack.push('C');
  cStack.push('D');
  cStack.push('E');
  for (i = 1; i < 6; i++)
    cout << cStack.pop() << "\t";
  cout << endl;

  return 0;
}
