/*
 *
 *        苎夏星染
 *
 *      2022.11.16
 *
 */


#include <iostream>
#include <string>

#define Maxsize 20
using namespace std;

struct SqStack {
    float data[Maxsize];
    string sym;
    int data_top;
    int sym_top;
};

void InitStack(SqStack &S) {
    S.data_top = -1;
    S.sym_top = -1;
}

bool StackSymEmpty(SqStack &S) {
    if (S.sym_top == -1)
        return true;
    return false;
}

bool StackDataEmpty(SqStack &S) {
    if (S.data_top == -1)
        return true;
    return false;
}

bool Push(SqStack &S, float x) {
    if (S.data_top == Maxsize - 1)
        return false;
    S.data[++S.data_top] = x;
    return true;
}

bool Push(SqStack &S, char x) {
    if (S.sym_top == Maxsize - 1)
        return false;
    S.sym[++S.sym_top] = x;
    return true;
}

bool Pop(SqStack &S, float &x) {
    if (StackDataEmpty(S))
        return false;
    x = S.data[S.data_top--];
    return true;
}

bool Pop(SqStack &S, char &x) {
    if (StackSymEmpty(S))
        return false;
    x = S.sym[S.sym_top--];
    float temp1, temp2;
    if (x == '+') {
        Pop(S, temp2);
        Pop(S, temp1);
        Push(S, temp1 + temp2);
    }
    if (x == '-') {
        Pop(S, temp2);
        Pop(S, temp1);
        Push(S, temp1 - temp2);
    }
    if (x == '*') {
        Pop(S, temp2);
        Pop(S, temp1);
        Push(S, temp1 * temp2);
    }
    if (x == '/') {
        Pop(S, temp2);
        Pop(S, temp1);
        Push(S, temp1 / temp2);
    }
    return true;
}

bool GetTop(SqStack &S, float &x) {
    if (StackDataEmpty(S))
        return false;
    x = S.data[S.data_top];
    return true;
}



int main() {
    SqStack S;
    InitStack(S);
    string str, str_temp;
    int sign = 0, flo = 0, num;
    float num1;
    char x;
    cin >> str;
    int a=int(str.length());
    if (str[0] == '-')
    {
        str.insert(0, "(");
        a++;
        int gy=2;
        for (gy=2;true;gy++)
        {
            if (str[gy] == '+' || str[gy] == '-' || str[gy] == '*' || str[gy] == '/')
            {
                break;
            }
        }
        str.insert(gy, ")");
        a++;
    }
    for (int i = 0; i < a; i++) {
        if (str[i] == '(' && str[i + 1] == '-') {
            str.insert(i+1, "0");
            a++;
        }
    }
     while (!str.empty()) {
         if(str[sign]=='.')
             flo=1;
         if (str[sign] == '+' || str[sign] == '-' || str[sign] == '*' || str[sign] == '/' || str[sign] == '(' ||
             str[sign] == ')' || str[sign] == '=') {
             if (sign == 0 &&
                 (str[sign] == '-' || str[sign] == '(' || str[sign] == '+' || str[sign] == '*' || str[sign] == '/')) {
                 if (str[sign] == '+') {
                     while (!StackSymEmpty(S) && S.sym[S.sym_top] != '(') {
                         Pop(S, x);
                     }
                     Push(S, str[sign]);
                 }
                 if (str[sign] == '-') {
                     while (!StackSymEmpty(S) && S.sym[S.sym_top] != '(') {
                         Pop(S, x);
                     }
                     Push(S, str[sign]);
                 }
                 if (str[sign] == '*') {
                     while (S.sym[S.sym_top] == '*' || S.sym[S.sym_top] == '/') {
                         Pop(S, x);
                     }
                     Push(S, str[sign]);
                 }
                 if (str[sign] == '/') {
                     while (S.sym[S.sym_top] == '*' || S.sym[S.sym_top] == '/') {
                         Pop(S, x);
                     }
                     Push(S, str[sign]);
                 }
                 if (str[sign] == '(')
                     Push(S, str[sign]);
                 str.erase(0, 1);
                 continue;
             }
             if ((str[sign] == ')' && (str[sign - 1] >= '0' && str[sign - 1] <= '9')) || str[sign] == '+' ||
                 str[sign] == '-' || str[sign] == '*' || str[sign] == '/' || str[sign] == '=') {
                 if(flo==0) {
                     num = stoi(str, nullptr, 10);
                     Push(S, float(num));
                 }
                 if(flo==1){
                     num1=stof(str, nullptr);
                     Push(S,num1);
                     flo=0;
                 }
             }
             if (str[sign] == '+') {
                 while (!StackSymEmpty(S) && S.sym[S.sym_top] != '(') {
                     Pop(S, x);
                 }
                 Push(S, str[sign]);
             }
             if (str[sign] == '-') {
                 while (!StackSymEmpty(S) && S.sym[S.sym_top] != '(') {
                     Pop(S, x);
                 }
                 Push(S, str[sign]);
             }
             if (str[sign] == '*') {
                 while (S.sym[S.sym_top] == '*' || S.sym[S.sym_top] == '/') {
                     Pop(S, x);
                 }
                 Push(S, str[sign]);
             }
             if (str[sign] == '/') {
                 while (S.sym[S.sym_top] == '*' || S.sym[S.sym_top] == '/') {
                     Pop(S, x);
                 }
                 Push(S, str[sign]);
             }
             if (str[sign] == ')') {
                 while (S.sym[S.sym_top] != '(') {
                     Pop(S, x);
                 }
                 Pop(S, x);
                 if (str[sign + 1] == '=') {
                     while (!StackSymEmpty(S)) {
                         Pop(S, x);
                     }
                     break;
                 }
             }
             if (str[sign] == '=') {
                 while (!StackSymEmpty(S)) {
                     Pop(S, x);
                 }
                 break;
             }
             str.erase(0, sign + 1);
             sign = -1;
         }
         sign++;
     }
     GetTop(S, num1);
     cout << num1;

}