#include "GSTATE.h"
#include "CMENU.h"
#include "CSETTING.h"
#include "CPLAYING.h"

GSTATE* GSTATE::createGState(stateTypes state) {
	GSTATE* gState;
	switch (state) {
	case INVALID:
		gState = nullptr;
		break;
	case MENU:
		gState = new CMENU();
		break;
	case SETTING:
		gState = new CSETTING();
		break;
	case PLAYING:
		gState = new CPLAYING(curWindow->getWindow());
		break;
	case GAMEOVER:
		gState = nullptr;
		break;
	default:
		gState = nullptr;
		break;
	}
	return gState;
}