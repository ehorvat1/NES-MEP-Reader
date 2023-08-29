#ifndef _ENERGYACCOUNTING_H
#define _ENERGYACCOUNTING_H

#include "Arduino.h"
#include "AmsData.h"
#include "AmsDataStorage.h"
#include "EntsoeApi.h"

struct EnergyAccountingPeak {
    uint8_t day;
    uint16_t value;
};

struct EnergyAccountingData {
    uint8_t version;
    uint8_t month;
    uint32_t costYesterday;
    uint32_t costThisMonth;
    uint32_t costLastMonth;
    uint32_t incomeYesterday;
    uint32_t incomeThisMonth;
    uint32_t incomeLastMonth;
    uint32_t lastMonthImport;
    uint32_t lastMonthExport;
    uint8_t lastMonthAccuracy;
    EnergyAccountingPeak peaks[5];
};

struct EnergyAccountingData5 {
    uint8_t version;
    uint8_t month;
    uint16_t costYesterday;
    uint16_t costThisMonth;
    uint16_t costLastMonth;
    uint16_t incomeYesterday;
    uint16_t incomeThisMonth;
    uint16_t incomeLastMonth;
    EnergyAccountingPeak peaks[5];
};

struct EnergyAccountingData4 {
    uint8_t version;
    uint8_t month;
    uint16_t costYesterday;
    uint16_t costThisMonth;
    uint16_t costLastMonth;
    EnergyAccountingPeak peaks[5];
};

struct EnergyAccountingData2 {
    uint8_t version;
    uint8_t month;
    uint16_t maxHour;
    uint16_t costYesterday;
    uint16_t costThisMonth;
    uint16_t costLastMonth;
};


class EnergyAccounting {
public:
    EnergyAccounting(RemoteDebug*);
    void setup(AmsDataStorage *ds, EnergyAccountingConfig *config);
    void setEapi(EntsoeApi *eapi);
    void setTimezone(Timezone*);
    EnergyAccountingConfig* getConfig();
    bool update(AmsData* amsData);
    bool load();
    bool save();
    bool isInitialized();

    float getUseThisHour();
    float getUseToday();
    float getUseThisMonth();
    float getUseLastMonth();

    float getProducedThisHour();
    float getProducedToday();
    float getProducedThisMonth();
    float getProducedLastMonth();

    float getCostThisHour();
    float getCostToday();
    float getCostYesterday();
    float getCostThisMonth();
    float getCostLastMonth();

    float getIncomeThisHour();
    float getIncomeToday();
    float getIncomeYesterday();
    float getIncomeThisMonth();
    float getIncomeLastMonth();

    float getMonthMax();
    uint8_t getCurrentThreshold();
    EnergyAccountingPeak getPeak(uint8_t);

    EnergyAccountingData getData();
    void setData(EnergyAccountingData&);

    void setFixedPrice(float price, String currency);
    float getPriceForHour(uint8_t h);
    void setFixedRefund(float refund, String currency);  //EHorvat new fixed income price / refund
    float getIncomeRefundForHour(uint8_t h);  //EHorvat new fixed income price / refund
//
    void setLast_Counter_Value(uint32_t last_counter_value);  //EHorvat new last_counter_value
    uint32_t getLast_Counter_Value();  //EHorvat new last_counter_value
    void setLast_Counter_Info(String last_counter_info);  //EHorvat new last_counter_value
    String getLast_Counter_Info();    //EHorvat new last_counter_value
    void setCostsLastCounterValue(float costs_last_counter_value);  //EHorvat new last_counter_value
    float getCostsLastCounterValue(); //EHorvat new last_counter_value
    void setLast_Counter_Diff(uint32_t last_counter_diff);  //EHorvat new last_counter_value
    uint32_t getLast_Counter_Diff();  //EHorvat new last_counter_value
//
    void setLast_expCounter_Value(uint32_t last_expcounter_value);  //EHorvat new last_counter_value
    uint32_t getLast_expCounter_Value();  //EHorvat new last_counter_value
    void setLast_expCounter_Info(String last_expcounter_info);  //EHorvat new last_counter_value
    String getLast_expCounter_Info();    //EHorvat new last_counter_value
    void setCostsLastexpCounterValue(float costs_last_expcounter_value);  //EHorvat new last_counter_value
    float getCostsLastexpCounterValue(); //EHorvat new last_counter_value
    void setLast_expCounter_Diff(uint32_t last_expcounter_diff);  //EHorvat new last_counter_value
    uint32_t getLast_expCounter_Diff();  //EHorvat new last_counter_value

private:
	AmsData* meterState;//EHorvat new last_counter_value
    RemoteDebug* debugger = NULL;
    unsigned long lastUpdateMillis = 0;
    bool init = false, initPrice = false;
    AmsDataStorage *ds = NULL;
    EntsoeApi *eapi = NULL;
    EnergyAccountingConfig *config = NULL;
    Timezone *tz = NULL;
    uint8_t currentHour = 0, currentDay = 0, currentThresholdIdx = 0;
    float use = 0, costHour = 0, costDay = 0;
    float produce = 0, incomeHour = 0, incomeDay = 0;
    EnergyAccountingData data = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    float fixedPrice = 0;
    float fixedRefund = 0;  //EHorvat new fixed income price / refund
//
    uint32_t last_counter_value = 0;  //EHorvat new last_counter_value
    String last_counter_info = "";    //EHorvat new last_counter_value
    float costs_last_counter_value = 0.0;//EHorvat new last_counter_value
    uint32_t last_counter_diff = 0;  //EHorvat new last_counter_value
    //
    uint32_t last_expcounter_value = 0;  //EHorvat new last_counter_value
    String last_expcounter_info = "";    //EHorvat new last_counter_value
    float costs_last_expcounter_value = 0.0;//EHorvat new last_counter_value
    uint32_t last_expcounter_diff = 0;  //EHorvat new last_counter_value
//
    String currency = "";
    void calcDayCost();
    bool updateMax(uint16_t val, uint8_t day);
};

#endif
