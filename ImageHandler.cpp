//
// Created by cuadriante on 10/10/21.
//

#include "ImageHandler.h"

ImageHandler::ImageHandler(String imageName) {
    if(!image.loadFromFile(imageName)){
        cout << "Error: Could not load image." << endl;
    }
}

[[noreturn]] void ImageHandler::storeImageAsPixels() {

    int x;
    int y;
    int currentColorInt = 0;
    int currentSignedColorR = 0;
    int currentSignedColorG = 0;
    int currentSignedColorB = 0;
    int previousColorInt = 0;

    for(x = 0; x < 550; x++){

        for(y = 0; y < 550; y++){
            Color colorAtImagePosition = image.getPixel(x, y);

            currentColorInt = (int) colorAtImagePosition.toInteger();
            currentSignedColorR = (int) colorAtImagePosition.r;
            currentSignedColorG = (int) colorAtImagePosition.g;
            currentSignedColorB = (int) colorAtImagePosition.b;

            if(previousColorInt != currentColorInt){

                cout << "32 bit color: " << currentColorInt;
                cout << " R: " << currentSignedColorR;
                cout << " G: " << currentSignedColorG;
                cout << " B: " << currentSignedColorB;
                cout << " in x: " << x << " and y: " << y << endl;

                //todo: add range for similar colors
                if (previousColorInt == -1){
                    whiteRectangleCoordinates[3] = y - 1;
                    whiteRectangleCoordinates[2] = x - 1;
                }
                previousColorInt = currentColorInt;
            }

            ogImage.push_back(currentColorInt);

            if(currentSignedColorR == 255 && currentSignedColorG == 255 && currentSignedColorB == 255){
                if (whiteRectangleCoordinates[0] == 0 && whiteRectangleCoordinates[1] == 0){
                    whiteRectangleCoordinates[0] = x;
                    whiteRectangleCoordinates[1] = y;
                }

                whiteRectangle.push_back(currentColorInt);
            }

        }


    }

    cout << "white rectangle coordinates: ";
    for(int i = 0; i < 4; i++){
        cout << whiteRectangleCoordinates[i];
        if (i == 3){
            cout << endl;
            break;
        }
        cout << ", ";
    }
}
