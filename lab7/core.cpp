#include "core.h"


double Function::get_y() {
    if (_x - 2 <= 0)
        throw LogWrongArgument(_x - 2);


    return log(_x) / log(_x - 2);
}
