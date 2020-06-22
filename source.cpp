#include <iostream>
#include "snake.h"
#include <conio.h>

using namespace std;

int main() {
	snake ob;
	ob.changeSpeed();
	ob.veKhung();
	
	while (1) {
		ob.veRan();
		if ((ob.getScore() % 50 == 0)&& (ob.getScore() !=0))ob.veToHon();
		else ob.veTao();
		ob.dieuKhien();
		ob.kiemTraAn();
		ob.kiemTraThua();
	}
	_getch();
	return 0;
}

