#include "main.h"

#include "msgdump.h"

int _dumpDefaultCoordinateX = 20;
int _dumpDefaultCoordinateY = 20;
int _dumpCoordinateX = _dumpDefaultCoordinateX;
int _dumpCoordinateY = _dumpDefaultCoordinateY;
int _dumpCharWidth = 9;
int _dumpLineHeight = 19;

DxLibOut dxout;
DxLibEndLine dxendl;
DxLibClear dxclr;

void msgDumpReset(){
	static int BLACK = GetColor(0, 0, 0);
	_dumpCoordinateY = 20;
	DrawBox(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, BLACK, 1);
}

DxLibOut &operator <<(DxLibOut &dlo, const DxLibEndLine &){
	_dumpCoordinateX = _dumpDefaultCoordinateX;
	_dumpCoordinateY += _dumpLineHeight;
	return dlo;
}
DxLibOut &operator <<(DxLibOut &dlo, const DxLibClear &){
	static int BLACK = GetColor(0, 0, 0);
	//DrawBox(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, BLACK, 1);
	_dumpCoordinateX = _dumpDefaultCoordinateX;
	_dumpCoordinateY = _dumpDefaultCoordinateY;
	return dlo;
}
