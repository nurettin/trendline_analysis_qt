#ifndef MATEMATIK_HPP
#define MATEMATIK_HPP

#include <cmath>
#include <limits>
#include <QPoint>
#include <QRect>

namespace onur{ namespace bilim{

template <typename T>
        T normalizasyon(T b, T e, T rb, T re, T v)
{
    T d= std::abs(b- e);
    T rd= std::abs(rb- re);
    T rv= rb+ (v- b)* rd/ d;
    return rv;
}

}}

#endif // MATEMATIK_HPP
