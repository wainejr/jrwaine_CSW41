/*__________________________________________________________________________________
|       Disciplina de Sistemas Embarcados - 2022-2
|       Prof. Douglas Renaux
| __________________________________________________________________________________
|
|		Lab 3
| __________________________________________________________________________________
*/

/*
 * @file     main.cpp
 * @author   Joao F. S. Machado & Waine B. O. Junior
 * @brief    Solution to Lab3 of ELF74/CSW41 - UTFPR. \n 
 *           Function in ARM Assembly that calculates the histogram of an image up to 64k. \n
             Call assembly function in c++. \n
             Display the histogram result in c++. \n
 * @version  V1
 * @date     Sep, 2022
 *****************************************************************************
*/

/*------------------------------------------------------------------------------
 *
 *      File includes
 *
 *------------------------------------------------------------------------------*/

#include <iostream>
#include <iomanip>
#include "image.c"

/*------------------------------------------------------------------------------
 *
 *      Functions and Methods
 *
 *------------------------------------------------------------------------------*/

/**
 * EightBitHistogram function.
 *
 * @brief     calculates the histogram of an image up to 64k
 * @param[in] width       - image width
 * @param[in] height      - image height
 * @param[in] p_image     - pointer to first image address
 * @param[in] p_histogram - pointer to first histogram address
 * @returns   uint16_t    - number of pixels processed
 */

extern "C" uint16_t EightBitHistogram(uint16_t width, uint16_t height, uint8_t const* p_image, uint16_t * p_histogram);

void showHistogram(uint16_t processed_pixels, uint16_t * p_histogram, uint8_t showZeros);

/**
 * Main function.
 *
 * @returns int - not used, declared for compatibility
 */

int main()
{
    uint16_t* histogram = new uint16_t[256];

    uint16_t processed_pixels;
    
    processed_pixels = EightBitHistogram(width0, height0, p_start_image0, histogram);
    
    std::cout << std::endl << "Test Case 0: " << std::endl << std::endl;
    
    showHistogram(processed_pixels, histogram, 0);
    
    processed_pixels = EightBitHistogram(width1, height1, p_start_image1, histogram);
    
    std::cout << std::endl << "Test Case 1: " << std::endl << std::endl;
    
    showHistogram(processed_pixels, histogram, 1);
    
    return 0;
}

/**
 * showHistogram function.
 *
 * @brief     displays a histogram
 * @param[in] processed_pixels - number of pixels processed
 * @param[in] histogram        - pointer to first histogram address
 * @param[in] showZeros        - flag that shows values with zero count when set
 * @returns void - no return
 */

void showHistogram(uint16_t processed_pixels, uint16_t * histogram, uint8_t showZeros)
{
    std::cout << "Processed pixels: " << processed_pixels << std::endl << std::endl;
    
    if(processed_pixels)
    {
        std::cout << "Val Count" << std::endl;
        for(uint16_t i = 0; i < 256; i++)
        {
            if(histogram[i] || showZeros)
            {
                std::cout << std::right << std::setw(3) << i << " " 
                  << std::setw(5) << histogram[i] << std::endl;
            }
        }
    } else {
        std::cout << "Unable to process image!" << std::endl;
    }
    std::cout << std::flush;
}