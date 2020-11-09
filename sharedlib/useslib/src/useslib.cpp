#include "version.cmake.h"
#include "mylib.h"
#include <System/tPrint.h>

int main(int argc, char** argv)
{
    myLib myLib;

    myLib.myLibPrintVersion();
    tPrintf("useslibVersion %d.%d.%d\n", useslibVersion::Major, useslibVersion::Minor, useslibVersion::Revision);

    return 0;
}
