#ifndef _VECTOR_2D_H_
#define _VECTOR_2D_H_

#include <cmath>

/**
 * Standard class function for Vector 2d
 */
class vector2d
{
private:
    static const unsigned int inf = 999999;
    double x, y;

public:
    vector2d()
    { x = y = 0; }

    /**
     * an array of int number for input
     * it will only look at the first two number
     * sample input: vector2d({1.0, 0.2}) 
     * */
    vector2d(double* x_y_input)
    { x = x_y_input[0]; y = x_y_input[1]; }

    double set_x(double x_input)
    { x = x_input; }

    double set_y(double y_input)
    { y = y_input; }

    double get_x() const
    { return x; }

    double get_y() const
    { return y; }

    double magnitude() const
    { return std::sqrt(x * x + y * y); }

    double gradient() const
    {
        if (x == 0)
            return inf;
        else
            return (y / x);
    }

    ~vector2d(){}
};

#endif