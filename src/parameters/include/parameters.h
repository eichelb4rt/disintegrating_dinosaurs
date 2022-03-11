#ifndef PARAMETERS_H_
#define PARAMETERS_H_

// parameters for the simulated annealing algorithm

// determines how far points move when they are shaken
extern double SHAKE;
// how far points can move without the need to be closer to the mathematical form
extern double ALLOWED_DIST;
// how many decimal digits should stay the same when the points are shaken
extern int ACCEPTED_DECIMAL_DIGITS;
// minimum temp for simulated annealing
extern double MIN_TEMPERATURE;
// maximum temp for simulated annealing
extern double MAX_TEMPERATURE;

#endif // PARAMETERS_H_