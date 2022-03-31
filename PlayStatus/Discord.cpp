#include "Discord.h"
#include <time.h>
#include <chrono>

#include "filter.h"

static int64_t eptime = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count();

extern char* proj_name;
extern SYS_INFO utl_sys;
extern char* pluginName;

void Discord::Initialize()
{
	DiscordEventHandlers Handle;
	memset(&Handle, 0, sizeof(Handle));
	Discord_Initialize("801042776288526349", &Handle, 1, NULL); //Default AppId
}

void Discord::Update()
{
    DiscordRichPresence discordPresence;
    memset(&discordPresence, 0, sizeof(discordPresence));
    discordPresence.state = "Editing Movie";
    discordPresence.details = utl_sys.info;
    discordPresence.startTimestamp = eptime;
    discordPresence.endTimestamp = NULL;
    discordPresence.largeImageKey = "icon";
    discordPresence.largeImageText = pluginName;
    Discord_UpdatePresence(&discordPresence);
}