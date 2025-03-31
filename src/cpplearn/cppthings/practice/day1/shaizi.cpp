/*
这段代码模拟了一个经典的赌场游戏，称为 "Craps"。以下是 Craps 游戏的基本规则：

1. **初始掷骰子（Come Out Roll）**：
   - 玩家掷两个骰子，计算它们的总和。
   - 如果总和是 7 或 11，玩家立即获胜。
   - 如果总和是 2、3 或 12，玩家立即失败（称为 "Craps"）。
   - 如果总和是其他值（4、5、6、8、9 或 10），这个值成为 "点数"（Point），游戏进入下一阶段。

2. **后续掷骰子（Point Roll）**：
   - 玩家继续掷两个骰子，计算它们的总和。
   - 如果总和等于之前的 "点数"，玩家获胜。
   - 如果总和是 7，玩家失败。
   - 如果总和是其他值，玩家继续掷骰子，直到掷出 "点数" 或 7 为止。
*/
#include <cstdlib>
#include <iostream>
using namespace std;

int rollDice();

int main(int argc, char* argv[]){
    int seed;
    cout << "Enter seed: ";
    cin >> seed;
    srand(seed);

    int sum = rollDice();
    int sec_sum;
    switch(sum) {
        case 7: case 11:
            cout << "Player wins" << endl;
            break;
        case 2: case 3: case 12:
            cout << "Player loses" << endl;
            break;
        default:
            while(1){
                sec_sum = rollDice();
                if (sum == sec_sum || sec_sum == 7){
                    cout << "Player wins" << endl;
                    break;
                }
            }
    }
    return 0;
}

int rollDice(){
    int die1 = rand() % 6 + 1;
    int die2 = rand() % 6 + 1;
    int sum = die1 + die2;
    cout << "Player rolled " << die1 << " + " << die2 << " = " << sum << endl;
    return sum;
}
