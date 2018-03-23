// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#include <cctype>
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include <stack>
#include "console.h"
#include "random.h"
#include "vector.h"
#include "map.h"
#include "filelib.h"
#include "tokenscanner.h"


using namespace std;
void GenerateMap(TokenScanner & scan, int n, Map<Vector<string>,Vector<string>> map, Vector<Vector<string>> &keys);
void Generateword(Vector<string> & inital,Map<Vector<string>,Vector<string>> map,Vector<string> &res,int number);

int main() {
    string name;
    int N, number;
    ifstream infile;
    cout<<"Welcome to CS 106B Random Writer ('N-Grams')."<<endl;
    cout<<"This program makes random text based on a document."<<endl;
    cout<<"Give me an input file and an 'N' value for groups"<<endl;
    cout<<"of words, and I'll create random text for you."<<endl;
    
    Map<Vector<string>,Vector<string>> map;
    Vector<Vector<string>> keys;
    
    while (1) {
        cout << "Input file name?"  << endl;
        cin >> name;
        infile.open(name.c_str()) ;
        if (!infile.fail()){
            break;
        }
        else {
            cout << "Unable to open that file. " << endl ;
            infile.clear() ;
        }
    }
    
    TokenScanner scanner(infile);
    scanner.ignoreWhitespace();
    while(1){
        cout<<"Value of N?"<<endl;
        cin>>N;
        if(N >= 2){
            break;
        }
        else{
            cout<<"N must be 2 or greater."<<endl;
        }
    }
    if(scanner.hasMoreTokens()){
        GenerateMap(scanner,N,map,keys);
    }
    
    while(1){
        cout << "# of random words to generate (0 to quit)?" << endl;
        int number;
        cin >> number;
        if (number == 0){
            cout << "Exiting." << endl;
            break;
        }
        int size = map.size();
        int start = randomInteger(0, size -1);
        Vector<string> res;
        Vector<string> inital = keys[start];
        res = inital;
        Generateword(inital,map,res,number);
        cout << "...";
        for (int i = 0; i < res.size(); i++){
            cout << res[i] << " ";
        }
        cout << "..." << endl;
    }
    return 0;
}

void GenerateMap(TokenScanner & scan, int n, Map<Vector<string>,Vector<string>> map, Vector<Vector<string>> &keys){
    Vector<string> key;
    string value = scan.nextToken();
    while(value!=""){
        key.add(scan.nextToken());
        value=scan.nextToken();
    }
    Vector<string>mean;
    if(map.containsKey(key)){
        mean= map.get(key);
        mean.add(value);
        map.put(key,mean);
    }
    else {
        mean.add(value);
        map.put(key,mean);
        keys.add(key);
    }
}

void Generateword(Vector<string> & inital,Map<Vector<string>,Vector<string>> map,Vector<string> &res,int number){
    while (res.size() <= number){
        Vector<string> former;
        former = map.get(inital) ;
        int point = randomInteger(0,former.size()-1);
        res.add(former[point]);
        former.remove(0);
        inital.add(former[point]);
    }
}

