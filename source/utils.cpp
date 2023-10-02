#include "net.h"
#include "simpleocv.h"
#include <iostream>
#include <time.h>
// #include <random>
#include "utils.h"


void pretty_print(const ncnn::Mat& m)
{
    for (int q = 0; q < m.c; q++)
    {
        const float* ptr = m.channel(q);
        for (int z = 0; z < m.d; z++)
        {
            for (int y = 0; y < m.h; y++)
            {
                for (int x = 0; x < m.w; x++)
                {
                    printf("%f ", ptr[x]);
                }
                ptr += m.w;
                printf("\n");
            }
            printf("\n");
        }
        printf("---------------------------------\n");

    }
    printf("Matric shape [C, H, W]: [%d, %d, %d]\n", m.c, m.h, m.w);
}

Randn::Randn()
{
    std::normal_distribution<float> distribution(0.0, 1.0);
    srand(time(0));
}

ncnn::Mat Randn::randn_ncnn(int h, int w, int c)
{
    // std::default_random_engine generator;
    // std::normal_distribution<float> distribution(0.0, 1.0);


    cv::Mat images(h, w, c);
    ncnn::Mat mat(images.cols, images.rows, images.c, (void*)images.data);

    int channels = mat.c;
    int size = mat.c * mat.h * mat.w;

    
    for (int i = 0; i < channels; i++)
    {
        float *ptr_c = mat.channel(i);

        for (int j = 0; j < size; j++)
        {
            // float norm = (float) distribution(generator);
            ptr_c[j] += distribution(generator);
            // std::cout << norm << std::endl;
        }
    }

    return mat;
}