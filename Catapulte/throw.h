#ifndef THROW_H
#define THROW_H

#include <stdlib.h>

#define level1Min 40
#define level2Min 70
#define level3Min 100
#define level3Max 130

class Throw
{
public:
    Throw(int level);
    float getTargetPoxX(){return targetPoxX;}
    float getTargetPoxY(){return targetPoxY;}
    float getTargetPoxZ(){return targetPoxZ;}
private:
    float targetPoxX, targetPoxY, targetPoxZ;
    int level;
};

#endif // THROW_H
