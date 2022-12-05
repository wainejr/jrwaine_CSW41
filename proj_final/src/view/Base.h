#include "globals.h"
#include "grlib/grlib.h"

#ifndef _VIEW_BASE_H_
#define _VIEW_BASE_H_

namespace view {
// Typedef of context to draw to
typedef tContext DrawContext;

/**
*   @brief Base class for all views
*   
*/
class Base {
public:
/**
*   @brief Draw function for each view
*   
*   @param context context to draw
*/
    virtual void draw(DrawContext* context) = 0;
};
}
#endif