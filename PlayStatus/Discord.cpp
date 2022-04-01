#include "Discord.h"
#include <time.h>
#include <chrono>

#include "filter.h"
#include <string>

static int64_t eptime = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count();

extern char* proj_name;
extern SYS_INFO utl_sys;
extern char* pluginName;

DiscordRichPresence discordPresence;

void Discord::Initialize()
{
	DiscordEventHandlers Handle;
	memset(&Handle, 0, sizeof(Handle));
	Discord_Initialize("801042776288526349", &Handle, 1, NULL); //Default AppId
}

void Discord::Update()
{
    memset(&discordPresence, 0, sizeof(discordPresence));
    discordPresence.state = "idle";
    discordPresence.details = utl_sys.info;
    discordPresence.startTimestamp = eptime;
    discordPresence.endTimestamp = NULL;
    discordPresence.largeImageKey = "icon";
    discordPresence.largeImageText = pluginName;
    Discord_UpdatePresence(&discordPresence);
}

void Discord::StateUpdate()
{
    //const std::string fullPath = utl_sys.project_name;
    //discordPresence.state = fullPath.substr(fullPath.find_last_of("/\\") + 1).c_str(); //文字化けするﾝｺﾞ

    discordPresence.state = utl_sys.project_name;
    Discord_UpdatePresence(&discordPresence);
}


void Discord::exit()
{
    Discord_Shutdown();
}
