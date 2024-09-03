// * * Author: Aditya
// ? the following code detects edges in a image and results the color of edges.
#include <stdio.h>

#include "CImg.h"
using namespace std;
using namespace cimg_library;

int main() {
    // * filter in x and y axis
    double filter[18] = {-1, -1, -1, 0,  0, 0, 1,  1, 1,
                         -1, 0,  1,  -1, 0, 1, -1, 0, 1};

    // * opening the image and assigning canvas
    CImg<unsigned int> *imageIn = new CImg<unsigned int>("image.jpg");
    CImg<unsigned char> image_canvas = *imageIn;
    CImg<unsigned char> image_padded(image_canvas.width() + 2,
                                     image_canvas.height() + 2, 1, 3);
    CImg<unsigned char> image_updated(image_canvas.width(),
                                      image_canvas.height(), 1, 3);
    image_padded.fill(0);
    image_updated.fill(0);

    // * applying padding
    for (int i = 0; i < image_canvas.width(); i++) {
        for (int j = 0; j < image_canvas.height(); j++) {
            image_padded(i + 1, j + 1, 0, 0) = image_canvas(i, j, 0, 0);
            image_padded(i + 1, j + 1, 0, 1) = image_canvas(i, j, 0, 1);
            image_padded(i + 1, j + 1, 0, 2) = image_canvas(i, j, 0, 2);
        }
    }

    // * main loop: for 2 separate filters, width traversal, height traversal,
    // rgb channels
    for (int q = 0; q < 2; q++) {
        for (int i = 1; i < image_canvas.width() + 1; i++) {
            for (int j = 1; j < image_canvas.height() + 1; j++) {
                for (int ch = 0; ch < 3; ch++) {
                    image_updated(i - 1, j - 1, 0, ch) +=
                        255 -
                        abs(static_cast<int>(
                                image_padded(i - 1, j - 1, 0, ch)) *
                                filter[0 + 9 * q] +
                            static_cast<int>(image_padded(i, j - 1, 0, ch)) *
                                filter[1 + 9 * q] +
                            static_cast<int>(
                                image_padded(i + 1, j - 1, 0, ch)) *
                                filter[2 + 9 * q] +
                            static_cast<int>(image_padded(i - 1, j, 0, ch)) *
                                filter[3 + 9 * q] +
                            static_cast<int>(image_padded(i, j, 0, ch)) *
                                filter[4 + 9 * q] +
                            static_cast<int>(image_padded(i + 1, j, 0, ch)) *
                                filter[5 + 9 * q] +
                            static_cast<int>(
                                image_padded(i - 1, j + 1, 0, ch)) *
                                filter[6 + 9 * q] +
                            static_cast<int>(image_padded(i, j + 1, 0, ch)) *
                                filter[7 + 9 * q] +
                            static_cast<int>(
                                image_padded(i + 1, j + 1, 0, ch)) *
                                filter[8 + 9 * q]) /
                            6;
                }
            }
        }
    }

    // * display the original and edge detection output.
    CImgDisplay draw_canvas(image_canvas, "image_changed");
    CImgDisplay draw_updated(image_updated, "image_updated");
    while (!draw_canvas.is_closed() && !draw_updated.is_closed()) {
        draw_canvas.wait();
        draw_updated.wait();
    }
}