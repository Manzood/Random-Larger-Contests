#include <iostream>
#include <fstream>
#include <sstream>
#include <utility>
#include <exception>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

vector<string> vec_splitter(string s) {
    s += ','; vector<string> res;
    while(!s.empty()) {
        res.push_back(s.substr(0, s.find(',')));
        s = s.substr(s.find(',') + 1);
    }
    return res;
}

void debug_out( vector<string> __attribute__ ((unused)) args, __attribute__ ((unused)) int idx, __attribute__ ((unused)) int LINE_NUM) { cerr << endl; } 
template <typename Head, typename... Tail>

void debug_out(vector<string> args, int idx, int LINE_NUM, Head H, Tail... T) {
    if(idx > 0) cerr << ", "; else cerr << "Line(" << LINE_NUM << ") ";
    stringstream ss; ss << H;
    cerr << args[idx] << " = " << ss.str();
    debug_out(args, idx + 1, LINE_NUM, T...);
}

#ifdef local 
    #define debug(...) debug_out(vec_splitter(#__VA_ARGS__), 0, __LINE__, __VA_ARGS__)
#else 
    #define debug(...) 42
#endif


/*
For this contest, you have to modify the code of the Robot class

Specifically, you have to implement 3 methods:

  Robot::initialize
    which takes an instance of a grid class and
    initializes any internal data structures that your robot requires

  Robot::move
    which takes no parameters, and returns the next
    move of the robot. It should return exactly one of these values
    Grid.LEFT, Grid.RIGHT, Grid.UP, Grid.DOWN

  Robot::gotEgg
    which takes 3 parameters: x, y, value
    immediately after Robot::move, if your robot lands up in
    a cell containing a goose, and the goose has laid an egg
    then got_egg is called with the co-ordinates of the goose
    and the value of the egg


Overall flow of the code:

The system will call the methods of the robot class in this order:

  r = Robot()
  r.initialize(grid)
  then it will call r.move() many times (2*grid.rows*grid.cols times)

  if, after any move your robot lands up in a cell with
  a goose, then the system will immediately call
  r.gotEgg(value)

Feel free to add other classes and data-structures as you feel
necessary. However, do not modify any of the code in the `Grid`
or `Main` classes. And do not read/write any data to or
from any files.

*/

// You can modify anything here as necessary
// You can add more classes, functions, data structures
class Grid {
  /* DO NOT MODIFY THIS CLASS */
public:
  static const int RIGHT = 1;
  static const int LEFT = 2;
  static const int UP = 3;
  static const int DOWN = 4;

  int rows;
  int cols;
  int num_geese;

  void init(int rows, int cols, int num_geese);
  bool isValidLocation(int x, int y);
  pair<int,int> newLocation(int x, int y,
                            int moveDirection);
};


/* 
 * You can modify the implementation details of any part of the Robot class
 * In addition, you can define new classes/data-structures/methods
 * as required
 */

class Robot {
private:
  Grid *grid;
  int x;
  int y;
  int horizDirection;
  int vertDirection;
  
public:
  /**
   * initialize the Robot
   *
   * grid->rows is the number of rows
   * grid->cols is the number of columns
   * grid->num_geese is the number of geese
   *
   * Feel free to modify this method as required
   */
  vector <vector <int>> a;
  vector <vector <int>> inactive;
  vector <vector <int>> dp;
  void initialize(Grid *grid) {
    this->grid = grid;
    x = 0;
    y = 0;
    horizDirection = grid->RIGHT;
    vertDirection = grid->UP;

    a.resize(grid->rows);
    inactive.resize(grid->rows);
    dp.resize(grid->rows);
    for (int i = 0; i < grid->rows; i++) {
        a[i].resize(grid->cols);
        inactive[i].resize(grid->cols);
        dp[i].resize(grid->cols);
        for (int j = 0; j < grid->cols; j++) {
            a[i][j] = 0;
        }
    }
  }

