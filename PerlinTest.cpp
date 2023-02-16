#include <iostream>
#include <opencv2/opencv.hpp>
#include "PerlinNoise.hpp"

struct PerlinNoiseLayer {
    int octaveCount;    // Number of octaves
    double frequency;   // Frequency of the first octave
    double persistence; // Persistence of the noise
    double amplitude;   // Amplitude of the first octave
    double lacunarity;  // Lacunarity of the noise
    int seed;           // Seed value for the noise
};

double generatePerlinNoise(PerlinNoiseLayer layer, double x, double y) {
    double noise = 0.0;
    double frequency = layer.frequency;
    double amplitude = layer.amplitude;

    for (int i = 0; i < layer.octaveCount; i++) {
        noise += PerlinNoise::noise(x * frequency, y * frequency, layer.seed) * amplitude;
        frequency *= layer.lacunarity;
        amplitude *= layer.persistence;
    }

    return noise;
}

double combineNoiseLayers(PerlinNoiseLayer layer1, PerlinNoiseLayer layer2, double x, double y) {
    double noise1 = generatePerlinNoise(layer1, x, y);
    double noise2 = generatePerlinNoise(layer2, x, y);
    double combinedNoise = noise1 + noise2;
    return combinedNoise;
}

int main() 
{
    std::cout << "Enter a seed value: ";
    unsigned int seed;
    std::cin >> seed;

    PerlinNoiseLayer layer = {
        4,          // octaveCount
        0.01,       // frequency
        0.5,        // persistence
        1.0,        // amplitude
        2.0,        // lacunarity
        seed       // seed
    };

    int width, height = 512;
    cv::Mat image(height, width, CV_8UC1);

    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            const double noise = generatePerlinNoise(layer, x, y);
            const uint8_t pixel_value = static_cast<uint8_t>(noise * 255.0);

            image.at<uint8_t>(y, x) = pixel_value;
        }
    }

    cv::imwrite("perlin.png", image);
    // Show user the image
    cv::imshow("Perlin Noise", image);
    // Press the 0 key to close the window
    cv::waitKey(0);

    return 0;
}