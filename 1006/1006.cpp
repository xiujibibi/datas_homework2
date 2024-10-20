#include <iostream>
#include <stack>
#include <string>
#include <cctype>
#include <sstream>
#include <vector>
#include <algorithm>

// 檢查括號是否對稱
bool areParenthesesBalanced(const std::string& expr) {
    std::stack<char> s;
    for (char ch : expr) {
        if (ch == '(') {
            s.push(ch);
        }
        else if (ch == ')') {
            if (s.empty()) return false;
            s.pop();
        }
    }
    return s.empty();
}

// 獲取運算子的優先級
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

// 將中序表達式轉換為後序表達式
std::string infixToPostfix(const std::string& expr) {
    std::stack<char> s;
    std::string postfix;
    for (char ch : expr) {
        if (isdigit(ch)) {
            postfix += ch;
        }
        else if (ch == '(') {
            s.push(ch);
        }
        else if (ch == ')') {
            while (!s.empty() && s.top() != '(') {
                postfix += s.top();
                s.pop();
            }
            s.pop();
        }
        else {
            while (!s.empty() && precedence(s.top()) >= precedence(ch)) {
                postfix += s.top();
                s.pop();
            }
            s.push(ch);
        }
    }
    while (!s.empty()) {
        postfix += s.top();
        s.pop();
    }
    return postfix;
}

// 計算後序表達式的結果
int evaluatePostfix(const std::string& postfix) {
    std::stack<int> s;
    for (char ch : postfix) {
        if (isdigit(ch)) {
            s.push(ch - '0');
        }
        else {
            int val2 = s.top(); s.pop();
            int val1 = s.top(); s.pop();
            switch (ch) {
            case '+': s.push(val1 + val2); break;
            case '-': s.push(val1 - val2); break;
            case '*': s.push(val1 * val2); break;
            case '/': s.push(val1 / val2); break;
            }
        }
    }
    return s.top();
}

int main() {
    std::string expr;
    char continueTest;
    do {
        // 請使用者輸入運算式
        std::cout << "請輸入運算式: ";
        std::cin >> expr;

        // 檢查括號是否對稱
        if (!areParenthesesBalanced(expr)) {
            std::cout << expr << " 運算式的括號不對稱，無法繼續運算\n";
        }
        else {
            // 將中序表達式轉換為後序表達式並計算結果
            std::string postfix = infixToPostfix(expr);
            int result = evaluatePostfix(postfix);
            std::cout << expr << " 運算式的左右括號對稱\n";
            std::cout << expr << " 運算式的後序表式法為: " << postfix << "\n";
            std::cout << expr << " 運算式的運算結果為: " << result << "\n";
        }

        // 詢問使用者是否繼續測試
        std::cout << "是否繼續測試? (Y/y 繼續, 其他鍵退出): ";
        std::cin >> continueTest;
    } while (continueTest == 'Y' || continueTest == 'y');

    return 0;
}