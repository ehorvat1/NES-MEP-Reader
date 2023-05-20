#include "AmsData.h"

AmsData::AmsData() {}

// EHorvat NES-MEP added next few lines...
bool NESMEP_data_ready;
long NESMEP_ActiveImportPower;
long NESMEP_ReactiveImportPower;
float NESMEP_Freq_Hz;
long NESMEP_ActiveExportPower;
long NESMEP_ReactiveExportPower;
float NESMEP_Pwr_Factor_L1;
float NESMEP_Pwr_Factor_L2;
float NESMEP_Pwr_Factor_L3;
float NESMEP_VA_L1L2L3;
float NESMEP_L1Voltage;
float NESMEP_L2Voltage;
float NESMEP_L3Voltage;
float NESMEP_L1Current;
float NESMEP_L2Current;
float NESMEP_L3Current;
double NESMEP_ActiveImportCounter;
double NESMEP_ReactiveImportCounter;
double NESMEP_ActiveExportCounter;
double NESMEP_ReactiveExportCounter;

long NESMEP_ReactivePower_Q1;
long NESMEP_ReactivePower_Q2;
long NESMEP_ReactivePower_Q3;
long NESMEP_ReactivePower_Q4;

long NESMEP_mep_alivecounter;
char NESMEP_Manufacturer[5];
char NESMEP_Model[9];
char NESMEP_UtilitySerialNumber[31];
char NESMEP_FirmwareRevision[8];
char NESMEP_HardwareRevision[8];

byte NESMEP_MainFirmwareVersionNumber;
byte NESMEP_FirmwareRevisionNumber;
byte NESMEP_MainHardwareVersionNumber;
byte NESMEP_HardwareRevisionNumber;
String FW_full = "";
String HW_full = "";

// EHorvat NES-MEP end

