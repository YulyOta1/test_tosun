      // TestTSMasterC.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <windows.h>
#include "TSMaster.h"
#include "seedNKeyDiag.h"
#include "CGW_cfg.h"
using namespace std;

void __stdcall TSMasterLogger(const char* AStr, const s32 ALevel)
{
    std::cout << "TSMaster Logger: " << ALevel << ": " << AStr << "\n";
}




bool CheckOK(const int ACode) 
{
    char* desc;
    vErrorCode = ACode;
    if (0 == ACode) return true;
    if (0 == tsapp_get_error_description(ACode, &desc)) {
        std::cout << "API error: " << desc << "\n";
    } else {
        std::cout << "API error code: " << ACode << "\n";
    }
    return false;
}

int main()
{
	if (initialize_lib_tsmaster("TSMasterTest\n") == 0) {
		cout<<"initialize success\n";
	}
	else {
		cout << "initialize failed\n";
		return 0;
	}
	if (tsapp_set_can_channel_count(CGW.CAN_CH_count) == 0) {
		cout << "set channel success\n";
	}
	else {
		cout << "set channel failed\n";
		return 0;
	}
	tsapp_show_tsmaster_window("Channel Selection", true);
	tsapp_show_hardware_configuration_window();
	if (tsapp_connect() == 0) {
		cout << "connect successful\n";
	}
	else {
		cout << "connect failed\n";
		return 0;
	}
	if (tsdiag_can_create(CGW.Diagnostic_Module_Handle, CGW.CH_Index, CGW.CANFD_Support, CGW.Max_DLC, CGW.RequestID, CGW.RequestID_is_Std, CGW.ResponseID, CGW.ResponseID_is_Std, CGW.FunctionID, CGW.FunctionID_is_Std) == 0) {
		cout << "diag module create success\n";
	}
	else {
		cout << "diag module create failed\n";
		return 0;
	}


	if (tsapp_connect() == 0) {
		cout << "connect success\n";
	}
	else {
		cout << "connect failed\n";
		return 0;
	}
	if (tsdiag_set_p2_timeout(*CGW.Diagnostic_Module_Handle, CGW_UDS_timing.p2_timeout) == 0) {
		cout << "set timing success\n";
	}
	else {
		cout << "set timing failed\n";
		return 0;
	}
	if (tsdiag_set_p2_extended(*CGW.Diagnostic_Module_Handle, CGW_UDS_timing.p2_extended) == 0) {
		cout << "set timing success\n";
	}
	else {
		cout << "set timing failed\n";
		return 0;
	}
	if (tsdiag_set_s3_servertime(*CGW.Diagnostic_Module_Handle, CGW_UDS_timing.s3_servertime) == 0) {
		cout << "set timing success\n";
	}
	else {
		cout << "set timing failed\n";
		return 0;
	}
	if (tsdiag_set_s3_clienttime(*CGW.Diagnostic_Module_Handle, CGW_UDS_timing.s3_clienttime) == 0) {
		cout << "set timing success\n";
	}
	else {
		cout << "set timing failed\n";
		return 0;
	}
	objDelay.delay(1);
	if (tstp_can_send_functional(*CGW.Diagnostic_Module_Handle, CGW_UDS_message.programming_session, CGW.ArraySize) == 0)
	{
		cout << "send diagnostic payload Success!\n";
	}
	else {
		cout << "send diagnostic payload Failed!\n";
		return 0;
	}
	objDelay.delay(1);
	if (tsdiag_can_security_access_request_seed(*CGW.Diagnostic_Module_Handle, SeedNKey.SeedLvl, SeedNKey.seedBuffer, &SeedNKey.ARecSeedSize) == 0) {
		GenerateKeyEx(SeedNKey.seedBuffer,          /* Array for the seed [in] */
			SeedNKey.seedLenght,               /* Length of the array for the seed [in] */
			SeedNKey.SecurityLvl,         /* Security level [in] */
			NULL,                     /* Name of the active variant [in] */
			SeedNKey.AKey,                /* Array for the key [in, out] */
			SeedNKey.keyLenght,             /* Maximum length of the array for the key [in] */
			SeedNKey.oActualKeyArraySize);        /* Length of the key [out] */
	}
	else {
		cout << "request seed failed\n";
		return 0;
	}
		if (tsdiag_can_security_access_send_key(*CGW.Diagnostic_Module_Handle, SeedNKey.KeyLvl, SeedNKey.AKey, SeedNKey.RecSeedSize) == 0) {
			cout << "accesskey success\n";
		}
		else {
			cout << "accesskey failed\n";
			return 0;
		}
	
	if (tsdiag_can_write_data_by_identifier(*CGW.Diagnostic_Module_Handle, CGW.Data_ID,
		CGW_UDS_message.writeData, 3076) == 0x00){
		cout << "writedata success\n";
									}
	else {
		cout << "writedata failed\n";
		return 0;
	}
	if (tstp_can_request_and_get_response(*CGW.Diagnostic_Module_Handle, CGW_UDS_message.reqDataArray, CGW.ArraySize, CGW_UDS_message.responseArray, &CGW_UDS_message.responseArraySize) == 0)
	{
		cout << "reset from soft success\n";
	}
	else {
		cout << "reset from soft failed\n";
		return 0;
	}
	tsapp_disconnect();
	finalize_lib_tsmaster();
}
