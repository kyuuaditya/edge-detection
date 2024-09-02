#include <bits/stdc++.h>
#include <stdio.h>

#include "CImg.h"
using namespace std;
using namespace cimg_library;

int main() {
    // ! Filter
    double filter[18] = {-1, -1, -1, 0,  0, 0, 1,  1, 1,
                         -1, 0,  1,  -1, 0, 1, -1, 0, 1};

    // * opening the image
    CImg<unsigned int> *imageIn = new CImg<unsigned int>("image.jpg");

    // *sending it to a canvas
    CImg<unsigned char> image_canvas = *imageIn;
    CImgDisplay draw_canvas(image_canvas, "image_changed");

    CImg<unsigned char> image_padded(image_canvas.width() + 2,
                                     image_canvas.height() + 2, 1, 3);
    // CImgDisplay draw_padded(image_padded, "image_padded");
    image_padded.fill(0);

    // * updated image
    CImg<unsigned char> image_updated(image_canvas.width(),
                                      image_canvas.height(), 1, 3);
    CImgDisplay draw_updated(image_updated, "image_updated");
    image_updated.fill(0);

    for (int i = 0; i < image_canvas.width(); i++) {
        for (int j = 0; j < image_canvas.height(); j++) {
            image_padded(i + 1, j + 1, 0, 0) = image_canvas(i, j, 0, 0);
            image_padded(i + 1, j + 1, 0, 1) = image_canvas(i, j, 0, 1);
            image_padded(i + 1, j + 1, 0, 2) = image_canvas(i, j, 0, 2);
        }
    }

    for (int q = 0; q < 2; q++) {
        for (int i = 1; i < image_canvas.width() + 1; i++) {
            for (int j = 1; j < image_canvas.height() + 1; j++) {
                image_updated(i - 1, j - 1, 0, 0) +=
                    255 -
                    abs(static_cast<int>(image_padded(i - 1, j - 1, 0, 0)) *
                            filter[0 + 9 * q] +
                        static_cast<int>(image_padded(i, j - 1, 0, 0)) *
                            filter[1 + 9 * q] +
                        static_cast<int>(image_padded(i + 1, j - 1, 0, 0)) *
                            filter[2 + 9 * q] +
                        static_cast<int>(image_padded(i - 1, j, 0, 0)) *
                            filter[3 + 9 * q] +
                        static_cast<int>(image_padded(i, j, 0, 0)) *
                            filter[4 + 9 * q] +
                        static_cast<int>(image_padded(i + 1, j, 0, 0)) *
                            filter[5 + 9 * q] +
                        static_cast<int>(image_padded(i - 1, j + 1, 0, 0)) *
                            filter[6 + 9 * q] +
                        static_cast<int>(image_padded(i, j + 1, 0, 0)) *
                            filter[7 + 9 * q] +
                        static_cast<int>(image_padded(i + 1, j + 1, 0, 0)) *
                            filter[8 + 9 * q]) /
                        6;
                image_updated(i - 1, j - 1, 0, 1) +=
                    255 -
                    abs(static_cast<int>(image_padded(i - 1, j - 1, 0, 1)) *
                            filter[0 + 9 * q] +
                        static_cast<int>(image_padded(i, j - 1, 0, 1)) *
                            filter[1 + 9 * q] +
                        static_cast<int>(image_padded(i + 1, j - 1, 0, 1)) *
                            filter[2 + 9 * q] +
                        static_cast<int>(image_padded(i - 1, j, 0, 1)) *
                            filter[3 + 9 * q] +
                        static_cast<int>(image_padded(i, j, 0, 1)) *
                            filter[4 + 9 * q] +
                        static_cast<int>(image_padded(i + 1, j, 0, 1)) *
                            filter[5 + 9 * q] +
                        static_cast<int>(image_padded(i - 1, j + 1, 0, 1)) *
                            filter[6 + 9 * q] +
                        static_cast<int>(image_padded(i, j + 1, 0, 1)) *
                            filter[7 + 9 * q] +
                        static_cast<int>(image_padded(i + 1, j + 1, 0, 1)) *
                            filter[8 + 9 * q]) /
                        6;
                image_updated(i - 1, j - 1, 0, 2) +=
                    255 -
                    abs(static_cast<int>(image_padded(i - 1, j - 1, 0, 2)) *
                            filter[0 + 9 * q] +
                        static_cast<int>(image_padded(i, j - 1, 0, 2)) *
                            filter[1 + 9 * q] +
                        static_cast<int>(image_padded(i + 1, j - 1, 0, 2)) *
                            filter[2 + 9 * q] +
                        static_cast<int>(image_padded(i - 1, j, 0, 2)) *
                            filter[3 + 9 * q] +
                        static_cast<int>(image_padded(i, j, 0, 2)) *
                            filter[4 + 9 * q] +
                        static_cast<int>(image_padded(i + 1, j, 0, 2)) *
                            filter[5 + 9 * q] +
                        static_cast<int>(image_padded(i - 1, j + 1, 0, 2)) *
                            filter[6 + 9 * q] +
                        static_cast<int>(image_padded(i, j + 1, 0, 2)) *
                            filter[7 + 9 * q] +
                        static_cast<int>(image_padded(i + 1, j + 1, 0, 2)) *
                            filter[8 + 9 * q]) /
                        6;
            }
        }
    }

    while (!draw_canvas.is_closed() && !draw_updated.is_closed()) {
        image_canvas.display(draw_canvas);
        // image_padded.display(draw_padded);
        image_updated.display(draw_updated);
    }
}