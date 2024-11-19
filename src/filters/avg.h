#ifndef AVG_H
#define AVG_H
#define DEFAULT_AVG_FILTER_SIZE 5

struct AVGFilter
{
    AVGFilter(int size = DEFAULT_AVG_FILTER_SIZE);

    void push(double value);
    double output();

    bool m_bFilled;
    int m_iIndex;
    int m_Size;
    double *m_Readings;
    double *m_Weights;
};

#endif