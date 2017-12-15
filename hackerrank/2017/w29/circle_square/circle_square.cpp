#include <map>
#include <unordered_map>
#include <set>
#include <list>
#include <stack>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <bitset>
#include <cstdio>
#include <cstdlib>
#include <numeric>
#include <sstream>
#include <iostream>
#include <string>
#include <climits>
#include <algorithm>
#include <vector>
#include <utility>

#include <stdio.h>
#include <string.h>
//#include <cstring>
#include <assert.h>
#include <bitset>

using namespace std;
typedef unsigned long ul;

void drawCircle( char** rastor, double w, double h, double xc1, double yc1, double r)
{
   double yr;
   double yc1r = yc1 * -1; // converting to 4th quadrant real yc1
   double r2 = r * r; // square of radius of circle :)
   if (r == 0)
   {
      return;
   }

   for(int x = 0; x < w; ++x) {
      for(int y = 0; y < h; ++y) {
         // converting values to 4th quadrant equal to get real y
         yr = double(y) * -1.0; 

         // cout << "x:" << x << " y:" << yr << " = ";
         // cout << (x - xc1)*(x - xc1) + (yr - yc1r)*(yr - yc1r) << endl;
         // checking equation of circle equality
         if ( (x - xc1)*(x - xc1) + (yr - yc1r)*(yr - yc1r) <= r2 )
         {
            rastor[y][x] = '#';
         }
      }
   }
   return;
}

void drawSquare( char** rastor, int w, int h, double x1, double y1, double x3, double y3)
{
   // converting to 4th quadrant real y values
   double y1r = y1 * -1;
   double y3r = y3 * -1;
   double yr;

   // say given points are A and C diagnol ends
   double xc, yc, xd, yd, x2, y2, x4, y4;

   xc = (x1 + x3)/2  ;  yc = (y1r + y3r)/2  ;    // Center point
   xd = (x1 - x3)/2  ;  yd = (y1r - y3r)/2  ;    // Half-diagonal

   x2 = xc - yd  ;  y2 = yc + xd;   // Third corner say B
   x4 = xc + yd  ;  y4 = yc - xd;   // Fourth corner say D

   // vector AB and BC
   double vabi, vabj, vbci, vbcj;
   vabi = x2 - x1;
   vabj = y2 - y1r;
   vbci = x3 - x2;
   vbcj = y3r - y2;

   double ab_dot_ab = vabi*vabi + vabj*vabj;
   double bc_dot_bc = vbci*vbci + vbcj*vbcj;
   

   for(int x = 0; x < w; ++x) {
      for(int y = 0; y < h; ++y) {
         // converting values to 4th quadrant equal to get real y
         yr = double(y) * -1; 

         // checking dot products
         double dot_ab = vabi*(x-x1) + vabj*(yr-y1r);
         double dot_bc = vbci*(x-x2) + vbcj*(yr-y2);

         if ( dot_ab <= ab_dot_ab && dot_ab >= 0 &&
               dot_bc <= bc_dot_bc && dot_bc >= 0)
         {
            rastor[y][x] = '#';
         }
      }
   }

   return;
}

void printRastor( char** rastor, int w, int h)
{
   for(int i = 0; i < h; ++i) {
      // cout << i << " ";
      for(int j = 0; j < w; ++j) {
         cout << rastor[i][j];
      }
      cout << endl;
   }
}

int main() {
   int w,h;
   double xc1,yc1,r,x1,y1,x3,y3;
   cin >> w >> h;
   cin >> xc1 >> yc1 >> r;
   cin >> x1 >> y1 >> x3 >> y3;

   char** rastor = new char*[h];
   for(int i = 0; i < h; ++i) {
      rastor[i] = new char[w];
      memset (rastor[i],'.',w);
   }

   drawCircle( rastor, w, h, xc1, yc1, r);
   drawSquare( rastor, w, h, x1, y1, x3, y3);
   printRastor( rastor, w, h);

   return 0;
}
