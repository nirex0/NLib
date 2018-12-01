#pragma comment (lib, "NCore86d.lib")
#include <NLib\NFile.h>

int main()
{
	NLib::NFile f;
	f.WriteAllText("Test.txt", "test");

	return 0;
}