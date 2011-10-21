#ifndef __MSGDUMP_H__
#define __MSGDUMP_H__

#include <sstream>
#include "graphicResource.h"
extern int _dumpDefaultCoordinateX;
extern int _dumpDefaultCoordinateY;
extern int _dumpCoordinateX;
extern int _dumpCoordinateY;
extern int _dumpCharWidth;
extern int _dumpLineHeight;

template<class T>
void msgDump(const T &value){
  static int WHITE = GetColor(255, 255, 255);
  ostringstream oss;
  oss << value;
  graresource.drawstring<string>(_dumpCoordinateX, _dumpCoordinateY, oss.str(),WHITE);
  _dumpCoordinateY += _dumpLineHeight;
}

extern class DxLibOut{} dxout;
extern class DxLibEndLine{} dxendl;
extern class DxLibClear{} dxclr;

template<class T>
DxLibOut &operator <<(DxLibOut &dlo, const T &value){
  static int WHITE = GetColor(255, 255, 255);
  ostringstream oss;
  oss << value;
  graresource.drawstring(_dumpCoordinateX, _dumpCoordinateY, oss.str(),WHITE);
  _dumpCoordinateX += _dumpCharWidth * static_cast<int>(oss.str().length());
  return dlo;
}
DxLibOut &operator <<(DxLibOut &dlo, const DxLibEndLine &);
DxLibOut &operator <<(DxLibOut &dlo, const DxLibClear &);

void msgDumpReset();

#endif // __MSGDUMP__
