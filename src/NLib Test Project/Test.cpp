#pragma comment (lib, "NCore86d.lib")
#include <NLib\NRandom.h>

auto main(int argc, char** argv) -> int
{
	double nrx = NLib::NRandom::Next();
	long long nsx = NLib::NRandom::Stretch(nrx, 50, 333);

	return false;
}