  void updatedp () {
    for (int i = 0; i < grid->rows; i++) {
      for (int j = 0; j < grid->cols; j++) {
        if (!inactive[i][j]) dp[i][j] = a[i][j];
      }
    }
    // left side
    for (int i = 0; i < grid->rows; i++) {
      for (int j = 0; j < grid->cols && j < y; j++) {
        if (!inactive[i][j] && a[i][j] > 0) {
          dp[i][j] = a[i][j];
          if (grid->isValidLocation(i-1, j)) dp[i][j] += max(0, dp[i-1][j] - 1);
          if (grid->isValidLocation(i, j-1)) dp[i][j] += max(0, dp[i][j-1] - 1);
          if (grid->isValidLocation(i+1, j)) dp[i][j] += max(0, dp[i+1][j] - 1);
        }
      }
    }
    // right side
    for (int i = 0; i < grid->rows; i++) {
      for (int j = grid->cols - 1; j >= 0 && j > y; j--) {
        if (!inactive[i][j] && a[i][j] > 0) {
          dp[i][j] = a[i][j];
          if (grid->isValidLocation(i-1, j)) dp[i][j] += max(0, dp[i-1][j] - 1);
          if (grid->isValidLocation(i, j+1)) dp[i][j] += max(0, dp[i][j+1] - 1);
          if (grid->isValidLocation(i+1, j)) dp[i][j] += max(0, dp[i+1][j] - 1);
        }
      }
    }
    // up 
    for (int i = grid->rows - 1; i >= 0; i--) {
      for (int j = 0; j < grid->cols && j < y; j++) {
        if (!inactive[i][j] && a[i][j] > 0) {
          if (grid->isValidLocation(i, j-1)) dp[i][j] += max(0, dp[i][j-1] - 1);
          if (grid->isValidLocation(i, j+1)) dp[i][j] += max(0, dp[i][j+1] - 1);
          if (grid->isValidLocation(i+1, j)) dp[i][j] += max(0, dp[i+1][j] - 1);
        }
      }
    }
    // down
    for (int i = 0; i < x; i++) {
      for (int j = 0; j < grid->cols; j++) {
        if (!inactive[i][j] && a[i][j] > 0) {
          dp[i][j] = a[i][j];
          if (grid->isValidLocation(i, j-1)) dp[i][j] += max(0, dp[i][j-1] - 1);
          if (grid->isValidLocation(i, j+1)) dp[i][j] += max(0, dp[i][j+1] - 1);
          if (grid->isValidLocation(i-1, j)) dp[i][j] += max(0, dp[i-1][j] - 1);
        }
      }
    }
    // for (int i = 0; i < grid->rows; i++) {
    //   for (int j = 0; j < grid->cols; j++) {
    //     printf("%d ", dp[i][j]);
    //   }
    //   printf("\n");
    // }
  }

  void updateinactive () {
    for (int i = 0; i < grid->rows; i++) {
      for (int j = 0; j < grid->cols; j++) {
        inactive[i][j] = max(inactive[i][j] - 1, 0);
      }
    }
  }

