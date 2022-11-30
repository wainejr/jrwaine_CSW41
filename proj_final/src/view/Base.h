#include "globals.h"
#include "grlib/grlib.h"

#ifndef _VIEW_BASE_H_
#define _VIEW_BASE_H_

namespace view {

typedef tContext DrawContext; 
 
class Base {
public:
    virtual void draw(DrawContext* context) = 0;
};
}
#endif