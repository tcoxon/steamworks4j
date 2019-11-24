#include "SteamUtilsCallback.h"
#include <cstdlib>

static SteamUtilsCallback* s_messageHookInstance = NULL;

SteamUtilsCallback::SteamUtilsCallback(JNIEnv* env, jobject callback)
	: SteamCallbackAdapter(env, callback)
	, m_CallbackSteamShutdown(this, &SteamUtilsCallback::onSteamShutdown)
	, m_CallbackGamepadTextInputDismissed(this, &SteamUtilsCallback::onGamepadTextInputDismissed) {

}

SteamUtilsCallback::~SteamUtilsCallback() {

}

extern "C" void __cdecl SteamAPIDebugTextHook(int severity, const char *debugText) {
	if (s_messageHookInstance != NULL) {
		s_messageHookInstance->onWarningMessage(severity, debugText);
	}
}

void SteamUtilsCallback::enableWarningMessageHook(bool enabled) {
	s_messageHookInstance = enabled ? this : NULL;
	SteamUtils()->SetWarningMessageHook(enabled ? &SteamAPIDebugTextHook : NULL);
}

void SteamUtilsCallback::onWarningMessage(int severity, const char *debugText) {
	invokeCallback({
		callVoidMethod(env, "onWarningMessage", "(ILjava/lang/String;)V",
			severity, env->NewStringUTF(debugText));
	});
}

void SteamUtilsCallback::onSteamShutdown(SteamShutdown_t* callback) {
    invokeCallback({
        callVoidMethod(env, "onSteamShutdown", "()V");
    });
}

void SteamUtilsCallback::onGamepadTextInputDismissed(GamepadTextInputDismissed_t* callback) {
	invokeCallback({
		char *buf = (char *)malloc(callback->m_unSubmittedText + 1);
		SteamUtils()->GetEnteredGamepadTextInput(buf, callback->m_unSubmittedText + 1);
		callVoidMethod(env, "onGamepadTextInputDismissed", "(ZLjava/lang/String;)V",
			callback->m_bSubmitted, env->NewStringUTF(buf));
		free(buf);
	});
}
