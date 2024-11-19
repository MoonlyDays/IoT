#include "avg.h"

AVGFilter::AVGFilter(int size)
{
    m_iIndex = 0;
    m_bFilled = false;
    m_Size = size;
    m_Weights = new double[m_Size]{0.1, 0.2, 0.3, 0.2, 0.2};
}

void AVGFilter::push(double value)
{
    m_Readings[m_iIndex++] = value;

    if (m_iIndex >= m_Size)
    {
        m_iIndex = 0;
        m_bFilled = true;
    }
}

double AVGFilter::output()
{
    float weightedSum = 0;
    float weightTotal = 0;

    for (int i = 0; i < m_Size; i++)
    {
        weightedSum += m_Readings[i] * m_Weights[i];
        weightTotal += m_Weights[i];
    }

    // Возвращаем результат
    return weightedSum / weightTotal;
}
