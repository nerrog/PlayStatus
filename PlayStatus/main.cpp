#include "Discord.h"
#include "filter.h"
#include <Windows.h>

Discord* g_Discord;
bool inited = false;


FILTER_DLL filter = {
	NULL,
	0,0,
	NULL, //?
	NULL,
	NULL,NULL,
	NULL,NULL,NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,NULL,
	NULL,
	NULL,
	"PlayStatus ver.0.0.1 by YU-PEI",
	NULL,
	NULL,
};

void Init() {
	g_Discord->Initialize();
	g_Discord->Update();

}


BOOL func_init(FILTER* fp) {
	if (!inited) {
		Init();
		inited = true;
	}
	return TRUE;
}


EXTERN_C FILTER_DLL __declspec(dllexport)* __stdcall GetFilterTable(void)
{
	if (GetModuleHandleA("PlayStatus.auf") != NULL) {
		Init();
		inited = true;
	}
	return &filter;
}