  /**
   * Where should the robot move next
   *
   * Must return one of grid->LEFT, grid->RIGHT, grid->UP, grid->DOWN
   * 
   * It is an error to return a direction that causes
   * the robot to move off the grid.
   * 
   * The current implementation is a simple 
   * left-right-left up-down-up traversal of the entire grid
   * 
   * Please modify this method so that it does something
   * more intelligent.
   * 
   * Note: in this method, do not access any members of the
   * Evaluate class. At the beginning, your robot does not know
   * anything other than grid->rows, grid->cols, grid->num_geese
   * grid->LEFT, grid->RIGHT, grid->UP, grid->DOWN
   *
   * Specifically, all the locations and values of geese need to be
   * automatically deduced by your robot based on when gotEgg
   * is called
   */
  int move(void) {
      updatedp ();
      updateinactive();
    pair<int, int> newLoc;
    int m = 0;
    if (grid->isValidLocation(x+1, y)) {
        m = max(dp[x+1][y], m);
    }
    if (grid->isValidLocation(x, y+1)) {
        m = max(dp[x][y+1], m);
    }
    if (grid->isValidLocation(x-1, y)) {
        m = max(dp[x-1][y], m);
    }
    if (grid->isValidLocation(x, y-1)) {
        m = max(dp[x][y-1], m);
    }
    // debug(newLoc.first, newLoc.second);
    // debug(x, y);
    if (m > 0) {
      if (grid->isValidLocation(x-1, y) && m == dp[x-1][y]) {
        x--;
        return grid->UP;
      }
      if (grid->isValidLocation(x, y+1) && m == dp[x][y+1]) {
        y++;
        return grid->RIGHT;
      }
      if (grid->isValidLocation(x, y-1) && m == dp[x][y-1]) {
        y--;
        return grid->LEFT;
      }
      if (grid->isValidLocation(x+1, y) && m == dp[x+1][y]) {
        x++;
        return grid->DOWN;
      }
    }
    newLoc = grid->newLocation(x, y, horizDirection);
    // debug(newLoc.first, newLoc.second);
    // debug(grid->isValidLocation(newLoc.first, newLoc.second));

    // original code starts here
    if (grid->isValidLocation(newLoc.first, newLoc.second)) {
      // continue moving in the current horiz_direction
      x = newLoc.first;
      y = newLoc.second;
      return horizDirection;
    } else {
      // we have reached an edge.
      // reverse the horizDirection
      horizDirection = horizDirection == grid->RIGHT ?
        grid->LEFT : grid->RIGHT;

      // before starting moving in horiz_direction
      // we will try moving up (or down if that fails)

      // move in the vert_direction
      newLoc = grid->newLocation(x, y, vertDirection);
      if(!grid->isValidLocation(newLoc.first, newLoc.second)) {
        // cant move
        // need to change vertical direction
        vertDirection = vertDirection == grid->DOWN ?
          grid->UP : grid->DOWN;
        
        // check if we can move in the new vert_direction
        newLoc = grid->newLocation(x, y, vertDirection);
        if(!grid->isValidLocation(newLoc.first, newLoc.second)) {
          // both vertical movements are illegal
          // this means that grid->cols is 1
          // we just keep moving left-right-left with
          // no vertical motion
          newLoc = grid->newLocation(x, y, horizDirection);
          x = newLoc.first;
          y = newLoc.second;
          return horizDirection;
        }
      }            

      // if we come here, we have successfully changed the
      // vertDirection
      //  move vertically in the new vertDirection
      x = newLoc.first;
      y = newLoc.second;
      return vertDirection;
    }
  }
        
  /**
   * This is called by `Evaluate` to indicate that an egg of `value`
   * was found at the current location of the robot.
   * 
   * Currently, this function does nothing. 
   * You probably want to modify this function so that it remembers 
   * the location and value of this golden goose. If this is a 
   * high value goose, you might consider returning here; but make
   * sure to not return before 10 steps.
   */
  void gotEgg(int x, int y, int value) {
      if (value > 0) {
          a[x][y] = value;
          inactive[x][y] = 10;
      }
  }
};

/* 
   DO NOT MODIFY ANYTHING AFTER THIS LINE
   
   The rest of this file contains evaluation code. You don't need to
   understand the code, and it is not even necessary to read the code.
   You are not allowed to change anything here
   code, nor are you allowed to access any of these
   variables/data-members here.
   
   All you need to know is that this code will instantiate
   the Robot class, `initialize` it, and call the `move` and `got_egg`
   methods in a loop.
   
   Any modification of code after this line, will result in 
   disqualification of your entry 
*/

class EvaluationError: public exception {};
class BadMove: public EvaluationError {};

void Grid::init(int rows, int cols, int num_geese) {
  this->rows = rows;
  this->cols = cols;
  this->num_geese = num_geese;
}

bool Grid::isValidLocation(int x, int y) {
  /**
   * Helper function to check if x,y is a 
   * valid location in the grid 
   */
  return 0 <= x && x < rows && 0 <= y && y < cols;
}

