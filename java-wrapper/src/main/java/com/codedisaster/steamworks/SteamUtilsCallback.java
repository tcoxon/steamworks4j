package com.codedisaster.steamworks;

public interface SteamUtilsCallback {

	void onSteamShutdown();
	
	void onGamepadTextInputDismissed(boolean submitted, String text);

}
