#include <iostream>
#include <algorithm>
#include <vector>
#include <random>
#include <iostream>
#include <opencv2/opencv.hpp>

class PerlinNoise {
private:
    std::vector<double> weights;
    std::vector<double> amplitudes;
    std::vector<double> scales;

public:
    PerlinNoise() {}

    void addLayer(double weight, double amplitude, double scale) {
        weights.push_back(weight);
        amplitudes.push_back(amplitude);
        scales.push_back(scale);
    }

    double fade(double t) {
        return t * t * t * (t * (t * 6 - 15) + 10);
    }

    double lerp(double t, double a, double b) {
        return a + t * (b - a);
    }

    double grad(int hash, double x, double y) {
        int h = hash & 15;
        double u = h < 8 ? x : y;
        double v = h < 4 ? y : (h == 12 || h == 14 ? x : 0);
        return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
    }

    double noise(double x, double y) {
        double result = 0.0;
        for (int i = 0; i < amplitudes.size(); i++) {
            double weight = weights[i];
            double amplitude = amplitudes[i];
            double scale = scales[i];

            double nx = x / scale;
            double ny = y / scale;

            int xi = (int)floor(nx) & 255;
            int yi = (int)floor(ny) & 255;
            int aaa = p[p[p[xi] + yi]];
            int aba = p[p[p[xi] + yi + 1]];
            int baa = p[p[p[xi + 1] + yi]];
            int bba = p[p[p[xi + 1] + yi + 1]];

            double xf = nx - floor(nx);
            double yf = ny - floor(ny);

            double u = fade(xf);
            double v = fade(yf);

            double x1 = lerp(grad(aaa, xf, yf), grad(baa, xf - 1, yf), u);
            double x2 = lerp(grad(aba, xf, yf - 1), grad(bba, xf - 1, yf - 1), u);

            result += weight * amplitude * lerp(x1, x2, v);
        }
        return result;
    }
};


int main() {
    int width = 512;
    int height = 512;

    // Create the Perlin noise object and add layers with different weights, amplitudes, and scales
    PerlinNoise noise;
    noise.addLayer(1.0, 1.0, 20.0);
    noise.addLayer(0.5, 2.0, 10.0);
    noise.addLayer(0.25, 4.0, 5.0);

    // Create an OpenCV Mat object to store the image
    cv::Mat image(height, width, CV_8UC1);

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            double n = noise.noise((double)x, (double)y);
            int c = (int)(n * 255);
            image.at<uchar>(y, x) = (uchar)c;
        }
    }

    // Save the image to a file
    cv::imwrite("output.png", image);

    return 0;
}



// class PerlinNoise {
// private:
//     std::vector<int> p;

// public:
//     PerlinNoise() {
//         p.resize(256);

//         for (int i = 0; i < 256; i++) {
//             p[i] = i;
//         }

//         std::random_device rd;
//         std::mt19937 g(rd());

//         std::shuffle(p.begin(), p.end(), g);
//         p.insert(p.end(), p.begin(), p.end());
//     }

//     double fade(double t) {
//         return t * t * t * (t * (t * 6 - 15) + 10);
//     }

//     double lerp(double t, double a, double b) {
//         return a + t * (b - a);
//     }

//     double grad(int hash, double x, double y) {
//         int h = hash & 15;
//         double u = h < 8 ? x : y;
//         double v = h < 4 ? y : (h == 12 || h == 14 ? x : 0);
//         return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
//     }

//     double noise(double x, double y) {
//         int xi = (int)floor(x) & 255;
//         int yi = (int)floor(y) & 255;
//         int aaa = p[p[p[xi] + yi]];
//         int aba = p[p[p[xi] + yi + 1]];
//         int baa = p[p[p[xi + 1] + yi]];
//         int bba = p[p[p[xi + 1] + yi + 1]];

//         double xf = x - floor(x);
//         double yf = y - floor(y);

//         double u = fade(xf);
//         double v = fade(yf);

//         double x1 = lerp(grad(aaa, xf, yf), grad(baa, xf - 1, yf), u);
//         double x2 = lerp(grad(aba, xf, yf - 1), grad(bba, xf - 1, yf - 1), u);

//         return lerp(x1, x2, v);
//     }
// };

// int main() {
//     int width = 512;
//     int height = 512;

//     PerlinNoise noise;

//     // Create an OpenCV Mat object to store the image
//     cv::Mat image(height, width, CV_8UC1);

//     for (int y = 0; y < height; y++) {
//         for (int x = 0; x < width; x++) {
//             double n = noise.noise((double)x / width * 10, (double)y / height * 10);
//             int c = (int)(n * 255);
//             image.at<uchar>(y, x) = (uchar)c;
//         }
//     }

//     // Save the image to a file
//     cv::imwrite("output.png", image);

//     return 0;
// }