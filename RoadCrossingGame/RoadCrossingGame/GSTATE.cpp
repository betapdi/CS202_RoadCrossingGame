#include "GSTATE.h"
#include "CMENU.h"
#include "CSETTING.h"
#include "CPLAYING.h"
#include "CCREDIT.h"
#include "CRATING.h"
#include "CGAMEOVER.h"
#include "CPAUSE.h"

GSTATE* GSTATE::createGState(stateTypes state, int type) {
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
	case CREDIT:
		gState = new CCREDIT();
		break;
	case RANKING:
		gState = new CRATING();
		break;
	case PLAYING:
		gState = new CPLAYING(curWindow->getWindow(), type);
		break;
	case GAMEOVER:
		gState = new CGAMEOVER();
		break;
	case PAUSE:
		gState = new CPAUSE();
		break;
	default:
		gState = nullptr;
		break;
	}
	return gState;
}