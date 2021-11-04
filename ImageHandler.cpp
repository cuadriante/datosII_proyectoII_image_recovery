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

[[noreturn]] void ImageHandler::analyzeImage(String imageName) {

    if (!image.loadFromFile(imageName)) {
        cout << "Error: Could not load image." << endl;
    }

    int x;
    int y;

    imageContent.clear();
    imageContent.reserve(image.getSize().x*image.getSize().y);
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
                        imageContent.push_back(i);
                        colorAtImagePositionInfo.setColor(ci.getColor());
                        break;
                    }
                }
                if (!exists) {
                    colorList.push_back(colorAtImagePositionInfo);
                    imageContent.push_back(colorList.size() - 1);
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
                imageContent.push_back(-1);
            }
            //imageContent.push_back(colorAtImagePosition);
            if (colorAtImagePosition == Color::White) {
                if (whiteRectangleCoordinates[0] == 0 && whiteRectangleCoordinates[1] == 0) {
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

    saveChangesToImageFile(0);
    printContents();
    //startGeneticAlgorithm(10000);
}

vector<char> ImageHandler::createIdealGenome() {
    whiteRectangleWidth = whiteRectangleCoordinates[2] - whiteRectangleCoordinates[0] + 1;
    whiteRectangleHeight = whiteRectangleCoordinates[3] - whiteRectangleCoordinates[1] + 1;
    vector<char> idealGenome;

    int startPointX = whiteRectangleCoordinates[0] - whiteRectangleWidth + 1;
    int startPointY =  whiteRectangleCoordinates[3] + 1;

    for (int x = 0; x < whiteRectangleWidth; x++) {
        for (int y = 0; y < whiteRectangleHeight; y++) {
            Color colorAtImagePosition = image.getPixel(whiteRectangleCoordinates[0] - whiteRectangleWidth + x, whiteRectangleCoordinates[3] + y);
            ColorInfo colorAtImagePositionInfo(colorAtImagePosition);

            for (int i = 0; i < colorList.size(); i++) {
                ColorInfo ci = colorList[i];
                if (ci.getColor() == colorAtImagePositionInfo.getColor()) {
                    idealGenome.push_back(i);
                    break;
                }
            }
        }
        }

//    for (int x = startPointX; x < (startPointX + whiteRectangleWidth); x++) {
//        for (int y = startPointY; y < (startPointY + whiteRectangleHeight); y++) {
//            Color colorAtImagePosition = image.getPixel(x, y);
//            ColorInfo colorAtImagePositionInfo(colorAtImagePosition);
//
//            for(int i = 0; i < colorList.size(); i++){
//                ColorInfo ci = colorList[i];
//                if (ci.isSimilar(&colorAtImagePositionInfo)) {
//                    idealGenome.push_back(i);
//                    break;
//                }
//            }
//
//        }
//    }
    //ImageInfo idealCharacteristics(idealGenome, whiteRectangleWidth, whiteRectangleHeight, &colorList);
    return idealGenome;
}

void ImageHandler::startGeneticAlgorithm(int maxGeneration) {
    vector<char> idealGenome = createIdealGenome();
    //createIdealGenome();
    ImageInfo idealRectangleCharacteristics(idealGenome, whiteRectangleWidth, whiteRectangleHeight, &colorList);

    //ImageInfo imageCharacteristics(imageContent, image.getSize().x, image.getSize().y, &colorList);
    //idealRectangleCharacteristics.debug();
   // recolorWhiteRectangle(idealGenome, whiteRectangleWidth + 1, whiteRectangleHeight + 1);
    Population population(this, &idealRectangleCharacteristics, &colorList);
    population.setMaxGeneration(maxGeneration);
    population.createInitialPopulation();
    while (population.getGeneration() < population.getMaxGeneration()){
        population.selection();
        population.crossover();
    }
   //recolorWhiteRectangle(idealRectangleCharacteristics.getImageContent(), whiteRectangleWidth, whiteRectangleHeight, 1);
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

    saveChangesToImageFile(0);
}

void ImageHandler::recolorWhiteRectangle(const vector<char> &newPixelSetIndex, int width, int height, int generation) {
    for (int x = 0; x < width; x++){
        for(int y = 0; y < height; y++){
            Color newColor = colorList[newPixelSetIndex.at(y + x * height)].getColor();
            image.setPixel(x+whiteRectangleCoordinates[0], y+whiteRectangleCoordinates[1], newColor);
        }
    }
    saveChangesToImageFile(generation);
}

void ImageHandler::saveChangesToImageFile(int generation) {
//    image.saveToFile("output/out.png");
    image.saveToFile("output/out" + to_string(generation - 1) + ".png");
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

ImageHandler::ImageHandler() {

}

