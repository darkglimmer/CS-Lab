/* 
 * TODO: put your own comments here. Also you should leave comments on
 * each of your methods.
 */

#include <math.h>
#include "recursion.h"
#include "map.h"
#include "vector.h"
#include "set.h"
#include "gwindow.h"
#include "gobjects.h"
#include "tokenscanner.h"
using namespace std;

int gcd(int a, int b) {
    if ( b == 0 ){
            cout << "gcd(" << a << ", " << b << ") = " << a << endl;
            return a ;
        }
        else {
            cout << "gcd(" << a << ", " << b << ") = gcd(" << b << ", " << a%b << ")" << endl;
            return gcd(b ,a % b) ;
        }

    return 0;
}

void serpinskii(GWindow &w, int leftX, int leftY, int size, int order) {
    if(order == 0);
    else if(order < 0){
        cout << "wrong" << endl;
    }
    else if(order == 1){
        w.drawLine(leftX, leftY, size + leftX, leftY);
        w.drawLine(size + leftX, leftY, size / 2 + leftX, size * (sqrt(3) / 2) + leftY);
        w.drawLine(size / 2 + leftX, size * sqrt(3) / 2 + leftY, leftX, leftY);
    }
    else{
        w.drawLine(leftX + size / 2, leftY, leftX + size / 4, leftY + (sqrt(3) * size) / 4);
        w.drawLine(leftX + size / 2, leftY, leftX + 3 * size / 4, leftY + (sqrt(3) * size) / 4);
        w.drawLine(leftX + size / 4, leftY + (sqrt(3) * size) / 4, leftX + size / 2, leftY + (sqrt(3) * size) / 4);
        serpinskii(w, leftX, leftY, size / 2, order - 1 ) ;
        serpinskii(w, leftX + size / 2, leftY, size / 2, order - 1 ) ;
        serpinskii(w, leftX + size / 4, leftY + size * sqrt(3) / 4, size / 2, order - 1 ) ;
    }
}

int ChangeColor(GBufferedImage& image, int x, int y, int newColor, int old){
    if (image.inBounds(x, y) && image.getRGB(x, y) == old){
        image.setRGB(x, y, newColor);
        return 1 + ChangeColor(image, x, y + 1, newColor, old) + ChangeColor(image, x, y - 1, newColor, old) + ChangeColor(image, x + 1, y, newColor, old) + ChangeColor(image, x - 1, y, newColor, old);
    }
    else{
        return 0;
    }
}

int floodFill(GBufferedImage& image, int x, int y, int newColor) {
    if(image.getRGB(x, y) != newColor){
         return ChangeColor(image, x, y, newColor, image.getRGB(x, y));
    }
    else {
        return 0;
    }
}

Map <string, int> printed;//放在函数外
void personalCurriculum(Map<string, Vector<string>> & prereqMap,string goal){
    if(!prereqMap.containsKey(goal) && !printed.containsKey(goal)){
        cout << goal << endl;
        printed.put(goal,1);
        return;
    }
    else{
        for(int i = 0; i < prereqMap.get(goal).size(); i++){
            personalCurriculum(prereqMap, prereqMap.get(goal).get(i));
            if(!printed.containsKey(prereqMap.get(goal).get(i))){
                cout << prereqMap.get(goal).get(i) << endl;
                printed.put(prereqMap.get(goal).get(i), 1);
            }
        }
    }
}

string generate(Map<string, Vector<string> > & grammar, string symbol){
    string str;
    if(grammar.containsKey(symbol)){
        string random = grammar.get(symbol).get(randomInteger(0, grammar.get(symbol).size() - 1));
        TokenScanner Scanner(random);
        while (Scanner.hasMoreTokens()) {//如果还有其他更多的token未被读取，返回true
            string newToken = Scanner.nextToken();
            str += generate(grammar,newToken);
        }
    }
    else{
        str += symbol;
    }

    return str;
}
