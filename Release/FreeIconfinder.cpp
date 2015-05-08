#include <stdio.h>
#include <stdint.h>
#include <malloc.h>
#include <string.h>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../stb/stb_image_write.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../stb/stb_image.h"

void AlphaInverse(uint32_t *src,uint32_t **out,int length)
{
	uint32_t *data_out = *out;
	for(int i=0;i<length;i++)
	{
		uint8_t *color_src = (uint8_t*)&src[i];
		uint8_t *color_out = (uint8_t*)&data_out[i];

		if(color_src[3] && color_src[3]!=0xFF)
        {
            int alpha = 0xFF*(color_out[3] - color_src[3])/(0xFF-color_src[3]);

            if(color_out[3]&&alpha)
            {
                color_out[0] = 0xFF*(color_out[0] * color_out[3] - color_src[0] * color_src[3])/(0xFF-color_src[3])/alpha;
                color_out[1] = 0xFF*(color_out[1] * color_out[3] - color_src[1] * color_src[3])/(0xFF-color_src[3])/alpha;
                color_out[2] = 0xFF*(color_out[2] * color_out[3] - color_src[2] * color_src[3])/(0xFF-color_src[3])/alpha;
                color_out[3] = alpha * 0xFD / 0xFF;;
            }
            else
            {
                data_out[i] = 0;
            }
        }
        else
        {
            // nothing
        }
	}
}

int main()
{
    int w,h;
    unsigned char *data;
    int n;
    data = stbi_load("test.png", &w, &h, &n, 4);

    int w1,h1;
    unsigned char *data1;
    int n1;
    data1 = stbi_load("../Merger/512.png", &w1, &h1, &n1, 4);

    AlphaInverse((uint32_t*)data1,(uint32_t**)&data,512*512);

    stbi_write_png("test_out.png", 512, 512, 4, data, 0);
}
