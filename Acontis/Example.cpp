//
// Created by Kumar Chakravarthy on 23-Sep-23.
//

#include <iostream>

static EC_T_PROCESS_VAR_INFO s_InputProcessVar;
staic EC_T_DWORD s_dwOutputOffset;
static EC_T_DWORD s_dwOUtputSize;

static EC_T_DWORD myAppPerpare(T_EC_DEMO_APP_CONTEXT* pAppContext) {
    EC_T_WORD dwRes = EC_E_NOERROR;

    dwRes = ecatFindInpVarByName("Slave_1004 [EL1014].Channel 1.Input", &s_InputProcessVar);

    if(dwRes != EC_E_NOERROR) {
        EcLogMsg(EC_LOG_LEVEL_ERROR, (pEcLogContext, EC_LOG_LEVEL_ERROR, "ERROR: ecatFindInpVarByName failed, return with %s (0x%x) \n", ecatGetText(dwRes), dwRes))
    }

    EC_T_CFG_SLAVE_INFO oCfgSlaveInfo;
    OsMemset(&oCfgSlaveInfo, 0, sizeof(EC_T_CFG_SLAVE_INFO));
    dwRes = ecatGetSlaveInfo(EC_TRUE, 1003, &oCfgSlaveInfo);
    if(dwRes != EC_E_NOERROR) {
        EcLogMsg(EC_LOG_LEVEL_ERROR, (pEcLogContext, EC_LOG_LEVEL_ERROR, "ERROR: ecatFindInpVarByName failed, return with %s (0x%x) \n", ecatGetText(dwRes), dwRes))
    }

    s_dwOutputOffset = oCfgSlaveInfo.dwPdOffsOut;
    s_dwOUtputSize = oCfgSlaveInfo.dwPdSizeOut;

return  EC_E_NOERROR;
}

static EC_T_DWORD myAppWordpd(T_EC_DEMO_APP_CONTEXT* pAppContext)
{
    EC_T_BYTE* pbyPdIn = ecatGetProcessImageInputPtr();
    EC_T_BYTE* pbyPdOut = ecatGetProcessImageOutputPtr();

    static EC_T_BOOL s_bInputLast = 0;
    EC_T_BOOL bInputCur = 0;

    bInputCur = EC_TESTBIT(pbyPdIn, s_InputProcessVar.nBitOffs);

    if(s_bInputLast != s_bInputCur) {
        if(s_bInputLast) {
            EC_T_BYTE byCnt = 0;

            EC_COPYBITS(&byCnt, 0, pbyPdOut, s_dwOutputOffset, s_dwOUtputSize);

            byCnt++;

            EC_COPYBITS(pbyPdOut, s_dwOutputOffset, &byCnt, 0, s_dwOUtputSize);
        }
    }

    s_bInputLast = s_bInputCur;

return  EC_E_NOERROR;
}

int main() {
    std::cout << "Hello, World!\n";
    return 0;
}
