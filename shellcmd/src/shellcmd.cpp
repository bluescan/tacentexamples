#include "version.cmake.h"
#include <System/tPrint.h>

int main(int argc, char** argv)
{
    tPrintf("shellcmdVersion %d.%d.%d\n", shellcmdVersion::Major, shellcmdVersion::Minor, shellcmdVersion::Revision);

    return 0;
}
