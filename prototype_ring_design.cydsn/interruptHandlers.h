#include "project.h"

extern int indices[4];
extern int motorRotations[4];

//Quadrature decoder interrupt handlers
CY_ISR(QuadInt0);
CY_ISR(QuadInt1);
CY_ISR(QuadInt2);
CY_ISR(QuadInt3);

//Timer interrupt handlers