#include <stdio.h>
#include <stdint.h>
#include <malloc.h>
#include <string.h>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../stb/stb_image_write.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../stb/stb_image.h"

int main()
{

    int w,h;
    unsigned char *data;
    int n;
    data = stbi_load("1.png", &w, &h, &n, 4);

    int w1,h1;
    unsigned char *data1;
    int n1;
    data1 = stbi_load("2.png", &w1, &h1, &n1, 4);



    uint32_t *color = (uint32_t*)data;
    uint32_t *color1 = (uint32_t*)data1;
    for (int i = 100; i < 512-100; ++i)
    {
        for (int j = 100; j < 512-100; ++j)
        {
            color[i*512+j] = color1[i*512+j];
        }
    }


    stbi_write_png("512.png", 512, 512, 4, data, 0);
}
