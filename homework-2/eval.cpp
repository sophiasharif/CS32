#include "Set.h"  // with ItemType being a type alias for char
#include <iostream>
#include <string>
#include <stack>
#include <cctype>
#include <cassert>
using namespace std;


// HELPER FUNCTION DECLARATIONS
bool toPostfix(string infix, string& postfix);
bool hasValidOperands(const string& postfix, int& returnCode, const Set& trueValues, const Set& falseValues);
bool eval(string postfix, const Set& trueValues);
int opComp(char op1, char op2);
char nextValidChar(string str, int i);

// EVALUATE FUNCTION
int evaluate(string infix, const Set& trueValues, const Set& falseValues, string& postfix, bool& result) {
    
    if(!toPostfix(infix, postfix)) return 1;
    
    int returnCode = 0;
    if (!hasValidOperands(postfix, returnCode, trueValues, falseValues))
        return returnCode;
    
    result = eval(postfix, trueValues);
    
    return 0;
}

// HELPER FUNCTION IMPLEMENTATIONS
int opComp(char op1, char op2) {
    
    string operatorValues = "|&!"; // index correspondes to precedence
    unsigned long op1val = operatorValues.find(op1);
    unsigned long op2val = operatorValues.find(op2);
    
    if (op1val == op2val) return 0;
    else if (op1val > op2val) return 1;
    else return -1;
}

char nextValidChar(string str, int i) {
    while (i+1 != str.length() && isspace(str.at(i+1))) i++;
    if (i+1 == str.length()) return '\0';
    return str.at(i+1);
}

bool toPostfix(string infix, string& postfix) {
    
    // check infix is not empty
    if (infix.length() == 0 || infix.find_first_not_of(' ') == string::npos) return false;
    
    postfix = "";
    stack<char> oStack;
    
    for (int i=0; i<infix.length(); i++) {
        char ch = infix.at(i);
        
        if (isspace(ch))
            continue;
        
        
        if (ch == ')' || islower(ch)) {
            
            // error checking: next char must be &, |, ), or end of string
            char next = nextValidChar(infix, i);
            if (!( next == '&' || next == '|' || next == ')' || next == '\0' ))
                return false;
            
            // handle lowercase letter
            if (islower(ch)) {
                postfix += ch;
                continue;
            }
            
            // handle parentheses
            while (!oStack.empty() && oStack.top() != '(') {
                postfix += oStack.top();
                oStack.pop();
            }
            // if there's no matching left parentheses, return false
            if (oStack.empty()) return false;
            // pop the open parentheses
            oStack.pop();
            continue;
        }
        
        if (ch == '|' || ch == '&' || ch == '!' || ch == '(') {
            
            // next char must exist, and must be a letter, (, or !
            char next = nextValidChar(infix, i);
            if (!next) return false;
            if (!( islower(next) || next == '(' || next == '!' ))
                return false;
            
            if (ch == '&' || ch == '|') {
                // check that at least one letter has been added to postfix
                if (postfix.size() == 0) return false;
            
                while (!oStack.empty() && oStack.top() != '(' && (opComp(ch, oStack.top()) <= 0)){
                    postfix += oStack.top();
                    oStack.pop();
                }
            }
            
            oStack.push(ch);
            continue;
        }
        return false;
                
    }
    
    // add last chars
    while (!oStack.empty()) {
        postfix += oStack.top();
        oStack.pop();
    }
    
    // last error checking
    if (postfix.find(')') != string::npos || postfix.find('(') != string::npos)
        return false;
    
    return true;
}

bool hasValidOperands(const string& postfix, int& returnCode, const Set& trueValues, const Set& falseValues) {
    for(int i=0; i != postfix.length(); i++) {
        char c = postfix[i];
        if (!islower(c)) continue;
        
        if (!trueValues.contains(c) && !falseValues.contains(c)) {
            returnCode = 2;
            return false;
        }
        
        if (trueValues.contains(c) && falseValues.contains(c)) {
            returnCode = 3;
            return false;
        }
    }
    
    return true;
}

bool eval(string postfix, const Set& trueValues) {
    
    stack<bool> bStack;
    
    for (int i=0; i != postfix.length(); i++){
        
        char c = postfix.at(i);
        
        if (c == '!') {
            bool res = !bStack.top();
            bStack.pop();
            bStack.push(res);
        }
        
        else if (c == '&') {
            bool b1 = bStack.top();
            bStack.pop();
            bool b2 = bStack.top();
            bStack.pop();
            bStack.push(b1 && b2);
        }
        
        else if (c == '|') {
            bool b1 = bStack.top();
            bStack.pop();
            bool b2 = bStack.top();
            bStack.pop();
            bStack.push(b1 || b2);
        }
        
        else if (trueValues.contains(c))
            bStack.push(true);
        
        else
            bStack.push(false);
        
    }
    
    return bStack.top();
}

int main()
{
   string trueChars  = "tywz";
   string falseChars = "fnx";
   Set trues;
   Set falses;
   for (int k = 0; k < trueChars.size(); k++)
       trues.insert(trueChars[k]);
   for (int k = 0; k < falseChars.size(); k++)
       falses.insert(falseChars[k]);

   string pf;
   bool answer;
   assert(evaluate("w| f", trues, falses, pf, answer) == 0  &&  pf == "wf|" &&  answer);
   assert(evaluate("y|", trues, falses, pf, answer) == 1);
   assert(evaluate("n t", trues, falses, pf, answer) == 1);
   assert(evaluate("nt", trues, falses, pf, answer) == 1);
   assert(evaluate("()", trues, falses, pf, answer) == 1);
   assert(evaluate("()z", trues, falses, pf, answer) == 1);
   assert(evaluate("y(n|y)", trues, falses, pf, answer) == 1);
   assert(evaluate("t(&n)", trues, falses, pf, answer) == 1);
   assert(evaluate("(n&(t|y)", trues, falses, pf, answer) == 1);
   assert(evaluate("n+y", trues, falses, pf, answer) == 1);
   assert(evaluate("", trues, falses, pf, answer) == 1);
   assert(evaluate("f  |  !f & (t&n) ", trues, falses, pf, answer) == 0
                          &&  pf == "ff!tn&&|"  &&  !answer);
   assert(evaluate(" x  ", trues, falses, pf, answer) == 0  &&  pf == "x"  &&  !answer);
   trues.insert('x');
   assert(evaluate("((x))", trues, falses, pf, answer) == 3);
   falses.erase('x');
   assert(evaluate("((x))", trues, falses, pf, answer) == 0  &&  pf == "x"  &&  answer);
   trues.erase('w');
   assert(evaluate("w| f", trues, falses, pf, answer) == 2);
   falses.insert('w');
   assert(evaluate("w| f", trues, falses, pf, answer) == 0  &&  pf == "wf|" &&  !answer);
}
