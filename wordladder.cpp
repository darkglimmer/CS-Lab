// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#include <cctype>
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include <stack>
#include <set>
#include "console.h"
#include "stack.h"
#include "simpio.h"
#include "queue.h"
#include "vector.h"
#include "lexicon.h"

using namespace std;

string tolower(string str);
void outputword(Stack<string>result,string w1,string w2);

int main() {
    string w1;
    string w2;
    string dic;
    ifstream infile;
    Vector<string>lines;
    cout << "Welcome to CS 106B Word Ladder." << endl ;
    cout << "Please give me two English words, and I will change the " << endl ;
    cout << "first into the second by changing one letter at a time." << endl ;
    while(1){
        cout << "Dictionary file name?" << endl ;
        cin>>dic;
        infile.open(dic.c_str());
        if (infile.fail()){
             cout<<"Unable to open that file.  Try again.";
             infile.clear();
        }
        else{
             Lexicon dic;
             break;
        }
    }

    while (1){
        cout << "Word #1 (or Enter to quit):" << endl ;
        cin >> w1 ;
        cout << "Word #2 (or Enter to quit):" << endl ;
        cin >> w2 ;
        Lexicon dic;
        if(w1[0] == 'Q'||w2[0] == 'Q'){
           cout << "Have a nice day." << endl;
           break;
        }
        w1 = tolower(w1) ;
        w2 = tolower(w2) ;
        if(dic.contains(w1) && dic.contains(w2)){
            if(w1.length() == w2.length()){
                if(w1 != w2){
                    cout << "A ladder from " << w2 << " back to " << w1 << ":" << endl;
                    Queue<Stack<string>> queue;
                    Stack<string> first;
                    Stack<string> stack;
                    Stack<string> result;
                    first.push(w1);
                    queue.enqueue(first);
                    while(!queue.isEmpty()){
                        stack = queue.dequeue();
                        string word = stack.peek();
                        for(int i = 0;i < word.length();i++){
                            string ladder = word;
                            for(int n=97;n<=122;n++){
                                ladder[i]=n;
                                if(dic.contains(ladder))
                                    stack.push(ladder);
                                    dic.remove(ladder);
                                    if(ladder==w2){
                                         result = stack;
                                    }
                                    stack.push(ladder);
                                    queue.enqueue(stack);
                                    string used=stack.pop();
                                }
                            }
                        }
                    if(!result.isEmpty()){
                       outputword(result,w1,w2);
                       break;
                    }
                }
                else{
                    cout<<"The two words must be different.";
                }
            }
            else{
                cout<<"The two words must be the same length.";
            }
        }
        else {
            cout<<"The two words must be found in the dictionary.";
        }
    }
    return 0;
}

string tolower(string str){
    for ( int i = 0 ; i < str.length() ; i++ )
        str[i] = tolower(str[i]) ;
    return str ;
}
void outputword(Stack<string>result,string w1,string w2){
    if(result.isEmpty()){
        cout<<"No Word Latter from "<<w2<<" to "<<w1<<endl;
    }
    else if(!result.isEmpty()){
        cout << "Ladder From "<<w2<<" back to "<<w1<<":"<< endl;
        while(!result.isEmpty()){
            cout << result.pop() <<"  ";
        }
    }
}