#ifndef PARAMETERS_H
#define PARAMETERS_H

// motor control
const float openingTolerance = 0.1;

// P-controller
const float toleratedPsiDelta = 0.1;
const float minOpening = 0.05;
const float maxOpeningAtPsiDelta = 1.5;



// derived parameters
const float targetTolerance = openingTolerance / 2;
const float m = (1. - minOpening) / maxOpeningAtPsiDelta;
const float b = minOpening;

#endif
