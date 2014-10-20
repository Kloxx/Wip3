#include "common.h"


float
utils::linspace(const unsigned int kk, const unsigned int kk_max, const float min_value, const float max_value)
{
    const float xx = static_cast<float>(kk+1)/(kk_max+1);
    return min_value + (max_value-min_value)*xx;
}

float
utils::smooth_function(const float xx)
{
    if (xx<0) return 0;
    if (xx>1) return 1;
    return xx*xx*(3-2*xx);
}

float
utils::smooth_interp(const unsigned int kk, const unsigned int kk_max)
{
    const float xx = static_cast<float>(kk+1)/(kk_max);
    return smooth_function(xx);
}

float
utils::smooth_diff(const unsigned int kk, const unsigned int kk_max)
{
    const float xx_current = static_cast<float>(kk)/kk_max;
    const float xx_next = static_cast<float>(kk+1)/kk_max;
    return smooth_function(xx_next)-smooth_function(xx_current);
}


