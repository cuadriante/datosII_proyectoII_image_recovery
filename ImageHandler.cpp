//
// Created by cuadriante on 10/10/21.
//

#include "ImageHandler.h"
#include "Population.h"

ImageHandler::ImageHandler(String imageName) {
    if (!image.loadFromFile(imageName)) {
        cout << "Error: Could not load image." << endl;
    }
}

[[noreturn]] void ImageHandler::storeImageAsPixels() {

    int x;
    int y;
    int currentColorInt = 0;

    for (x = 0; x < image.getSize().x; x++) {

        for (y = 0; y < image.getSize().y; y++) {
            Color colorAtImagePosition = image.getPixel(x, y);

            ColorInfo colorAtImagePositionInfo(colorAtImagePosition);

            if (!colorAtImagePositionInfo.isGrayScale()) {
                bool exists = false;
                for(int i = 0; i < colorList.size(); i++){
                    ColorInfo * ci = &colorList[i];
                //}
                //for (ColorInfo ci: colorList) {
                    if (ci->isSimilar(&colorAtImagePositionInfo)) {
                        ci->setFrequency(ci->getFrequency() + 1);
                        exists = true;
                        image.setPixel(x, y, ci->getColor());
                        break;
                    }
                }

                if (!exists) {
                    colorList.push_back(colorAtImagePositionInfo);
                    colorAtImagePositionInfo.setFrequency(colorAtImagePositionInfo.getFrequency() + 1);
                    cout << "R: " << colorAtImagePositionInfo.getRed();
                    cout << " G: " << colorAtImagePositionInfo.getGreen();
                    cout << " B: " << colorAtImagePositionInfo.getBlue() << endl;
                } else {
                    cout << "Color already exists:" << colorAtImagePosition.toInteger() << endl;
                }
            } else {
                image.setPixel(x, y, Color::White);
                colorAtImagePosition = Color::White;

            }

            ogImage.push_back(currentColorInt);

            if (colorAtImagePosition == Color::White) {
                if (whiteRectangleCoordinates[0] == 0 && whiteRectangleCoordinates[1] == 0) {
                    whiteRectangleCoordinates[0] = x;
                    whiteRectangleCoordinates[1] = y;
                } else {
                    whiteRectangleCoordinates[2] = x + 1;
                    whiteRectangleCoordinates[3] = y + 1;
                }
                whiteRectangle.push_back(colorAtImagePositionInfo);
            }
        }
    }

    calculateColorPercentages();
    saveChangesToImageFile();
    printContents();
    Population population(this);
    //recolorWhiteRectangle();
}


const Image &ImageHandler::getImage() const {
    return image;
}

void ImageHandler::printContents() {
    // white rectangle coordinates
    cout << "white rectangle coordinates: ";
    for (int i = 0; i < 4; i++) {
        cout << whiteRectangleCoordinates[i];
        if (i == 3) {
            cout << endl;
            break;
        }
        cout << ", ";
    }
    // colors found
    cout << "Found " << colorList.size() << " colors: ";
    for (ColorInfo ci: colorList) {
        cout << "R: " << ci.getRed();
        cout << " G: " << ci.getGreen();
        cout << " B: " << ci.getBlue();
        cout << " Occurrence: " << ci.getFrequency() << endl;
    }
}

void ImageHandler::recolorWhiteRectangle() {

    for (int x = whiteRectangleCoordinates[0]; x <= whiteRectangleCoordinates[2]; x++) {
        for (int y = whiteRectangleCoordinates[1]; y <= whiteRectangleCoordinates[3]; y++) {
            int index = rand() % colorList.size() ;
            Color newColor = colorList[index].getColor();
            image.setPixel(x, y, newColor);
        }
    }

    saveChangesToImageFile();
}

void ImageHandler::saveChangesToImageFile() {
    image.saveToFile("out.png");
}

void ImageHandler::calculateColorPercentages() {
    for(ColorInfo ci: colorList){
        double percentage = (ci.getFrequency() / colorList.size()) * 100;
        ci.setPercentage(percentage);
    }
}

const vector<ColorInfo> &ImageHandler::getWhiteRectangle() const {
    return whiteRectangle;
}

const vector<ColorInfo> &ImageHandler::getColorList() {
    return colorList;
}

const int *ImageHandler::getWhiteRectangleCoordinates() const {
    return whiteRectangleCoordinates;
}


