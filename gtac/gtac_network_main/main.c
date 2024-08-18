#include "types.h"
#include "constants.h"
#include "intrinsics.h"
#include "natives.h"
#include "common.h"
#include "gtac.h"
#include "util.h"
#include "gtac_util.h"
#include "network_main.h"

void main()
{
	THIS_SCRIPT_IS_SAFE_FOR_NETWORK_GAME();
	ALLOW_THIS_SCRIPT_TO_BE_PAUSED(false);

	while (true)
	{
		if (g_bRestartNetworkGame)
		{
			FORCE_LOADING_SCREEN(1);
			FAKE_DEATHARREST();
			WAIT(0);
			while (NETWORK_IS_OPERATION_PENDING())
				WAIT(0);
			Start_A_Network_Game_From_A_Network_Game();
			TERMINATE_THIS_SCRIPT();
		}
		else if (g_bLeaveSession || DOES_GAME_CODE_WANT_TO_LEAVE_NETWORK_SESSION())
		{
			CleanupNet();
			if (GET_RETURN_TO_FILTER_MENU())
			{
				LoadScript("MPcellphoneNetwork", 16888);
			}
			else
			{
				SHUTDOWN_AND_LAUNCH_SINGLE_PLAYER_GAME();
			}
			TERMINATE_THIS_SCRIPT();
		}

		WAIT(100);
	}

	TERMINATE_THIS_SCRIPT();
}
