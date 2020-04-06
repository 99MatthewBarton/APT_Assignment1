
#include "Breadcrumb.h"

Breadcrumb::Breadcrumb(int x, int y, bool stale): x(x), y(y), stale(stale) {
   std::cout << "TEST - BREADCRUMB x: " << x << " y: " << y << std::endl;
}

Breadcrumb::~Breadcrumb() {
   // TODO
}

int Breadcrumb::getX() {
   return x;
}

int Breadcrumb::getY() {
   return y;
}

bool Breadcrumb::isStale() {
   return stale;
}

void Breadcrumb::setStale(bool stale) {
   this -> stale = stale;
}
