 # include<iostream>
# include <math.h>
# include <algorithm>
using namespace std;

struct Stack {
    int TOP;
    int SIZE;
    char *ARRAY;

    Stack(int s) {
        SIZE = s;
        ARRAY = new char[SIZE];
        TOP = -1;
    }

    void PUSH(char x) {
        if (TOP == SIZE - 1) {
            return;
        }
        ARRAY[++TOP] = x;
    }

    char POP() {
        if (TOP == -1) {
            return -1;  	
        }
        return ARRAY[TOP--];
    }

    char peek() {
        if (TOP == -1) {
            return -1; 
        }
        return ARRAY[TOP];
    }
    bool KHALI() {
        return TOP == -1;
    }
};
int PREC(char c) {
    if (c == '^') {
        return 3;
    } else if (c == '*' || c == '/') {
        return 2;
    } else if (c == '+' || c == '-') {
        return 1;
    } else if (c == '(') {
        return 0;
    }
}

string CONVERSION(string s) {
    Stack st(s.length());
    string RESULT;
    for (int i = 0; i < s.length(); i++) {
        if (s[i] >= '0' && s[i] <= '9') {
            RESULT += s[i];
        } else if (s[i] == '(') {
            st.PUSH(s[i]);
        } else if (s[i] == ')') {
            while (!st.KHALI() && st.peek() != '(') { 
                RESULT += st.POP(); 
            }
            if (!st.KHALI()) {
                st.POP();
            }
        } else {
            while (!st.KHALI() && PREC(st.peek()) >= PREC(s[i])) {
                RESULT += st.POP(); 
            }
            st.PUSH(s[i]); 
        }
    }
    
    while (!st.KHALI()) {
        RESULT += st.POP(); 
    }
    return RESULT;
}

string PREFIX(string s)
{
    Stack st(s.length()); 
    reverse(s.begin(), s.end()); 

    for (int i = 0; i < s.length(); i++) { 
        if (s[i] == '(') {
            s[i] = ')';
        }
        else if (s[i] == ')') {
            s[i] = '(';
        }
    }
    string PREFIX_STRING = CONVERSION(s);
    reverse(PREFIX_STRING.begin(), PREFIX_STRING.end()); 
    return PREFIX_STRING;
}



int SOLVE(string s) {
    Stack st(s.length());
    for (int i = 0; i < s.length(); i++) {
        if (s[i] >= '0' && s[i] <= '9') {
            st.PUSH(s[i] - '0');
        } else {
            int OPERAND2 = st.POP();
            int OPERAND1 = st.POP();
            if (s[i] == '+') {
                st.PUSH(OPERAND1 + OPERAND2);
            } else if (s[i] == '-') {
                st.PUSH(OPERAND1 - OPERAND2);
            } else if (s[i] == '*') {
                st.PUSH(OPERAND1 * OPERAND2);
            } else if (s[i] == '/') {
                st.PUSH(OPERAND1 / OPERAND2);
            } else if (s[i] == '^') {
                st.PUSH(pow(OPERAND1, OPERAND2));
            }
        }
    }
    return st.POP();
}

struct BracketStack {
    char brackets[100];
    int top;

    BracketStack() {
        top = -1 ;
    }

    void PUSH(char bracket) {
        top++;
        brackets[top] = bracket;
    }

    char POP() {
        char bracket = brackets[top];
        top--;
        return bracket;
    }

    bool EMPTY() {
        return top == -1;
    }
};

bool CHECK_BRACKET(string EXPRESSION) {
    int LENGTH = EXPRESSION.length();
    BracketStack stack;
    for (int i = 0; i < LENGTH; i++) {
        char CURRENT = EXPRESSION[i];
        if (CURRENT == '(' || CURRENT == '[' || CURRENT == '{') {
            stack.PUSH(CURRENT);
        } else if (CURRENT == ')' || CURRENT == ']' || CURRENT == '}') {
            if (stack.EMPTY()) {
                return false;
            }
            char TOP = stack.POP();
            if ((CURRENT == ')' && TOP != '(') || (CURRENT == ']' && TOP != '[') || (CURRENT == '}' && TOP != '{')) {
                return false;
            }
        }
    }
    return stack.EMPTY();
}

int main() {
    string EXPRESSION;
    cout << "\033[1;32mENTER AN INFIX EXPRESSION: \033[1;0m";
    cin >> EXPRESSION;
    
    if (!CHECK_BRACKET(EXPRESSION)) {
        cout << "INVALID EXPRESSION DUE TO UNBALANCED BRACKETS." << endl;
        return 0;
    }

    cout << "\n\t\t\t\t\033[1;33mINFIX EXPRESSION \033[0m" << EXPRESSION;
    
    string POS_EXP = CONVERSION(EXPRESSION);
    cout << "\n\n\t\t\033[1;36mPOSTFIX EXPRESSION \033[1;0m" << POS_EXP;
//********************************************    
    string PREFIX_EXP = PREFIX(EXPRESSION);
    cout << "\t\t\033[1;36mPREFIX EXPRESSION \033[1;0m" << PREFIX_EXP;
    cout << "\n\033[1;35mANSWER: \033[1;0m" << SOLVE(POS_EXP);
    
    return 0;
}


// 4+6/2*5+7

