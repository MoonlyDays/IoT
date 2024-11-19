#include <filters/sap.h>
#include "sap.h"

SATFilter::SATFilter(int size)
{
    m_iIndex = 0;
    m_bFilled = false;
    m_Size = size;
    m_Readings = new double[size];
}

void SATFilter::push(double value)
{
    m_Readings[m_iIndex++] = value;

    if (m_iIndex >= m_Size)
    {
        m_iIndex = 0;
        m_bFilled = true;
    }
}

double SATFilter::output(void)
{
    int sorted[m_Size];
    for (int i = 0; i < m_Size; i++)
    {
        sorted[i] = m_Readings[i];
    }

    // Сортируем массив (например, методом пузырька)
    for (int i = 0; i < m_Size - 1; i++)
    {
        for (int j = 0; j < m_Size - i - 1; j++)
        {
            if (sorted[j] > sorted[j + 1])
            {
                // Обмен элементов
                int temp = sorted[j];
                sorted[j] = sorted[j + 1];
                sorted[j + 1] = temp;
            }
        }
    }

    // Возвращаем медианное значение
    return sorted[m_Size / 2];
}
