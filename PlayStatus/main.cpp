#include "Discord.h"
#include "filter.h"
#include <Windows.h>


Discord* g_Discord; //DiscordRPC用のポインタ
bool inited = false;
char* pluginname = "PlayStatus ver.0.0.2 by YU-PEI"; //プラグイン名・バージョン
char* proj_name; //プロジェクト名(未実装)
char* utl_ver; //Aviutl本体のバージョン (未実装)


// フィルタプラグイン構造体
FILTER_DLL filter = {
	NULL,	// int flag
	0, 0,	// int x,y
	pluginname,	// TCHAR *name
	NULL,NULL,NULL,	// int track_n, TCHAR **track_name, int *track_default
	NULL,NULL,	// int *track_s, *track_e
	NULL,NULL,NULL,	// int check_n, TCHAR **check_name, int *check_default
	NULL,	// (*func_proc)
	NULL,	// (*func_init)
	NULL,	// (*func_exit)
	NULL,	// (*func_update)
	NULL,	// (*func_WndProc)
	NULL,NULL,	// reserved
	NULL,	// void *ex_data_ptr
	NULL,	// int ex_data_size
	pluginname,	// TCHAR *information
	NULL,	// (*func_save_start)
	NULL,	// (*func_save_end)
	NULL,	// EXFUNC *exfunc;
	NULL,	// HWND	hwnd;
	NULL,	// HINSTANCE dll_hinst;
	NULL,	// void	*ex_data_def;
	NULL,	// (*func_is_saveframe)
	NULL,	// (*func_project_load)
	func_project_save,	// (*func_project_save)
	NULL,	// (*func_modify_title)
	NULL,	// TCHAR *dll_path;
};
void Init() {
	//DiscordRPC初期化関数
	//utl_ver = sip->info;
	g_Discord->Initialize();
	g_Discord->Update();

}


BOOL func_init(FILTER* fp) {
	//フィルタプラグイン初期化関数
	if (!inited) {
		Init();
		inited = true;
	}
	return TRUE;
}

BOOL func_project_save(FILTER* fp, void* editp, void* data, int* size) {
	
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

