#ifndef SAP_H
#define SAP_H

#define DEFAULT_SAT_FILTER_SIZE 5

struct SATFilter
{
    SATFilter(int size = DEFAULT_SAT_FILTER_SIZE);

    void push(double value);
    double output( void );

    bool m_bFilled;
    int m_iIndex;
    int m_Size;
    double* m_Readings;
};

#endif