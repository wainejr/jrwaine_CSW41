#include <iostream>
#include <iomanip>
#include "image.c"

extern "C" uint16_t EightBitHistogram(uint16_t width, uint16_t height, uint8_t const* p_image, uint16_t * p_histogram);

int main()
{
    uint16_t histogram[256];
  
    uint16_t processed_pixels = EightBitHistogram(width0, height0, p_start_image0, histogram);

    std::cout << "processed_pixels " << processed_pixels << std::endl << std::endl;
    
    if(processed_pixels)
    {
        std::cout << "val count" << std::endl;
        for(uint16_t i = 0; i < 256; i++)
        {
            std::cout << std::right << std::setw(3) << i << " " 
                << std::setw(5) << histogram[i] << std::endl;
        }
    } else {
        std::cout << "Unable to process image" << std::endl;
    }
    std::cout << std::flush;
    
  return 0;
}