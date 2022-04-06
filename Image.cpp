//
// Created by floodd on 23/03/2022.
//
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include "Image.h"
using namespace std;


bool Image::load(string filename)
{
    ifstream ifs;
    ifs.open(filename, ios::binary);
    // need to spec. binary mode for Windows users

    try {
        if (ifs.fail()) {
            throw("Can't open input file");
        }
        string header;
        int w, h, b;
        ifs >> header;
        if (strcmp(header.c_str(), "P6") != 0) throw("Can't read input file");
        ifs >> w >> h >> b;
        this->w = w;
        this->h = h;
        this->pixels = new Rgb[w * h]; // this is throw an exception if bad_alloc
        ifs.ignore(256, '\n'); // skip empty lines in necessary until we get to the binary data
        unsigned char pix[3]; // read each pixel one by one and convert bytes to floats
        for (int i = 0; i < w * h; ++i) {
            ifs.read(reinterpret_cast<char *>(pix), 3);
            this->pixels[i].r = pix[0];
            this->pixels[i].g = pix[1];
            this->pixels[i].b = pix[2];
        }
        ifs.close();
    }
    catch (const char *err) {
        fprintf(stderr, "%s\n", err);
        ifs.close();
        return false;
    }


    return true;

}
bool Image::loadRaw(string filename)
{




    return false;
}
bool Image::savePPM(string filename)
{
    if (this->w == 0 || this->h == 0) { fprintf(stderr, "Can't save an empty image\n"); return false; }
    std::ofstream ofs;
    try {
        ofs.open(filename, std::ios::binary); // need to spec. binary mode for Windows users
        if (ofs.fail()) throw("Can't open output file");
        ofs << "P6\n" << this->w << " " << this->h << "\n255\n";
        float r, g, b;

        // loop over each pixel in the image, clamp and convert to byte format
        for (int i = 0; i < this->w * this->h; ++i) {
            r = (float) this->pixels[i].r;
            g = (float) this->pixels[i].g;
            b = (float) this->pixels[i].b;
            ofs << r << g << b;
        }
        cout << "r " << r<<"g " << g<<"b " << b;
        ofs.close();
    }
    catch (const char *err) {
        fprintf(stderr, "%s\n", err);
        ofs.close();
        return false;
    }


    return true;
}


void Image::filterRed()
{
    for (int i = 0; i < w * h; ++i) {
        this->pixels[i].g = 0;
        this->pixels[i].b = 0;
        }
}
void Image::filterGreen()
{
    for (int i = 0; i < w * h; ++i) {
        this->pixels[i].r = 0;
        this->pixels[i].b = 0;
    }
}
void Image::filterBlue()
{
    for (int i = 0; i < w * h; ++i) {
        this->pixels[i].r = 0;
        this->pixels[i].g = 0;
    }
}
void Image::greyScale()
{
    int avg;
    for (int i = 0; i < w * h; ++i) {
        avg = (this->pixels[i].r + this->pixels[i].g + this->pixels[i].b)/3;
        this->pixels[i].r = avg;
        this->pixels[i].g = avg;
        this->pixels[i].b = avg;
    }
}
void Image::flipHorizontal()
{
    int tempPixels[3];
    unsigned int pixel1;
    unsigned int pixel2;
    for (int y = 0; y < h; ++y) {
        for(int x = 0; x < w/2; ++x)
        {
            pixel1 = x + y * w;
            pixel2 = (w - 1 - x) + y * w;
            tempPixels[0] = this->pixels[pixel1].r;
            tempPixels[1] = this->pixels[pixel1].g;
            tempPixels[2] = this->pixels[pixel1].b;
            this->pixels[pixel1].r = this->pixels[pixel2].r;
            this->pixels[pixel1].g = this->pixels[pixel2].g;
            this->pixels[pixel1].b = this->pixels[pixel2].b;
            this->pixels[pixel2].r = tempPixels[0];
            this->pixels[pixel2].g = tempPixels[1];
            this->pixels[pixel2].b = tempPixels[2];

        }

    }

}
void Image::flipVertically()
{


}
void Image::AdditionalFunction2()
{

}
void Image::AdditionalFunction3()
{

}
void Image::AdditionalFunction1()
{

}

/* Functions used by the GUI - DO NOT MODIFY */
int Image::getWidth()
{
    return w;
}

int Image::getHeight()
{
    return h;
}

Rgb* Image::getImage()
{
    return pixels;
}