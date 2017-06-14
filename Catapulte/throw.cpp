#include "throw.h"

float randomFloat(float a, float b) {
    float random = ((float) rand()) / (float) RAND_MAX;
    float diff = b - a;
    float r = random * diff;
    return a + r;
}

Throw::Throw(int level) : level(level)
{
    targetPoxX = randomFloat(-20, 20); // -20 to 20
    targetPoxZ = randomFloat(2,10);
    switch (level) {
    case 1:
        targetPoxY = randomFloat(level1Min, level2Min);
        break;
    case 2:
        targetPoxY = randomFloat(level2Min, level3Min);
        break;
    case 3:
        targetPoxY = randomFloat(level3Min, level3Max);
        break;
    default:
        break;
    }
}


