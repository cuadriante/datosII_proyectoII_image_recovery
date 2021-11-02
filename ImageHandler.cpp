//
// Created by cuadriante on 10/10/21.
//

#include "ImageHandler.h"
#include "Population.h"
#include "ImageInfo.h"

ImageHandler::ImageHandler(String imageName) {
    if (!image.loadFromFile(imageName)) {
        cout << "Error: Could not load image." << endl;
    }
}

[[noreturn]] void ImageHandler::analyzeImage() {

    int x;
    int y;
    // processes every pixel and analyzes
    for (x = 0; x < image.getSize().x; x++) {
        for (y = 0; y < image.getSize().y; y++) {
            Color colorAtImagePosition = image.getPixel(x, y);
            ColorInfo colorAtImagePositionInfo(colorAtImagePosition);
            if (!colorAtImagePositionInfo.isGrayScale()) {

                bool exists = false;
                for(int i = 0; i < colorList.size(); i++){
                    ColorInfo ci = colorList[i];
                    if (ci.isSimilar(&colorAtImagePositionInfo)) {
                        exists = true;
                        colorAtImagePositionInfo.setColor(ci.getColor());
                        break;
                    }
                }
                if (!exists) {
                    colorList.push_back(colorAtImagePositionInfo);
                    cout << "R: " << colorAtImagePositionInfo.getRed();
                    cout << " G: " << colorAtImagePositionInfo.getGreen();
                    cout << " B: " << colorAtImagePositionInfo.getBlue() << endl;
                } else {
                    image.setPixel(x, y, colorAtImagePositionInfo.getColor());
                    //cout << "Color already exists:" << colorAtImagePosition.toInteger() << endl;
                }
            } else {
                image.setPixel(x, y, Color::White);
                colorAtImagePosition = Color::White;
            }
            imageContent.push_back(colorAtImagePosition);
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

    saveChangesToImageFile();
    printContents();
    startGeneticAlgorithm();
}

void ImageHandler::startGeneticAlgorithm() {
    ImageInfo idealCharacteristics(&imageContent, image.getSize().x, image.getSize().y, &colorList);
    //idealCharacteristics.debug();
    Population population(this, &idealCharacteristics, &colorList);
    population.setMaxGeneration(10000);
    population.createInitialPopulation();
    while (population.getGeneration() < population.getMaxGeneration()){
        population.selection();
        population.crossover();
    }
}

void ImageHandler::printContents() {
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
    }
    cout << endl;
}

void ImageHandler::recolorInitialWhiteRectangle() {
    srand((unsigned int)time(NULL));
    for (int x = whiteRectangleCoordinates[0]; x <= whiteRectangleCoordinates[2]; x++) {
        for (int y = whiteRectangleCoordinates[1]; y <= whiteRectangleCoordinates[3]; y++) {
            int index = rand() % colorList.size() ;
            Color newColor = colorList[index].getColor();
            image.setPixel(x, y, newColor);
        }
    }

    saveChangesToImageFile();
}

void ImageHandler::recolorWhiteRectangle(vector<Color> * newPixelSet, int width, int height) {
    for (int x = 0; x < width; x++){
        for(int y = 0; y < height; y++){
            Color newColor = newPixelSet->at(x + y*width);
            image.setPixel(x+whiteRectangleCoordinates[0], y+whiteRectangleCoordinates[1], newColor);
        }
    }
//    for (int x = whiteRectangleCoordinates[0]; x <= whiteRectangleCoordinates[2]; x++) {
//        for (int y = whiteRectangleCoordinates[1]; y <= whiteRectangleCoordinates[3]; y++) {
//            int index = x + y*(whiteRectangleCoordinates[2]-whiteRectangleCoordinates[0]) ;
//            Color newColor = newPixelSet[index];
//            image.setPixel(x, y, newColor);
//        }
//    }
    saveChangesToImageFile();
}

void ImageHandler::saveChangesToImageFile() {
    image.saveToFile("out.png");
}

const vector<ColorInfo> &ImageHandler::getWhiteRectangle() const {
    return whiteRectangle;
}

vector<ColorInfo> &ImageHandler::getColorList() {
    return colorList;
}

const int *ImageHandler::getWhiteRectangleCoordinates() const {
    return whiteRectangleCoordinates;
}

const Image &ImageHandler::getImage() const {
    return image;
}

