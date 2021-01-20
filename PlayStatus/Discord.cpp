#include "Discord.h"
#include <time.h>
#include <chrono>


static int64_t eptime = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count();

void Discord::Initialize()
{
	DiscordEventHandlers Handle;
	memset(&Handle, 0, sizeof(Handle));
	Discord_Initialize("801042776288526349", &Handle, 1, NULL); //Your Api Key
}

void Discord::Update()
{
        DiscordRichPresence discordPresence;
        memset(&discordPresence, 0, sizeof(discordPresence));
        discordPresence.details = "Idle";
        discordPresence.startTimestamp = 1507665886;
        discordPresence.endTimestamp = 1507665886;
        discordPresence.largeImageKey = "icon";
        discordPresence.largeImageText = "Aviutl(Plugin by YU-PEI)";
        Discord_UpdatePresence(&discordPresence);
}
/* çHéñíÜ
void Discord::Update_proj(char* name)
{
    char* proj_s;
    sprintf(proj_s, "%s%s","Editing",name);
    DiscordRichPresence discordPresence;
    memset(&discordPresence, 0, sizeof(discordPresence));
    discordPresence.details = proj_s;
    discordPresence.startTimestamp = 1507665886;
    discordPresence.endTimestamp = 1507665886;
    discordPresence.largeImageKey = "icon";
    discordPresence.largeImageText = "Aviutl(Plugin by YU-PEI)";
    Discord_UpdatePresence(&discordPresence);
}
*/