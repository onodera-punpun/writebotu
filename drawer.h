#ifndef DRAWER_H
#define DRAWER_H

#if DEBUG
#include <assert.h>
#endif
#include <avr/io.h>
#include <math.h>
#include <stdlib.h>

#include "millis.h"
#include "stepper.h"
#include "util.h"

/// Drawer is class for easier interaction with *multiple* stepper
/// motors.
class Drawer {
private:
	/// The steppers we want to use.
	Stepper lstepper, rstepper;

	/// The minimum intervals the steppers should use in μs. This
	/// value can be bigger depending on the required intervals
	/// `moveto()` calculates.
	unsigned interval;

	/// The distance between the two steppers in mm. Take note, this
	/// is not the center of the spool, but the position where the
	/// cord leaves the spool.
	float width;

	/// The vertical distance between the steppers and the point of
	/// origin (0,0) in mm. In our case the origin is the bottom
	/// left corner of our drawing area.
	float height;

	/// The horizonal distance between the stepper motors and the
	/// point of origin (0,0) in mm. Again, our origin is the bottom
	/// left corner of our drawing area. Also, again, don't measure
	/// from the center of the spool, but from the position where the
	/// cord leaves the spool.
	float offset;

	/// The scale of the produced writings.
	float scale;

	/// The current cord lengths. This value will be altered later on
	/// by the `moveto()` function to reflect changes.
	float cllen = sqrt((offset*offset)+(height*height));
	float crlen = sqrt((width-offset)*(width-offset)+(height*height));

	/// The current pen position. Also this value will be altered
	/// later on by the `moveto()` function to reflect chancges.
	float cx = 0;
	float cy = 0;
public:
	Drawer(Stepper &lstepper, Stepper &rstepper,
		unsigned interval=3000, float width=520, float height=510,
		float offset=155, unsigned scale=16);

	/// off sets all the stepper motor pins to low.
	void low();

	/// moveto moves the pen to the given coordinates.
	void moveto(float x, float y);

	/// turn turns the stepper motors `steps` amount of steps.
	/// `ldirection` and `rdirection` setting the respective
	/// directions, 0 being a countclockwise direction and 1 being a
	/// clockwise direction. `linterval` and `rinterval`
	/// set the delay between each step for the respective steppers.
	void turn(bool ldirection, bool rdirection, unsigned lsteps,
		unsigned rsteps, unsigned linterval=3000,
		unsigned rinterval=3000);

	// Various unit tests.
	#if DEBUG
	int moveto_test();
	#endif
};

#endif
