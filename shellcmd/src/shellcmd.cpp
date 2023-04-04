#include "version.cmake.h"
#include <System/tPrint.h>
#include <System/tFile.h>
#include <Image/tPicture.h>
#include <LibPNG/include/png.h>

int main(int argc, char** argv)
{
	tPrintf("shellcmdVersion %d.%d.%d\n", shellcmdVersion::Major, shellcmdVersion::Minor, shellcmdVersion::Revision);

#define TEST_LIBPNG_TYPES
#ifdef TEST_LIBPNG_TYPES
	int numBytes = 0;
	uint8* pngFileInMemory = tSystem::tLoadFile("TestImage.png", nullptr, &numBytes);
	if (!pngFileInMemory || !numBytes)
		return 10;

	png_image pngImage;
	tStd::tMemset(&pngImage, 0, sizeof(pngImage));
	pngImage.version = PNG_IMAGE_VERSION;
	int successCode = png_image_begin_read_from_memory(&pngImage, pngFileInMemory, numBytes);
	if (!successCode)
	{
		png_image_free(&pngImage);
		delete[] pngFileInMemory;
		return 20;
	}

	delete[] pngFileInMemory;
#endif

	return 0;
}
