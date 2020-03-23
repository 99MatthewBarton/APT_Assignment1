
#include "Trail.h"


Trail::Trail() {
   Breadcrumb * breadcrumbs [TRAIL_ARRAY_MAX_SIZE];
   int length = 0;
}

Trail::~Trail() {
   // TODO
}

int Trail::size() {
   return length;
}

Breadcrumb* Trail::getPtr(int i) {
   return breadcrumbs[i];
}

void Trail::addCopy(Breadcrumb* t) {
   breadcrumbs[length] = t;
   length++;
}

bool Trail::contains(int x, int y) {
   for (int i = 0; i < length; i++) {
      if (breadcrumbs[i] -> getX() == x && breadcrumbs[i] -> getY() == y) {
         return true;
      }
   }
   return false;
}
