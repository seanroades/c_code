#include <iostream>
#include <opencv2/opencv.hpp>
#include "PerlinNoise.hpp"

int main()
{
    std::cout << "Enter a seed value: ";
    unsigned int seed;
    std::cin >> seed;

    const siv::PerlinNoise perlin{ seed };

    const int width = 512*2*2;
    const int height = 512*2*2;
    cv::Mat image(height, width, CV_8UC1);

    const double scale = 0.012;
    const double amplitude = 3.0;

    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            const double noise = perlin.octave2D_01((x * scale), (y * scale), 4) * amplitude;
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
