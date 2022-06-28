#include "mylib.h"
#include "version.cmake.h"
#include <System/tPrint.h>

void myLib::myLibPrintVersion()
{ 
    tPrintf("mylibVersion %d.%d.%d\n", mylibVersion::Major, mylibVersion::Minor, mylibVersion::Revision);
}
