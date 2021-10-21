#include <iostream>
#include<SFML/Graphics.hpp>
#include <valarray>
#include "ImageHandler.h"
#include "StrategyTest.h"

using namespace sf;

double diff(vector<int> v1, vector<int> v2){
    double d = 0.0;
    for(int i = 0; i < v1.size(); i++){
        double a = v1[i];
        double b = v2[i];
        d = d + a*a - b*b;
    }
    d = sqrt(d);
    cout << d << endl;
    return d;
}

int main() {
//    vector<int> vector1 = {5,7,8};
//    vector<int> vector2;
//
//    StrategyTest st;
//    StrategyTest bestst;
//
//    double previousBest = 800;
//    vector<int> bestVector = vector2;
//
//    for(int times = 0; times < 500; times ++){
//        st = bestst;
//        st.mutate();
//        vector2.clear();
//
//        for(int i = 0; i < vector1.size(); i++){
//            int y = st.f(i);
//            vector2.push_back(y);
//        }
//
//        double d = diff(vector1, vector2);
//
//        if ( d < previousBest){
//            bestst = st;
//            bestVector = vector2;
//            bestst.increasePrecision();
//        } else {
//            if (!(d > previousBest)){
//                bestst.decreasePrecision();
//            }
//        }
//
//    }
//
//    for(int x:vector1){
//        cout << x;
//    }
//    cout << endl;
//
//    for(int x:bestVector){
//        cout<< x;
//    }
//
//    cout<< endl;
//
//    cout << diff(vector1, vector2) << endl;
//
//


    ImageHandler imageHandler("brownPattern.png");


    //sfml window
    RenderWindow window (VideoMode(1000, 800), "Image Recovery");
    while (window.isOpen())
    {
        Event event;
        while(window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }
        window.clear(Color(23,57,84,255));
        window.display();
        imageHandler.storeImageAsPixels();
    }
    return 0;
}
