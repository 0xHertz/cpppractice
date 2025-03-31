#include <iostream>
using namespace std;
double power(double x, int n);

int main(int argc, char const *argv[]) {
  int x;
  cin >> x;
  int wei = 0;
  int sum = 0;
  int each, chu;
  /* 个位*1,十位*2,百位*4,千位*8....... */
  /* 如果输入二进制，效果相当于二进制转十进制 */
  for (int i = 0; i < 8; i++) {
    each = x % 10;
    chu = x / 10;
    sum += each * power(2, wei);
    x = chu;
    wei++;
  }
  cout << sum << endl;

  return 0;
}
double power(double x, int n) {
  double val = 1.0;
  while (n--) {
    val *= x;
  }
  return val;
}
