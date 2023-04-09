#include "AmsData.h"

AmsData::AmsData() {}

// EHorvat NES-MEP added...
bool NESMEP_data_ready;
uint16_t NESMEP_ActiveImportPower;
uint16_t NESMEP_ReactiveImportPower;
float NESMEP_Freq_Hz;
uint16_t NESMEP_ActiveExportPower;
uint16_t NESMEP_ReactiveExportPower;
float NESMEP_L1Voltage;
float NESMEP_L2Voltage;
float NESMEP_L3Voltage;
float NESMEP_L1Current;
float NESMEP_L2Current;
float NESMEP_L3Current;
double NESMEP_ActiveImportCounter;
double NESMEP_ReactiveImportCounter;    //.... this is now NESMEP_data_ready (0/1)
double NESMEP_ActiveExportCounter;
double NESMEP_ReactiveExportCounter;
double NESMEP_mep_alivecounter;
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
//          this->listType = other.getListType();                       //EHorvat NES-MEP removed case
            this->listType = 4;                                         //EHorvat NES-MEP added
//                                                                      EHorvat NES-MEP  .... Next lines disabled... no switch case...
//    switch(other.getListType()) {
//        case 4:
//            this->powerFactor = other.getPowerFactor();
//            this->l1PowerFactor = other.getL1PowerFactor();
//            this->l2PowerFactor = other.getL2PowerFactor();
//            this->l3PowerFactor = other.getL3PowerFactor();
//            this->l1activeImportPower = other.getL1ActiveImportPower();
//            this->l2activeImportPower = other.getL2ActiveImportPower();
//            this->l3activeImportPower = other.getL3ActiveImportPower();
//            this->l1activeExportPower = other.getL1ActiveExportPower();
//            this->l2activeExportPower = other.getL2ActiveExportPower();
//            this->l3activeExportPower = other.getL3ActiveExportPower();
//        case 3:
            this->meterTimestamp = other.getMeterTimestamp();
            this->meterTimestamp = time(nullptr) - 1;                       // EHorvat NES-MEP
            this->activeImportCounter = NESMEP_ActiveImportCounter;         //EHorvat NES-MEP
            this->activeExportCounter = NESMEP_ActiveExportCounter;         //EHorvat NES-MEP
            this->reactiveImportCounter = NESMEP_ReactiveImportCounter;     //EHorvat NES-MEP .... this is now NESMEP_data_ready (0/1)
            this->reactiveExportCounter = NESMEP_mep_alivecounter;          // Send mep_alivecounter instead of ReactiveExportCounter....
//            this->activeImportCounter = other.getActiveImportCounter();
//            this->activeExportCounter = other.getActiveExportCounter();
//            this->reactiveImportCounter = other.getReactiveImportCounter();
//            this->reactiveExportCounter = other.getReactiveExportCounter();
            this->counterEstimated = false;
//        case 2:
            this->listId = other.getListId();
            this->meterId = other.getMeterId();
            this->meterType = other.getMeterType();
            this->meterModel = other.getMeterModel();
//            this->reactiveImportPower = other.getReactiveImportPower();
//            this->reactiveExportPower = other.getReactiveExportPower();
            this->reactiveImportPower = NESMEP_ReactiveImportPower;  //EHorvat NES-MEP
            this->activeExportPower = NESMEP_ActiveExportPower;  //EHorvat NES-MEP
            this->reactiveExportPower = NESMEP_ReactiveExportPower;  //EHorvat NES-MEP
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
        this->activeImportPower = other.getActiveImportPower();  //EHorvat NES-MEP
}

// ************ EHorvat NES-MEP  ****************
float AmsData::setfromNESMEP(bool Data_ready, uint16_t ActiveImportPower, long Freq_mHz, uint16_t ActiveExportPower, uint16_t ReactiveExportPower, float L1Voltage, float L2Voltage, float L3Voltage, float L1Current, float L2Current, float L3Current, double ActiveImportCounter,double ReactiveImportCounter, double ActiveExportCounter, double Mep_alivecounter) {
    NESMEP_data_ready = Data_ready;
    NESMEP_ActiveImportPower = ActiveImportPower;
//    NESMEP_ReactiveImportPower = ReactiveImportPower;
    NESMEP_Freq_Hz = float(Freq_mHz) / 1000.0;
    NESMEP_ActiveExportPower = ActiveExportPower;
    NESMEP_ReactiveExportPower = Freq_mHz;
    NESMEP_L1Voltage = L1Voltage;
    NESMEP_L2Voltage = L2Voltage;
    NESMEP_L3Voltage = L3Voltage;
    NESMEP_L1Current = L1Current;
    NESMEP_L2Current = L2Current;
    NESMEP_L3Current = L3Current;
    NESMEP_ActiveImportCounter = ActiveImportCounter;        
//    NESMEP_ReactiveImportCounter = ReactiveImportCounter;     // Send NESMEP_data_ready instead of ReactiveImportCounter....
    NESMEP_ReactiveImportCounter = NESMEP_data_ready ? 1 : 0;   // Send NESMEP_data_ready instead of ReactiveImportCounter....
    NESMEP_ActiveExportCounter = ActiveExportCounter;
//    NESMEP_ReactiveExportCounter = ReactiveExportCounter;     // Send mep_alivecounter instead of ReactiveExportCounter....
    NESMEP_mep_alivecounter = Mep_alivecounter;                 // Send mep_alivecounter instead of ReactiveExportCounter....
return 123.4;
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
    return this->meterId;
}

uint8_t AmsData::getMeterType() {
    return this->meterType;
}

String AmsData::getMeterModel() {
//    return this->meterModel;    // EHorvat NES-MEP
    return "NES";                 // EHorvat NES-MEP}
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
    return this->l1PowerFactor;
}

float AmsData::getL2PowerFactor() {
    return this->l2PowerFactor;
}

float AmsData::getL3PowerFactor() {
    return this->l3PowerFactor;
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
//    return this->reactiveImportCounter;           // EHorvat NES-MEP
    return NESMEP_ReactiveImportCounter;            // This is mep_data_ready now (0/1)
}

double AmsData::getActiveExportCounter() {
//   return this->activeExportCounter;                 // EHorvat NES-MEP
   return NESMEP_ActiveExportCounter;                  // EHorvat NES-MEP
}

double AmsData::getReactiveExportCounter() {
//    return this->reactiveExportCounter;
    return NESMEP_mep_alivecounter;             // Send mep_alivecounter instead of ReactiveExportCounter....
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
    return lastErrorCount > 3 ? lastError : 0;
}

void AmsData::setLastError(int8_t lastError) {
    this->lastError = lastError;
    if(lastError == 0) {
        lastErrorCount = 0;
    } else {
        lastErrorCount++;
    }
}