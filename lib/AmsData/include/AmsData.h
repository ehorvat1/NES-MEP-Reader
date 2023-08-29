#ifndef _AMSDATA_H
#define _AMSDATA_H

#include "Arduino.h"
#include <Timezone.h>

enum AmsType {
    AmsTypeAutodetect = 0x00,
    AmsTypeAidon = 0x01,
    AmsTypeKaifa = 0x02,
    AmsTypeKamstrup = 0x03,
    AmsTypeIskra = 0x08,
    AmsTypeLandisGyr = 0x09,
    AmsTypeSagemcom = 0x0A,
    AmsTypeCustom = 0x88,
    AmsTypeUnknown = 0xFF
};

class AmsData {
public:
    AmsData();

    void apply(AmsData& other);

    unsigned long getLastUpdateMillis();

    time_t getPackageTimestamp();

    uint8_t getListType();

    String getListId();
    String getMeterId();
    String getMeterHW();  //EHorvat new for Hardware Rev
    String getMeterFW();  //EHorvat new for Firmware Rev
    String getMeterType();  //EHorvat was uint8_t
    String getMeterSerial();  //EHorvat new
    String getMeterModel();

    time_t getMeterTimestamp();

    uint32_t getActiveImportPower();
    uint32_t getReactiveImportPower();
    float getFrequency();              //  EHorvat NESMEP
    uint32_t getActiveExportPower();
    uint32_t getReactiveExportPower();

    uint8_t setfromNESMEP_0(bool Data_ready, long Mep_alivecounter); // EHorvat
    uint8_t setfromNESMEP_1(long ActiveImportPower, 
                            double ActiveImportCounter,
                            long ActiveExportPower, 
                            double ActiveExportCounter, 
                            long ReactiveImportPower,
                            long ReactiveExportPower, 
                            double ReactiveImportCounter, 
                            double ReactiveExportCounter, 
                            float Pwr_Factor_L1, 
                            float Pwr_Factor_L2, 
                            float Pwr_Factor_L3,
                            long Ap_Power,
                            long ReactivePower_Q1,
                            long ReactivePower_Q2,
                            long ReactivePower_Q3,
                            long ReactivePower_Q4,
                            float Freq_mHz, 
                            float L1Voltage, 
                            float L2Voltage, 
                            float L3Voltage, 
                            float L1Current, 
                            float L2Current, 
                            float L3Current); // EHorvat
    uint8_t setfromNESMEP_2(char Manufacturer[5], 
                            char Model[9], 
                            byte MainHardwareVersionNumber, 
                            byte HardwareRevisionNumber, 
                            byte MainFirmwareVersionNumber, 
                            byte FirmwareRevisionNumber, 
                            char UtilitySerialNumber[31]); // EHorvat

    float getL1Voltage();
    float getL2Voltage();
    float getL3Voltage();

    float getL1Current();
    float getL2Current();
    float getL3Current();

    float getPowerFactor();
    float getL1PowerFactor();
    float getL2PowerFactor();
    float getL3PowerFactor();
    uint32_t getAparentPower();        //EHorvat new get VA L1L2L3
    uint32_t getReactivePower_Q1();        //EHorvat new
    uint32_t getReactivePower_Q2();        //EHorvat new
    uint32_t getReactivePower_Q3();        //EHorvat new
    uint32_t getReactivePower_Q4();        //EHorvat new

    float getL1ActiveImportPower();
    float getL2ActiveImportPower();
    float getL3ActiveImportPower();

    float getL1ActiveExportPower();
    float getL2ActiveExportPower();
    float getL3ActiveExportPower();

    double getActiveImportCounter();
    double getReactiveImportCounter();
    double getActiveExportCounter();
    double getReactiveExportCounter();
    double getAliveCounter();               //EHorvat
    bool isData_ready();        //EHorvat
    
    bool isThreePhase();
    bool isTwoPhase();

    int8_t getLastError();
    void setLastError(int8_t);

protected:
    unsigned long lastUpdateMillis = 0;
    unsigned long lastList2 = 0;
    uint8_t listType = 1, meterType; //EHorvat Set List Type to 1 (was 0)
    String meterType_fw = "";
    time_t packageTimestamp = 0;
    String listId = "", meterId = "", meterModel = "";
    time_t meterTimestamp = 0;
    uint32_t activeImportPower = 0, reactiveImportPower = 0, activeExportPower = 0, reactiveExportPower = 0;
    uint32_t AparentPower=0, ReactivePower_Q1 = 0, ReactivePower_Q2 = 0, ReactivePower_Q3 = 0, ReactivePower_Q4 = 0;
    float l1voltage = 0, l2voltage = 0, l3voltage = 0, l1current = 0, l2current = 0, l3current = 0;
    float l1activeImportPower = 0, l2activeImportPower = 0, l3activeImportPower = 0;
    float l1activeExportPower = 0, l2activeExportPower = 0, l3activeExportPower = 0;
    float powerFactor = 0, l1PowerFactor = 0, l2PowerFactor = 0, l3PowerFactor = 0;
    double activeImportCounter = 0, reactiveImportCounter = 0, activeExportCounter = 0, reactiveExportCounter = 0;
    bool threePhase = false, twoPhase = false, counterEstimated = false;

    int8_t lastError = 0x00;
    uint8_t lastErrorCount = 0;
};

#endif
