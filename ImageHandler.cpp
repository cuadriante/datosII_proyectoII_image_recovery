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

    for(x = 0; x < image.getSize().x; x++){

        for(y = 0; y < image.getSize().y; y++){
            Color colorAtImagePosition = image.getPixel(x, y);

            ColorInfo colorAtImagePositionInfo(colorAtImagePosition);

            if (!colorAtImagePositionInfo.isGrayScale()){
                bool exists = false;
                for(ColorInfo ci: colorList){
                    if (ci.isSimilar(&colorAtImagePositionInfo)){
                        exists = true;
                        image.setPixel(x, y, ci.getColor());
                        break;
                    }
                }

                if (!exists){
                    colorList.push_back(colorAtImagePositionInfo);
                    cout << "R: " << colorAtImagePositionInfo.getRed();
                    cout << " G: " << colorAtImagePositionInfo.getGreen();
                    cout << " B: " << colorAtImagePositionInfo.getBlue() << endl;
                } else {
                    cout << "Color already exists:" << colorAtImagePosition.toInteger() << endl;
                }
            } else {
                image.setPixel(x, y, Color::White);

            }

            ogImage.push_back(currentColorInt);

            if(colorAtImagePositionInfo.getRed() == 255 && colorAtImagePositionInfo.getGreen() == 255 && colorAtImagePositionInfo.getBlue() == 255){
                if (whiteRectangleCoordinates[0] == 0 && whiteRectangleCoordinates[1] == 0){
                    whiteRectangleCoordinates[0] = x;
                    whiteRectangleCoordinates[1] = y;
                } else {
                    whiteRectangleCoordinates[2] = x;
                    whiteRectangleCoordinates[3] = y;
                }
                whiteRectangle.push_back(colorAtImagePositionInfo);
            }
        }
    }
    image.saveToFile("out.png");
    printContents();
}


const Image &ImageHandler::getImage() const {
    return image;
}

void ImageHandler::printContents() {
    cout << "white rectangle coordinates: ";
    for(int i = 0; i < 4; i++){
        cout << whiteRectangleCoordinates[i];
        if (i == 3){
            cout << endl;
            break;
        }
        cout << ", ";
    }

    cout << "Found " << colorList.size() << " colors: ";
    for(ColorInfo ci: colorList){
        cout << "R: " << ci.getRed();
        cout << " G: " << ci.getGreen();
        cout << " B: " << ci.getBlue() << endl;
    }
}


