#include <iostream>
using namespace std;

enum weekday { s, m, t, w, thu, f, s1 };

int main(int argc, char const *argv[]) {
  enum weekday wek = s;
  cout << wek << endl; // 0
  cout << m << endl; // 1
  // weekday wek=s;
  for (int i = wek; i != f; i++) {
    cout << i << endl; // 0 1 2 3 4
    cout << wek + s << endl; // 0 0 0 0 0
    cout << "-------哈哈-------" << endl;
  }

  return 0;
}
