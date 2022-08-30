#include <iostream>
#include <iomanip>
#include "image.c"

extern "C" uint16_t EightBitHistogram(uint16_t width, uint16_t height, uint8_t const* p_image, uint16_t * p_histogram);

int main()
{
    uint16_t histogram[256];
  
    uint16_t processed_pixels = EightBitHistogram(width1, height1, p_start_image1, histogram);

    std::cout << "processed_pixels " << processed_pixels << std::endl << std::endl;
    
    if(processed_pixels)
    {
        std::cout << "val count" << std::endl;
        for(uint16_t i = 0; i < 256; i++)
        {
            if(histogram[i])
            {
                std::cout << std::right << std::setw(3) << i << " " << std::setw(5) << histogram[i] << std::endl;
            }
        }
    }
    
  return 0;
}