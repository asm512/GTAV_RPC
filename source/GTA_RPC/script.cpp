#define _CRT_SECURE_NO_WARNINGS

#include "script.h"
#include "keyboard.h"
#include "discord-rpc\discord-rpc.h"
#include <string>
#include <ctime>
#include <vector>

#pragma warning(disable : 4244 4305) // double <-> float conversions

static const char* APPLICATION_ID = "489135107895066635";
//static int64_t StartTime;
static int SendPresence = 1;

int ShowNotification(char *text)
{
	UI::_SET_NOTIFICATION_TEXT_ENTRY("STRING");
	UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(text);
	return UI::_DRAW_NOTIFICATION(0, 0);
}

void menu_beep()
{
	AUDIO::PLAY_SOUND_FRONTEND(-1, "NAV_UP_DOWN", "HUD_FRONTEND_DEFAULT_SOUNDSET", 0);
}

static void updateDiscordPresence()
{
	if (SendPresence) {
		//char buffer[256];
		DiscordRichPresence discordPresence;
		memset(&discordPresence, 0, sizeof(discordPresence));
		discordPresence.state = "State";
		discordPresence.details = "Details";
		//discordPresence.startTimestamp = StartTime;
		//discordPresence.endTimestamp = time(0) + 5 * 60;
		discordPresence.largeImageKey = "gta_logo";
		//discordPresence.smallImageKey = "ptb-small";
		//discordPresence.partyId = "party1234";
		//discordPresence.partySize = 1;
		//discordPresence.partyMax = 6;
		//discordPresence.matchSecret = "xyzzy";
		//discordPresence.joinSecret = "join";
		//discordPresence.spectateSecret = "look";
		discordPresence.instance = 0;
		Discord_UpdatePresence(&discordPresence);
	}
	else {
		Discord_ClearPresence();
	}
}


static void handleDiscordReady(const DiscordUser* connectedUser)
{
	//std::string hash("#");

	//std::string username = connectedUser->username;

	//std::string StartupMessage = "Discord: Connected to " + username + hash + connectedUser->discriminator;

	////char *startmsg = &StartupMessage[0u];

	//char* startmsg = const_cast<char*>(StartupMessage.c_str());

	//ShowNotification(startmsg);
}

static void handleDiscordDisconnected(int errcode, const char* message)
{
	//printf("\nDiscord: disconnected (%d: %s)\n", errcode, message);
}

static void handleDiscordError(int errcode, const char* message)
{
	//printf("\nDiscord: error (%d: %s)\n", errcode, message);
}

static void handleDiscordJoin(const char* secret)
{
	//printf("\nDiscord: join (%s)\n", secret);
}

static void handleDiscordSpectate(const char* secret)
{
	//printf("\nDiscord: spectate (%s)\n", secret);
}


static void discordInit()
{
	DiscordEventHandlers handlers;
	memset(&handlers, 0, sizeof(handlers));
	handlers.ready = handleDiscordReady;
	handlers.disconnected = handleDiscordDisconnected;
	handlers.errored = handleDiscordError;
	handlers.joinGame = handleDiscordJoin;
	handlers.spectateGame = handleDiscordSpectate;
	Discord_Initialize(APPLICATION_ID, &handlers, 1, NULL);
}

void main()
{	
	ShowNotification("RPC Loaded");
	discordInit();
	//menu_beep();
	while (true)
	{
		updateDiscordPresence();
		WAIT(0);
	}
}

void ScriptMain()
{
	main();
}

