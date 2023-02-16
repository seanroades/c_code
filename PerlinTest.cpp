#include <iostream>
#include <opencv2/opencv.hpp>
#include "PerlinNoise.hpp"

struct PerlinNoiseLayer {
    int octaveCount;    // Number of octaves
    double frequency;   // Frequency of the first octave
    double persistence; // Persistence of the noise
    double amplitude;   // Amplitude of the first octave
    double lacunarity;  // Lacunarity of the noise
    unsigned int seed;           // Seed value for the noise
};

double generatePerlinNoise(PerlinNoiseLayer layer, double x, double y) {
    double noise = 0.0;
    double frequency = layer.frequency;
    double amplitude = layer.amplitude;
    const siv::PerlinNoise perlin{ layer.seed };

    // Does not include layer.lacunarity; 
    noise = perlin.octave2D_01(x * frequency, y * frequency, layer.octaveCount, layer.persistence) * amplitude;

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
    // Declare variables
    // int octaveCount = 1;
    // double frequency = 1;
    // double persistence = 1;
    // double amplitude = 1;
    // double lacunarity = 1;
    // unsigned int seed = 1;

    // // Declare variables
    // int octaveCount2 = 10;
    // double frequency2 = 4;
    // double persistence2 = 0.5;
    // double amplitude2 = 2;
    // double lacunarity2 = 1;
    // unsigned int seed2 = 3;

    int octaveCount = 3;
    double frequency = 1;
    double persistence = 1;
    double amplitude = 1;
    double lacunarity = 1;
    unsigned int seed = 212;

    // Declare variables
    int octaveCount2 = 10;
    double frequency2 = 3.4;
    double persistence2 = 0.58;
    double amplitude2 = 1.7;
    double lacunarity2 = 1;
    unsigned int seed2 = 122;

    // // Ask for user input
    // std::cout << "Enter octave count: ";
    // std::cin >> octaveCount;
    // std::cout << "Enter frequency: ";
    // std::cin >> frequency;
    // std::cout << "Enter persistence: ";
    // std::cin >> persistence;
    // std::cout << "Enter amplitude: ";
    // std::cin >> amplitude;
    // std::cout << "Enter lacunarity: ";
    // std::cin >> lacunarity;
    // std::cout << "Enter seed: ";
    // std::cin >> seed;

    PerlinNoiseLayer layer = {
        octaveCount,          // octaveCount
        frequency,       // frequency
        persistence,        // persistence
        amplitude,        // amplitude
        lacunarity,        // lacunarity
        seed       // seed
    };

    //     // Ask for user input
    // std::cout << "Time for #2";
    // std::cout << "Enter octave count: ";
    // std::cin >> octaveCount2;
    // std::cout << "Enter frequency: ";
    // std::cin >> frequency2;
    // std::cout << "Enter persistence: ";
    // std::cin >> persistence2;
    // std::cout << "Enter amplitude: ";
    // std::cin >> amplitude2;
    // std::cout << "Enter lacunarity: ";
    // std::cin >> lacunarity2;
    // std::cout << "Enter seed: ";
    // std::cin >> seed2;

    PerlinNoiseLayer layer2 = {
        octaveCount2,          // octaveCount
        frequency2,       // frequency
        persistence2,        // persistence
        amplitude2,        // amplitude
        lacunarity2,        // lacunarity
        seed2       // seed
    };

    int width = 512;
    int height = 512;
    cv::Mat image(height, width, CV_8UC1);

    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            const double noise = combineNoiseLayers(layer, layer2, (double) x / width, (double) y / height);
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