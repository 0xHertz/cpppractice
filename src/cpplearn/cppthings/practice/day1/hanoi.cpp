/*
汉诺塔问题是一个递归问题，目标是将一组盘子从一个柱子移动到另一个柱子，遵循以下规则：
1. 每次只能移动一个盘子。
2. 任何时候都不能将较大的盘子放在较小的盘子上。
*/
#include <iostream>
using namespace std;

/* `move`函数用于输出移动操作，将盘子从柱子 `A` 移动到柱子 `B` */
void move(char a, char b);
/* （'A', 'B', 'C'），其中 'A' 是起始柱，'B' 是辅助柱，'C' 是目标柱。 */
void hanoi(int n, char a, char b, char c);

int main(int argc, char* argv[]){
    cout << "enter the number of disk: ";
    int disk;
    cin >> disk;
    hanoi(disk, 'A', 'B', 'C');
}

void move(char a, char b){
    cout << a << " -> " << b << endl;
}
void hanoi(int n, char a, char b, char c){
    if (n == 1){
        /* 如果只有一个盘子（`n == 1`），直接将盘子从 `A` 移动到 `C` */
        move(a, c);
    } else {
        /* 将 `n-1` 个盘子从 `A` 移动到 `B`（使用 `C` 作为辅助柱） */
        hanoi(n-1, a, c, b);
        /* 然后将第 `n` 个盘子从 `A` 移动到 `C` */
        move(a, c);
        /* 最后将 `n-1` 个盘子从 `B` 移动到 `C`（使用 `A` 作为辅助柱） */
        hanoi(n-1, b, a, c);
    }
}