pair<int,int> Grid::newLocation(int x, int y,
                                int moveDirection) {
  /**
   * Helper function to determine new co-ordinates after move
   * If robot is at `x,y` and moves in `move_direction`, what 
   * will be the new_x and new_y. This does not do any 
   * boundary value checking.
   */
  if (moveDirection == LEFT) 
    return pair<int,int>(x-1, y);
  else if (moveDirection == RIGHT) 
    return pair<int,int>(x+1, y);
  else if (moveDirection == UP) 
    return pair<int,int>(x, y+1);
  else if (moveDirection == DOWN) 
    return pair<int,int>(x, y-1);
  return pair<int,int>(-1, -1);
}

class Evaluate {
private:
  vector<vector<int> > geese;
  vector<vector<int> > lastVisited;
  int score;
  int moveNo;
  int robotX;
  int robotY;
  Robot robot;
  Grid grid;

public:
  void readInput(string inputFile) {
    int rows, cols, num_geese;
    ifstream inf(inputFile.c_str());
    inf >> rows >> cols >> num_geese;
    grid.init(rows, cols, num_geese);
    geese.resize(rows);
    for(int row=0; row<rows; row++) {
      geese[row].resize(cols);
      for(int col=0; col<cols; col++) 
        inf >> geese[row][col];
    }
  }

  void initRobot(void) {
    moveNo = 0;
    score = 0;
    robotX = 0;
    robotY = 0;
    
    lastVisited.resize(grid.rows);
    for(int row=0; row<grid.rows; row++) {
      lastVisited[row].resize(grid.cols);
      for(int col=0; col<grid.cols; col++)
        lastVisited[row][col] = -1;
    }
    robot.initialize(&grid);
  }

  /**
   * check if there's a goose in the current location
   * non-zero means there is a goose
   */
  void processCurrentCell(void) {
    int rawGooseValue = geese[robotX][robotY];
    int gooseValue;
    
    // check if 10 moves have passed since last visit
    int lastVisit = lastVisited[robotX][robotY];
    if (lastVisit >= 0 && moveNo - lastVisit < 10)
      // visited a goose too soon
      gooseValue = 0;
    else
      gooseValue = rawGooseValue;
    
    if (gooseValue > 0) {
      score += gooseValue;
      robot.gotEgg(robotX, robotY, gooseValue);
    }

    // cout << robotX << ", " << robotY
    //      << ": " << gooseValue << "[" << rawGooseValue << "]" << endl;
    
    // update the last_visited matrix
    lastVisited[robotX][robotY] = moveNo;
  }

  /**
   * Evaluate one full circuit of the robot 2*rows*cols moves
   *
   * This will be called multiple times by `evaluate` to get
   * average performance of the robot
   */
  int evaluateRobotOnce(void) {
    initRobot();
    // robot starts in cell 0
    // if there is a goose there, we need to process it
    // before any robot moves
    processCurrentCell();
    
    // now start moving the robot
    int maxMoves = 2*grid.rows*grid.cols;
    for(moveNo=0; moveNo<maxMoves; moveNo++) {
      int moveDirection = robot.move();
      pair<int,int> newLoc = grid.newLocation(robotX, robotY,
                                              moveDirection);
      robotX = newLoc.first;
      robotY = newLoc.second;
      if(!grid.isValidLocation(robotX, robotY)) {
        throw BadMove();
      }
      processCurrentCell();
    }
    return score;
  }

  string evaluate() {
    int NUM_EVALS = 1;
    int scoreSum = 0;
    int numErrors = 0;
    for (int i=0; i<NUM_EVALS; i++) {
      try {
        scoreSum += evaluateRobotOnce();
      } catch (EvaluationError e) {
        numErrors += 1;
      }
    }
    ostringstream output;
    if (numErrors == NUM_EVALS)
      output << "error";
    else
      output << int(scoreSum/NUM_EVALS);
    return output.str();
  }
};

int main(void) {
  string inputFile = "input.txt";
  string outputFile = "output.txt";
  Evaluate evaluate;
  evaluate.readInput(inputFile);
  string output = evaluate.evaluate();
  ofstream fout(outputFile.c_str());
  fout << output << endl;
}

