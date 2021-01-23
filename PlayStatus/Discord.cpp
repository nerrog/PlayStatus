#include "Discord.h"
#include <time.h>
#include <chrono>

static int64_t eptime = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count();

extern char* proj_name;
extern char* utl_ver;

void Discord::Initialize()
{
	DiscordEventHandlers Handle;
	memset(&Handle, 0, sizeof(Handle));
	Discord_Initialize("KEY", &Handle, 1, NULL); //Your Api Key
}

void Discord::Update()
{
        DiscordRichPresence discordPresence;
        memset(&discordPresence, 0, sizeof(discordPresence));
        discordPresence.state = "Editing Movie";
        discordPresence.details = proj_name;
        discordPresence.startTimestamp = eptime;
        discordPresence.endTimestamp = NULL;
        discordPresence.largeImageKey = "icon";
        discordPresence.largeImageText = "Aviutl(Plugin by YU-PEI)";
        discordPresence.smallImageKey = "icon";
        discordPresence.smallImageText = utl_ver;
        Discord_UpdatePresence(&discordPresence);
}