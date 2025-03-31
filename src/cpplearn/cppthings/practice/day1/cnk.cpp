/* 计算组合数C(n,k) */
#include <iostream>
using namespace std;

int Cnk(int n, int k);

int main(int argc ,char* argv[]){
    cout << "input n and k: ";
    int n, k;
    cin >> n >> k;
    cout << "C(" << n << "," << k << ") = " << Cnk(n, k) << endl;
}

int Cnk(int n, int k){
    // 如果k==0或者k==n，返回1，只有一种情况
    if (k == 0 || k == n){
        return 1;
    } else {
        // 分两种情况，k中包含n，Cnk(n-1,k-1)
        // k中不包含n，Cnk(n-1,k)
        return Cnk(n-1, k-1) + Cnk(n-1, k);
    }
}
