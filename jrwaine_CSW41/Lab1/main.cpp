#include <iostream>



int main()
{
  std::cout << "Date " << __DATE__ << std::endl;
  std::cout << "File " << __FILE__ << std::endl;
  std::cout << "Time " << __TIME__ << std::endl;
  std::cout << "Core " << __CORE__ << std::endl;
  std::cout << "ARM VFP " << __ARMVFP__ << std::endl;
  std::cout << "__ARM_SIZEOF_WCHAR_T " << __ARM_SIZEOF_WCHAR_T << std::endl;
  std::cout << std::flush;

  float val;
  float const_sum = 3.14;
  std::cout << "Enter float number: " << std::flush;
  std::cin >> val;
  std::cout << std::endl;
  
  float sum_val = val+const_sum;
  std::cout << "Sum " << val << "+" << const_sum << "=" << sum_val << std::flush;

  return 0;
}
