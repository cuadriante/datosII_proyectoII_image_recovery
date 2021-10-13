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
    int previousColorR = 0;
    int currentSignedColorG = 0;
    int previousColorG = 0;
    int currentSignedColorB = 0;
    int previousColorB = 0;
    int previousColorInt = 0;

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

            if(currentColorInt == -1){
                if (whiteRectangleCoordinates[0] == 0 && whiteRectangleCoordinates[1] == 0){
                    whiteRectangleCoordinates[0] = x;
                    whiteRectangleCoordinates[1] = y;
                }

                whiteRectangle.push_back(currentColorInt);
            }
        }
    }

    image.saveToFile("/home/cuadriante/CLionProjects/datosII_proyectoII_image_recovery/images/out.png");

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

int ImageHandler::getHue(int red, int green, int blue) {
    double minv = min(min(red, green), blue);
    double maxv = max(max(red, green), blue);

    if (minv == maxv) {
        return 0;
    }

    double hue = 0.0;
    if (maxv == red) {
        hue = (green - blue) / (maxv - minv);

    } else if (maxv == green) {
        hue = 2.0 + (blue - red) / (maxv - minv);

    } else {
        hue = 4.0 + (red - green) / (maxv - minv);
    }

    hue = hue * 60;
    //if (hue < 0) hue = hue + 360;
    hue = hue + 0.5 - (hue<0);

    return (int) hue;
}

const Image &ImageHandler::getImage() const {
    return image;
}


