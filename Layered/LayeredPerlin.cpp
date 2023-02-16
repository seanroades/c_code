#include <iostream>
#include <cmath>
#include <vector>
#include <random>
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;

class PerlinNoise {
private:
    vector<int> p;

public:
    PerlinNoise() {
        p.resize(256);

        for (int i = 0; i < 256; i++) {
            p[i] = i;
        }

        std::random_device rd;
        std::mt19937 g(rd());

        std::shuffle(p.begin(), p.end(), g);
        p.insert(p.end(), p.begin(), p.end());
    }

    double fade(double t) {
        return t * t * t * (t * (t * 6 - 15) + 10);
    }

    double lerp(double t, double a, double b) {
        return a + t * (b - a);
    }

    double grad(int hash, double x, double y, double z) {
        int h = hash & 15;
        double u = h < 8 ? x : y;
        double v = h < 4 ? y : h == 12 || h == 14 ? x : z;
        return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
    }

    double noise(double x, double y, double z) {
        int X = (int)floor(x) & 255;
        int Y = (int)floor(y) & 255;
        int Z = (int)floor(z) & 255;
        x -= floor(x);
        y -= floor(y);
        z -= floor(z);
        double u = fade(x);
        double v = fade(y);
        double w = fade(z);
        int A = p[X] + Y;
        int AA = p[A] + Z;
        int AB = p[A + 1] + Z;
        int B = p[X + 1] + Y;
        int BA = p[B] + Z;
        int BB = p[B + 1] + Z;

        return lerp(w, lerp(v, lerp(u, grad(p[AA], x, y, z),
                                     grad(p[BA], x - 1, y, z)),
                             lerp(u, grad(p[AB], x, y - 1, z),
                                  grad(p[BB], x - 1, y - 1, z))),
                    lerp(v, lerp(u, grad(p[AA + 1], x, y, z - 1),
                                     grad(p[BA + 1], x - 1, y, z - 1)),
                         lerp(u, grad(p[AB + 1], x, y - 1, z - 1),
                              grad(p[BB + 1], x - 1, y - 1, z - 1))));
    }
};

double octavePerlin(double x, double y, double z, int octaves, double persistence, PerlinNoise& noise) {
    double total = 0;
    double frequency = 1;
    double amplitude = 1;
    double maxValue = 0;

    for (int i = 0; i < octaves; i++) {
        total += noise.noise(x * frequency, y * frequency, z * frequency) * amplitude;

        maxValue += amplitude;

        amplitude *= persistence;
        frequency *= 2;
    }

    return total / maxValue;
}

using namespace cv;
using namespace std;

// The rest of the code goes here...

int main() {
    int width = 512;
    int height = 512;

    PerlinNoise noise;

    double* noiseMap = new double[width * height];

    // Generate noise map and normalize values to 0-1 range
    // The rest of the code goes here...

    // Create an OpenCV Mat object to store the image
    Mat image(height, width, CV_8UC1);

    // Convert the noise map to a grayscale image and save it
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int value = (int)(255 * noiseMap[y * width + x]);
            image.at<uchar>(y, x) = (uchar)value;
        }
    }

    imwrite("output.png", image);

    // Clean up
    delete[] noiseMap;

    return 0;
}
