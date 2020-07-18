#include<algorithm>

class Solution {
public:
    double angleClock(int hour, int minutes) {
        const int hc = 12, mc = 60;
        hour %= 12;
        // get hour and minute hand percentage
        const double hp = (double)hour / hc, mp = (double)minutes / mc;
        // get hour and minute angle
        double ha = hp * 360 + mp * 30;
        double ma = mp * 360;
        // get one angle between two hand
        double angle = std::abs(ha - ma);
        // return smaller angle
        return std::min(angle, 360 - angle);
    }
};
