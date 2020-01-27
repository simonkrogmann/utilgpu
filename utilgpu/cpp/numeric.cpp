#include "numeric.h"

#include <algorithm>

namespace util
{
std::vector<int> toDigits(unsigned int number)
{
    std::vector<int> digits;
    do
    {
        digits.push_back(number % 10);
        number /= 10;
    } while (number > 0);
    std::reverse(digits.begin(), digits.end());
    return digits;
}
}  // namespace util
