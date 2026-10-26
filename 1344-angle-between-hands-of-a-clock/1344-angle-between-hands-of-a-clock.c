
double angleClock(int hour, int minutes) {
    double minuteAngle = minutes * 6.0;
    double hourAngle = (hour % 12) * 30.0 + minutes * 0.5;

    double angle = hourAngle - minuteAngle;

    if (angle < 0) {
        angle = -angle;
    }

    if (angle > 180.0) {
        angle = 360.0 - angle;
    }

    return angle;
}