void AmsData::apply(AmsData& other) {
    if(other.getListType() < 3) {
        unsigned long ms = this->lastUpdateMillis > other.getLastUpdateMillis() ? 0 : other.getLastUpdateMillis() - this->lastUpdateMillis;

        if(ms > 0) {
            if(other.getActiveImportPower() > 0) {
                float add = other.getActiveImportPower() * (((float) ms) / 3600000.0);
                activeImportCounter += add / 1000.0;
                //Serial.printf("%dW, %dms, %.6fkWh added\n", other.getActiveImportPower(), ms, add);
            }

            if(other.getListType() > 1) {
                ms = this->lastUpdateMillis > other.getLastUpdateMillis() ? 0 : other.getLastUpdateMillis() - this->lastList2;
                if(other.getActiveExportPower() > 0) {
                    float add = other.getActiveExportPower() * (((float) ms) / 3600000.0);
                    activeExportCounter += add / 1000.0;
                }
                if(other.getReactiveImportPower() > 0) {
                    float add = other.getReactiveImportPower() * (((float) ms) / 3600000.0);
                    reactiveImportCounter += add / 1000.0;
                }
                if(other.getReactiveExportPower() > 0) {
                    float add = other.getReactiveExportPower() * (((float) ms) / 3600000.0);
                    reactiveExportCounter += add / 1000.0;
                }
            }
            counterEstimated = true;
        }
    }

    //  this->lastUpdateMillis = other.getLastUpdateMillis();        //EHorvat NES-MEP
    this->lastUpdateMillis = millis() - 10000;                      //Ehorvat make HAN port look green and offset ms by 10 sec
    this->listType = 4;                                             //EHorvat NES-MEP added
   
    if(other.getListType() > 1) {
        this->lastList2 = this->lastUpdateMillis;
    }
//      this->packageTimestamp = other.getPackageTimestamp(); 
        this->packageTimestamp = time(nullptr) - 10;                   //EHorvat NES-MEP
        if(other.getListType() > this->listType)
        //   this->listType = other.getListType();           //EHorvat NES-MEP removed case
            this->listType = 4;                                         //EHorvat NES-MEP added
//
//    switch(other.getListType()) {                           //EHorvat NES-MEP removed case
//        case 4:
//            this->powerFactor = other.getPowerFactor();
            this->l1PowerFactor = NESMEP_Pwr_Factor_L1;
            this->l2PowerFactor = NESMEP_Pwr_Factor_L2;
            this->l3PowerFactor = NESMEP_Pwr_Factor_L3;
            this->AparentPower = NESMEP_VA_L1L2L3;
            this->ReactivePower_Q1 = NESMEP_ReactivePower_Q1;
            this->ReactivePower_Q2 = NESMEP_ReactivePower_Q2;
            this->ReactivePower_Q3 = NESMEP_ReactivePower_Q3;
            this->ReactivePower_Q4 = NESMEP_ReactivePower_Q4;
//            this->l1activeImportPower = other.getL1ActiveImportPower();
//            this->l2activeImportPower = other.getL2ActiveImportPower();
//            this->l3activeImportPower = other.getL3ActiveImportPower();
//            this->l1activeExportPower = other.getL1ActiveExportPower();
//            this->l2activeExportPower = other.getL2ActiveExportPower();
//            this->l3activeExportPower = other.getL3ActiveExportPower();
//        case 3:
            this->meterTimestamp = other.getMeterTimestamp();
            this->meterTimestamp = time(nullptr) - 1;                       // EHorvat NES-MEP
            this->activeImportPower = NESMEP_ActiveImportPower;  //EHorvat NES-MEP
            this->activeImportCounter = NESMEP_ActiveImportCounter;         //EHorvat NES-MEP
            this->activeExportCounter = NESMEP_ActiveExportCounter;         //EHorvat NES-MEP
            this->activeExportPower = NESMEP_ActiveExportPower;             //EHorvat NES-MEP            this->reactiveImportCounter = NESMEP_ReactiveImportCounter;     //EHorvat NES-MEP .... this is now NESMEP_data_ready (0/1)
            this->reactiveImportPower = NESMEP_ReactiveImportPower;         //EHorvat NES-MEP
            this->reactiveExportPower = NESMEP_ReactiveExportPower;          //EHorvat NES-MEP
            this->reactiveExportCounter = NESMEP_ReactiveExportCounter;
//            this->activeImportCounter = other.getActiveImportCounter();
//            this->activeExportCounter = other.getActiveExportCounter();
            this->counterEstimated = false;
//        case 2:
            this->listId = other.getListId();
            this->meterId = other.getMeterId();
//            this->meterType = other.getMeterType();//EHorvat NES-MEP
//            this->meterType_fw = String(NESMEP_MainFirmwareVersionNumber) + "_" + String(NESMEP_FirmwareRevisionNumber);
            this->meterType_fw = FW_full;//EHorvat NES-MEP
            this->meterModel = other.getMeterModel();
//            this->reactiveImportPower = other.getReactiveImportPower();
//            this->reactiveExportPower = other.getReactiveExportPower();

//            this->l1current = other.getL1Current();
//            this->l2current = other.getL2Current();
//            this->l3current = other.getL3Current();
//            this->l1voltage = other.getL1Voltage();
//            this->l2voltage = other.getL2Voltage();
//            this->l3voltage = other.getL3Voltage();
            this->l1current = NESMEP_L1Current;  //EHorvat NES-MEP
            this->l2current = NESMEP_L2Current;  //EHorvat NES-MEP
            this->l3current = NESMEP_L3Current;  //EHorvat NES-MEP
            this->l1voltage = NESMEP_L1Voltage;  //EHorvat NES-MEP
            this->l2voltage = NESMEP_L2Voltage;  //EHorvat NES-MEP
            this->l3voltage = NESMEP_L3Voltage;  //EHorvat NES-MEP
            this->threePhase = other.isThreePhase();
            this->twoPhase = other.isTwoPhase();
//    }   //EHorvat NES-MEP removed case

    // Moved outside switch to handle meters alternating between sending active and accumulated values
    // EHorvat NES-MEP Disabled next 4 lines 
//    if(other.getListType() == 1 || (other.getActiveImportPower() > 0 || other.getActiveExportPower() > 0))
//        this->activeImportPower = other.getActiveImportPower();
//    if(other.getListType() == 2 || (other.getActiveImportPower() > 0 || other.getActiveExportPower() > 0))
//        this->activeExportPower = other.getActiveExportPower();
}

