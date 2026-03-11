#include "LinearCharacteristics.h"

using namespace std;

LinearCharacteristics::LinearCharacteristics(float gain, float offset)
{
    m_gain = gain;
    m_offset = offset;
    m_ulim = 999999.0f;  // a large number
    m_llim = -999999.0f; // a large neg. number
}

LinearCharacteristics::LinearCharacteristics(float x_min, float x_max, float y_min, float y_max)
{
    // Calculate gain and offset based on the provided limits
    m_gain = (y_max - y_min) / (x_max - x_min); // height / width = Gain (steigung) 
    m_offset = x_min-y_min/m_gain; // x_min - y_min / gain = offset (x-Achsenabschnitt)
    m_ulim = y_max;
    m_llim = y_min;
}


LinearCharacteristics::~LinearCharacteristics() {}

float LinearCharacteristics::evaluate(float x)
{
    // calculate result as y(x) = gain * (x - offset)
    float ret_val = m_gain * (x - m_offset);
    
    // apply limits (saturation)
    if (ret_val > m_ulim) {
        ret_val = m_ulim;
    } else if (ret_val < m_llim) {
        ret_val = m_llim;
    }

    return ret_val;
}

void LinearCharacteristics::set_limits(float ll, float ul)
{
    m_llim = ll;
    m_ulim = ul;
}
