#include <vector>
#include <iostream>
#include "Vec3.h"

using namespace std;

class EEntity {      //Engine EEntity class
   Vec3 position;
   Vec3r rotation;

   public:
   void Go( void ) {
      cout << "Testing EEntity" << endl;
   }

   void PositionEntity( double x, double y, double z ) {
      position.x = x;
      position.y = y;
      position.z = z;
   }

};

EEntity Test;

int main( void ) {
   Test.Go();
   Test.PositionEntity( 0.0, 1.0, 0.0 );

   return(0);
}