// ************ EHorvat NES-MEP  ****************
uint8_t AmsData::setfromNESMEP_0(bool Data_ready, long Mep_alivecounter) {
    NESMEP_data_ready = Data_ready;
    NESMEP_mep_alivecounter = Mep_alivecounter;                 // Send mep_alivecounter instead of ReactiveExportCounter....
return 1;
}

uint8_t AmsData::setfromNESMEP_1(long ActiveImportPower,
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
                                long VA_L1L2L3,
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
                                float L3Current) {
//
    NESMEP_ActiveImportPower = ActiveImportPower;
    NESMEP_ActiveImportCounter = ActiveImportCounter;     
    NESMEP_ActiveExportPower = ActiveExportPower; 
    NESMEP_ActiveExportCounter = ActiveExportCounter;  
    NESMEP_ReactiveImportPower = ReactiveImportPower;
    NESMEP_ReactiveExportPower = ReactiveExportPower;
    NESMEP_ReactiveImportCounter = ReactiveImportCounter;
    NESMEP_ReactiveExportCounter = ReactiveExportCounter;
    NESMEP_Pwr_Factor_L1 = Pwr_Factor_L1,
    NESMEP_Freq_Hz = Freq_mHz;
    NESMEP_Pwr_Factor_L2 = Pwr_Factor_L2,
    NESMEP_Pwr_Factor_L3 = Pwr_Factor_L3,
    NESMEP_L1Voltage = L1Voltage;
    NESMEP_L2Voltage = L2Voltage;
    NESMEP_L3Voltage = L3Voltage;
    NESMEP_L1Current = L1Current;
    NESMEP_L2Current = L2Current;
    NESMEP_L3Current = L3Current;
    NESMEP_VA_L1L2L3 = VA_L1L2L3;
    NESMEP_ReactivePower_Q1 = ReactivePower_Q1;
    NESMEP_ReactivePower_Q2 = ReactivePower_Q2;
    NESMEP_ReactivePower_Q3 = ReactivePower_Q3;
    NESMEP_ReactivePower_Q4 = ReactivePower_Q4;
return 1;
}

uint8_t AmsData::setfromNESMEP_2(char Manufacturer[5], char Model[9], byte MainHardwareVersionNumber, byte HardwareRevisionNumber, byte MainFirmwareVersionNumber, byte FirmwareRevisionNumber, char UtilitySerialNumber[31]) {
    memcpy(NESMEP_Manufacturer,Manufacturer,5);
    memcpy(NESMEP_Model,Model,9);
    memcpy(NESMEP_UtilitySerialNumber,UtilitySerialNumber,31);
    NESMEP_MainHardwareVersionNumber = MainHardwareVersionNumber;
    NESMEP_HardwareRevisionNumber= HardwareRevisionNumber;
    NESMEP_MainFirmwareVersionNumber = MainFirmwareVersionNumber;
    NESMEP_FirmwareRevisionNumber= FirmwareRevisionNumber;
return 1;
}

// ************ EHorvat NES-MEP end   ****************

unsigned long AmsData::getLastUpdateMillis() {
//    return this->lastUpdateMillis;    // EHorvat NES-MEP
    return (NESMEP_data_ready ? (millis() - 1000) : (millis() - 60000) );     // EHorvat NES-MEP fake last Update millis to 1 minuta ago if MEP not ready... so MEP indicator will turn red
}

time_t AmsData::getPackageTimestamp() {
//    return this->packageTimestamp;     // EHorvat NES-MEP
      return time(nullptr) - 1;         // EHorvat NES-MEP
}

uint8_t AmsData::getListType() {
//    return this->listType;
        return 4;  //EHorvat was 3
}

String AmsData::getListId() {
    return this->listId;
}

