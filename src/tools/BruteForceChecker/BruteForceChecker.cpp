#include <iostream>
#include <string>
#include <cstdlib> 

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    const string G = "\033[0;32m";
    const string R = "\033[0;31m";
    const string NC = "\033[0m";

    cout << "-------------------------------------\n";
    cout << "Starting BruteForceChecker...\n";
    cout << "-------------------------------------\n";
    
    // 编译所有程序
    system("g++ -std=c++20 -O2 data.cpp -o data");
    system("g++ -std=c++20 -O2 std.cpp -o std");
    system("g++ -std=c++20 -O2 solve.cpp -o solve");

    int t = 0;
    while (true) {
        t ++;
        cout << "Test " << t << ": ";
        
        // 运行程序并生成输入输出文件
        system("./data > solve.in");
        system("./std < solve.in > solve.out");
        system("./solve < solve.in > solve.ans");
        
        // 使用 diff 比较结果
        if (system("diff -q -b solve.out solve.ans > /dev/null")) {
            cout << R << "Wrong Answer" << NC << "\n";
            system("code --diff solve.ans solve.out");
            system("code solve.in");
            // 找到错误，停止对拍，并保留文件
            break;
        } else {
            cout << G << "Accepted" << NC << "\n";
        }
    }
    
    // 清理可执行文件
    system("rm -f data std solve");

    return 0;
}