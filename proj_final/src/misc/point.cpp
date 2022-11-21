#include <stdint.h>

namespace misc
{
    template <class T>
    class Point{
        T x;
        T y;

        void add(Point p){
            this.x += p.x;
            this.y += p.y;
        }
    };
}