String AmsData::getMeterId() {
    return NESMEP_Manufacturer;// EHorvat NES-MEP
}

String AmsData::getMeterType() {  //EHorvat was uint8_t
    String FW_part1 = "";
    String FW_part2 = "";
    FW_part1 = String(NESMEP_MainFirmwareVersionNumber);
    FW_part2 = String(NESMEP_FirmwareRevisionNumber);
    FW_full = FW_part1 + "_" + FW_part2;
//    FW_full = "";
    return FW_full;// EHorvat NES-MEP
//    return this->meterType;// EHorvat NES-MEP
}

String AmsData::getMeterSerial() {  //EHorvat was uint8_t
    return NESMEP_UtilitySerialNumber;// EHorvat NES-MEP
}
String AmsData::getMeterHW() {  //EHorvat new for Hardware Rev
    uint8_t HW_part1 = 0;
    uint8_t HW_part2 = 0;
    uint8_t HW_part3 = 0;
    uint16_t HW_sum = 0;
    HW_sum = NESMEP_MainHardwareVersionNumber * 256 + NESMEP_HardwareRevisionNumber;
    HW_part1 = HW_sum & 31;                         //mask out bits 0..4
    HW_sum = (HW_sum - HW_part1) / 32;              // shift out bits 0..4
    HW_part2 = HW_sum & 127;                        //mask out bits 5..11
    HW_part3 = (HW_sum - HW_part2) / 128;           // shift out bits 5..11
    HW_full = String(HW_part3) + "." + String(HW_part2) + "." + String(HW_part1);
    return HW_full;// EHorvat NES-MEP
}
String AmsData::getMeterFW() {  //EHorvat new for Firmware Rev
    uint8_t FW_part1 = 0;
    uint8_t FW_part2 = 0;
    uint8_t FW_part3 = 0;
    uint16_t FW_sum = 0;
    FW_sum = NESMEP_MainFirmwareVersionNumber * 256 + NESMEP_FirmwareRevisionNumber;
    FW_part1 = FW_sum & 31;                         //mask out bits 0..4
    FW_sum = (FW_sum - FW_part1) / 32;              // shift out bits 0..4
    FW_part2 = FW_sum & 127;                        //mask out bits 5..11
    FW_part3 = (FW_sum - FW_part2) / 128;           // shift out bits 5..11
    FW_full = String(FW_part3) + "." + String(FW_part2) + "." + String(FW_part1);
//    FW_full = "";
    return FW_full;// EHorvat NES-MEP
}

String AmsData::getMeterModel() {
//    return this->meterModel;    // EHorvat NES-MEP
    return NESMEP_Model;                 // EHorvat NES-MEP}
}

time_t AmsData::getMeterTimestamp() {
//    return this->meterTimestamp;          // EHorvat NES-MEP
    return time(nullptr) - 1;              // EHorvat NES-MEP
}

uint32_t AmsData::getActiveImportPower() {
//    return this->activeImportPower;                  // EHorvat NES-MEP
    return NESMEP_ActiveImportPower;                   // EHorvat NES-MEP
}

uint32_t AmsData::getReactiveImportPower() {
//    return this->reactiveImportPower;              // EHorvat NES-MEP
    return NESMEP_ReactiveImportPower;               // EHorvat NES-MEP
}

uint32_t AmsData::getActiveExportPower() {
//   return this->activeExportPower;        // EHorvat NES-MEP
    return NESMEP_ActiveExportPower;        // EHorvat NES-MEP
}

uint32_t AmsData::getReactiveExportPower() {
//    return this->reactiveExportPower;        // EHorvat NES-MEP
    return NESMEP_ReactiveExportPower;         // EHorvat NES-MEP
}

float AmsData::getFrequency() {
//    return this->l1voltage;     // EHorvat NES-MEP
    return NESMEP_Freq_Hz;      // EHorvat NES-MEP
}

float AmsData::getL1Voltage() {
//    return this->l1voltage;     // EHorvat NES-MEP
    return NESMEP_L1Voltage;      // EHorvat NES-MEP
}

