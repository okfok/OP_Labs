#include "core.h"

double _log(double arg){
    if (arg == 0)
        throw LogArgumentZero();

    if (arg < 0)
        throw LogWrongArgument(arg);

    return log(arg);
}


double Function::get_y() {
    return _log(_x) / _log(_x - 2);
}
