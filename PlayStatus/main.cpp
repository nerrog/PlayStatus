#include <string>

#include "Discord.h"
#include "filter.h"
#include <Windows.h>

#include "RPC_State.h"

//�ϐ��Ƃ��|�C���^
Discord* g_Discord; //DiscordRPC�p�̃|�C���^
SYS_INFO utl_sys; //SYS_INFO
FILE_INFO fi; //FILE_INFO
bool inited = false; //�������ς݂�
const char* pluginName = "PlayStatus 0.0.4 by YU-PEI"; //�v���O�C�����E�o�[�W����

//�ݒ�E�B���h�E�p
#define CHECK_N 3
char* plugin_cfg_check[] = { "DiscordRPC��L����", "�ҏW�t�@�C������\��", "�v���W�F�N�g�ύX��A�o�ߎ��Ԃ����Z�b�g" };
int plugin_cfg_check_default[] = { 1, 1, 0 };


//�ݒ�L�^�p�N���X
RPC_State rpc_state;

// �t�B���^�v���O�C���\����
FILTER_DLL filter = {
	FILTER_FLAG_EX_INFORMATION | FILTER_FLAG_PRIORITY_LOWEST | FILTER_FLAG_WINDOW_THICKFRAME | FILTER_FLAG_ALWAYS_ACTIVE,	// int flag
	0, 0,	// int x,y
	const_cast<char*>("PlayStatus"),	// TCHAR *name
	NULL,nullptr,nullptr,	// int track_n, TCHAR **track_name, int *track_default
	nullptr,nullptr,	// int *track_s, *track_e
	CHECK_N, plugin_cfg_check, plugin_cfg_check_default,	// int check_n, TCHAR **check_name, int *check_default
	nullptr,	// (*func_proc)
	func_init,	// (*func_init)
	func_exit,	// (*func_exit)
	func_update,	// (*func_update)
	nullptr,	// (*func_WndProc)
	nullptr,nullptr,	// reserved
	nullptr,	// void *ex_data_ptr
	NULL,	// int ex_data_size
	const_cast<char*>(pluginName),	// TCHAR *information
	nullptr,	// (*func_save_start)
	nullptr,	// (*func_save_end)
	nullptr,	// EXFUNC *exfunc;
	nullptr,	// HWND	hwnd;
	nullptr,	// HINSTANCE dll_hinst;
	nullptr,	// void	*ex_data_def;
	nullptr,	// (*func_is_saveframe)
	func_project_load,	// (*func_project_load)
	func_project_save,	// (*func_project_save)
	nullptr,	// (*func_modify_title)
	nullptr,	// TCHAR *dll_path;
};

// FILE_INFO���擾����RPC���A�b�v�f�[�g����֐�
void update_edit_name(FILTER* fp, void* editp)
{
	//FILE_INFO�̎擾
	fp->exfunc->get_file_info(editp, &fi);
	//RPC�A�b�v�f�[�g
	g_Discord->StateUpdate();
}

//INI���擾����RPC_State�N���X�ϐ��Ƃ��ĕԂ��֐�
RPC_State get_cfg(FILTER* fp)
{
	RPC_State *_rpc_state = new RPC_State;

	for (int i=0 ; i < CHECK_N; i++)
	{
		if (i ==0)
		{
			//enable rpc
			_rpc_state->Enable_RPC = fp->exfunc->ini_load_int(fp, "ENABLE_RPC", 1);
		}
		else if (i == 1)
		{
			//show file name
			_rpc_state->Show_FileName = fp->exfunc->ini_load_int(fp, "SHOW_FILE_NAME", 1);
		}
		else if(i == 2)
		{
			//reset eptime
			_rpc_state->Rest_Eptime = fp->exfunc->ini_load_int(fp, "RESET_EPTIME", 0);
		}
	}

	return *_rpc_state;
}

//RPC_State����INI�ɏ������ޕϐ�
void save_cfg(FILTER* fp, RPC_State state)
{
	for (int i = 0; i < CHECK_N; i++)
	{
		if (i == 0)
		{
			//enable rpc
			fp->exfunc->ini_save_int(fp, "ENABLE_RPC", state.Enable_RPC);
		}
		else if (i == 1)
		{
			//show file name
			fp->exfunc->ini_save_int(fp, "SHOW_FILE_NAME", state.Show_FileName);
		}
		else if (i == 2)
		{
			//reset eptime
			fp->exfunc->ini_save_int(fp, "RESET_EPTIME", state.Rest_Eptime);
		}
	}
}

BOOL func_init(FILTER* fp) {
	//�t�B���^�v���O�C���������������Ƃ��ɌĂяo�����֐�
	if (!inited) {
		//SYS_INFO�̎擾
		fp->exfunc->get_sys_info(nullptr, &utl_sys);

		//�ݒ�擾
		rpc_state = get_cfg(fp);

		//RPC������
		if (rpc_state.Enable_RPC == 1)
		{
			g_Discord->Initialize();
			g_Discord->Update();
		}

		inited = true;
	}
	return TRUE;
}

BOOL func_project_load(FILTER* fp, void* editp, void* data, int size)
{
	//�v���W�F�N�g�����[�h���ꂽ�Ƃ��ɌĂяo�����֐�
	update_edit_name(fp, editp);
	return TRUE;
}

BOOL func_project_save(FILTER* fp, void* editp, void* data, int* size)
{
	//�v���W�F�N�g���ۑ����ꂽ�Ƃ��ɌĂяo�����֐�
	update_edit_name(fp, editp);
	return TRUE;
}

BOOL func_update(FILTER* fp, int status)
{
	//�ݒ肪�ύX���ꂽ�Ƃ�
	switch (status)
	{
	case FILTER_UPDATE_STATUS_CHECK:
		OutputDebugString(std::to_string(status).c_str());
		//Toggle RPC
		
		break;
	case FILTER_UPDATE_STATUS_CHECK+1:
		//Show FileName
		break;
	case FILTER_UPDATE_STATUS_CHECK+2:
		//Reset EptTime
		break;
	}

	return TRUE;
}



BOOL func_exit(FILTER* fp)
{
	//�v���O�C�����A�����[�h�����Ƃ��ɌĂяo�����֐�
	//RPC�ؒf
	g_Discord->exit();

	//�ݒ�ۑ�
	save_cfg(fp, rpc_state);

	return TRUE;
}



EXTERN_C FILTER_DLL __declspec(dllexport)* __stdcall GetFilterTable(void)
{
	return &filter;
} 
