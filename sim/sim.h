/*
  Ardumower (www.ardumower.de)

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


#ifndef SIM_H

#include <vector>
#include <opencv2/core/core.hpp>
#include "world.h"
#include "simrobot.h"

using namespace std;
using namespace cv;

// states
enum {
  STATE_FORW,
  STATE_REV,
  STATE_ROLL,
};

class SimRobot;
class World;


class Sim
{
  public:
    Mat imgBfieldRobot;
    World world;
	SimRobot robot;
    float speed;
    int state;
    float stateTime;
    int plotIdx;
    Sim();
    void step();
    void draw();
    void plotXY(Mat &image, int x, int y, int r, int g, int b, bool clearplot);
};



#endif