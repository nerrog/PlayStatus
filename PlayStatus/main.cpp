#include "Discord.h"
#include "filter.h"
#include <Windows.h>

Discord* g_Discord; //DiscordRPC�p�̃|�C���^
SYS_INFO utl_sys;
bool inited = false;
char* pluginName = "PlayStatus 0.0.4"; //�v���O�C�����E�o�[�W����
char* proj_name; //�v���W�F�N�g��(������)

// �t�B���^�v���O�C���\����
FILTER_DLL filter = {
	NULL,	// int flag
	0, 0,	// int x,y
	pluginName,	// TCHAR *name
	NULL,NULL,NULL,	// int track_n, TCHAR **track_name, int *track_default
	NULL,NULL,	// int *track_s, *track_e
	NULL,NULL,NULL,	// int check_n, TCHAR **check_name, int *check_default
	NULL,	// (*func_proc)
	func_init,	// (*func_init)
	func_exit,	// (*func_exit)
	NULL,	// (*func_update)
	NULL,	// (*func_WndProc)
	NULL,NULL,	// reserved
	NULL,	// void *ex_data_ptr
	NULL,	// int ex_data_size
	pluginName,	// TCHAR *information
	NULL,	// (*func_save_start)
	NULL,	// (*func_save_end)
	NULL,	// EXFUNC *exfunc;
	NULL,	// HWND	hwnd;
	NULL,	// HINSTANCE dll_hinst;
	NULL,	// void	*ex_data_def;
	NULL,	// (*func_is_saveframe)
	func_project_load,	// (*func_project_load)
	func_project_save,	// (*func_project_save)
	NULL,	// (*func_modify_title)
	NULL,	// TCHAR *dll_path;
};

// SYS_INFO���擾����RPC���A�b�v�f�[�g����֐�
void update_edit_name(FILTER* fp, void* editp)
{
	//SYS_INFO�̎擾
	fp->exfunc->get_sys_info(editp, &utl_sys);
	//RPC�A�b�v�f�[�g
	g_Discord->StateUpdate();
}

BOOL func_init(FILTER* fp) {
	//�t�B���^�v���O�C���������֐�
	if (!inited) {
		//SYS_INFO�̎擾
		fp->exfunc->get_sys_info(nullptr, &utl_sys);

		//RPC������
		g_Discord->Initialize();
		g_Discord->Update();
		inited = true;
	}
	return TRUE;
}

BOOL func_project_load(FILTER* fp, void* editp, void* data, int size)
{
	update_edit_name(fp, editp);
	return TRUE;
}

BOOL func_project_save(FILTER* fp, void* editp, void* data, int* size)
{
	update_edit_name(fp, editp);
	return TRUE;
}

BOOL func_exit(FILTER* fp)
{
	//RPC�ؒf
	g_Discord->exit();

	return TRUE;
}



EXTERN_C FILTER_DLL __declspec(dllexport)* __stdcall GetFilterTable(void)
{
	return &filter;
} 
