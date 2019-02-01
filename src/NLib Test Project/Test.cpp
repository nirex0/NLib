#pragma comment (lib, "NCore86d.lib")
#include <NLib\NRandom.h>

int main()
{

	NLib::NRandom nr;
	NLib::NumberManip nmp;
	double nrx = nr.Next();

	long long nsx = nmp.Stretch(nrx, 50, 333);

	return 0;
}