float AmsData::getL2Voltage() {
//    return this->l2voltage;     // EHorvat NES-MEP
    return NESMEP_L2Voltage;      // EHorvat NES-MEP
}

float AmsData::getL3Voltage() {
//    return this->l3voltage;     // EHorvat NES-MEP
    return NESMEP_L3Voltage;      // EHorvat NES-MEP
}    

float AmsData::getL1Current() {
//    return this->l1current;     // EHorvat NES-MEP
    return NESMEP_L1Current;      // EHorvat NES-MEP
}

float AmsData::getL2Current() {
//    return this->l2current;     // EHorvat NES-MEP
    return NESMEP_L2Current;      // EHorvat NES-MEP
}

float AmsData::getL3Current() {
//    return this->l3current;     // EHorvat NES-MEP
    return NESMEP_L3Current;      // EHorvat NES-MEP
}
float AmsData::getPowerFactor() {
    return this->powerFactor;
}

float AmsData::getL1PowerFactor() {
    return NESMEP_Pwr_Factor_L1;
}

float AmsData::getL2PowerFactor() {
    return NESMEP_Pwr_Factor_L2;
}

float AmsData::getL3PowerFactor() {
    return NESMEP_Pwr_Factor_L3;
}
uint32_t AmsData::getAparentPower() {
    return NESMEP_VA_L1L2L3;        // EHorvat NES-MEP
}

uint32_t AmsData::getReactivePower_Q1() {
    return NESMEP_ReactivePower_Q1;        // EHorvat NES-MEP
}
uint32_t AmsData::getReactivePower_Q2() {
    return NESMEP_ReactivePower_Q2;        // EHorvat NES-MEP
}
uint32_t AmsData::getReactivePower_Q3() {
    return NESMEP_ReactivePower_Q3;        // EHorvat NES-MEP
}
uint32_t AmsData::getReactivePower_Q4() {
    return NESMEP_ReactivePower_Q4;        // EHorvat NES-MEP
}

float AmsData::getL1ActiveImportPower() {
    return this->l1activeImportPower;
}

float AmsData::getL2ActiveImportPower() {
    return this->l2activeImportPower;
}

float AmsData::getL3ActiveImportPower() {
    return this->l3activeImportPower;
}

float AmsData::getL1ActiveExportPower() {
    return this->l1activeExportPower;
}

float AmsData::getL2ActiveExportPower() {
    return this->l2activeExportPower;
}

float AmsData::getL3ActiveExportPower() {
    return this->l3activeExportPower;
}

double AmsData::getActiveImportCounter() {
//    return this->activeImportCounter;
    return NESMEP_ActiveImportCounter;                  // EHorvat NES-MEP
}

double AmsData::getReactiveImportCounter() {
    return NESMEP_ReactiveImportCounter;           
}

double AmsData::getActiveExportCounter() {
   return NESMEP_ActiveExportCounter;                  // EHorvat NES-MEP
}

double AmsData::getReactiveExportCounter() {
//    return this->reactiveExportCounter;
    return NESMEP_ReactiveExportCounter;             // Send mep_alivecounter instead of ReactiveExportCounter....
}

double AmsData::getAliveCounter() {
//    return this->reactiveExportCounter;
    return NESMEP_mep_alivecounter;             // Send mep_alivecounter instead of ReactiveExportCounter....
}

bool AmsData::isData_ready() {
    return NESMEP_data_ready;           // EHorvat NES-MEP
}

bool AmsData::isThreePhase() {
//    return this->threePhase;           // EHorvat NES-MEP
    return true;                         // EHorvat NES-MEP
}

bool AmsData::isTwoPhase() {
//    return this->twoPhase;
    return false;                         // EHorvat NES-MEP
}

int8_t AmsData::getLastError() {
    return lastErrorCount > 2 ? lastError : 0;
}

void AmsData::setLastError(int8_t lastError) {
    this->lastError = lastError;
    if(lastError == 0) {
        lastErrorCount = 0;
    } else {
        lastErrorCount++;
    }
}