#include "RawMqttHandler.h"
#include "hexutils.h"
#include "Uptime.h"

bool RawMqttHandler::publish(AmsData* data, AmsData* meterState, EnergyAccounting* ea, EntsoeApi* eapi) {
	if(topic.isEmpty() || !mqtt->connected())
		return false;

    mqtt10secCount++;
    if (mqtt10secCount > 4) {
        mqtt10sec = 1;
        mqtt10secCount = 0;
    } else {
        mqtt10sec = 0;
    }        
    if(data->getPackageTimestamp() > 0) {
        mqtt->publish(topic + "/meter/dlms/timestamp", String(data->getPackageTimestamp()));
    }
    switch(data->getListType()) {
        case 4:
            publishList4(data, meterState);
            loop();
        case 3:
            publishList3(data, meterState);
            loop();
        case 2:
            publishList2(data, meterState);
            loop();
        case 1:
            publishList1(data, meterState);
            loop();
    }
    if(ea->isInitialized()) {
        publishRealtime(ea);
        loop();
    }
    return true;
}

bool RawMqttHandler::publishList1(AmsData* data, AmsData* meterState) {
// full = 2 second rate
// 
    if(full || mqtt10sec) {
        mqtt->publish(topic + "/uptime", String((unsigned long) millis64()/1000));  //EHorvat 
        mqtt->publish(topic + "/meter/import/active", String(data->getActiveImportPower()));
    }
    return true;
}

bool RawMqttHandler::publishList2(AmsData* data, AmsData* meterState) {
    if(full || mqtt10sec) {
        mqtt->publish(topic + "/meter/id", data->getMeterId());
        mqtt->publish(topic + "/meter/type", data->getMeterModel());
        mqtt->publish(topic + "/meter/l1/current", String(data->getL1Current(), 2));
        mqtt->publish(topic + "/meter/l1/voltage", String(data->getL1Voltage(), 2));
        mqtt->publish(topic + "/meter/l2/current", String(data->getL2Current(), 2));
        mqtt->publish(topic + "/meter/l2/voltage", String(data->getL2Voltage(), 2));
        mqtt->publish(topic + "/meter/l3/current", String(data->getL3Current(), 2));
        mqtt->publish(topic + "/meter/l3/voltage", String(data->getL3Voltage(), 2));
        mqtt->publish(topic + "/meter/export/reactive", String(data->getReactiveExportPower()));
        mqtt->publish(topic + "/meter/export/active", String(data->getActiveExportPower()));
        mqtt->publish(topic + "/meter/import/reactive", String(data->getReactiveImportPower()));
    }
    return true;
}

bool RawMqttHandler::publishList3(AmsData* data, AmsData* meterState) {
    // 
    if(full || mqtt10sec) {
//       mqtt->publish(topic + "/meter/id", data->getMeterId(), true, 0);
//        mqtt->publish(topic + "/meter/type", data->getMeterModel(), true, 0);
        mqtt->publish(topic + "/meter/clock", String(data->getMeterTimestamp()));
        mqtt->publish(topic + "/meter/import/reactive/accumulated", String(data->getReactiveImportCounter(), 3), true, 0);
        mqtt->publish(topic + "/meter/import/active/accumulated", String(data->getActiveImportCounter(), 3), true, 0);
        mqtt->publish(topic + "/meter/export/reactive/accumulated", String(data->getReactiveExportCounter(), 3), true, 0);
        mqtt->publish(topic + "/meter/export/active/accumulated", String(data->getActiveExportCounter(), 3), true, 0);
    }
    return true;
}

bool RawMqttHandler::publishList4(AmsData* data, AmsData* meterState) {
    if(full || mqtt10sec) {
            mqtt->publish(topic + "/meter/import/l1", String(data->getL1ActiveImportPower(), 2));
            mqtt->publish(topic + "/meter/import/l2", String(data->getL2ActiveImportPower(), 2));
            mqtt->publish(topic + "/meter/import/l3", String(data->getL3ActiveImportPower(), 2));
            mqtt->publish(topic + "/meter/export/l1", String(data->getL1ActiveExportPower(), 2));
            mqtt->publish(topic + "/meter/export/l2", String(data->getL2ActiveExportPower(), 2));
            mqtt->publish(topic + "/meter/export/l3", String(data->getL3ActiveExportPower(), 2));
            mqtt->publish(topic + "/meter/power/frequency", String(data->getFrequency(), 2));
            mqtt->publish(topic + "/meter/l1/powerfactor", String(data->getL1PowerFactor(), 2));
            mqtt->publish(topic + "/meter/l2/powerfactor", String(data->getL2PowerFactor(), 2));
            mqtt->publish(topic + "/meter/l3/powerfactor", String(data->getL3PowerFactor(), 2));
            mqtt->publish(topic + "/meter/power/aparentpower", String(data->getAparentPower()));
            mqtt->publish(topic + "/meter/power/reactivepower_Q1", String(data->getReactivePower_Q1()));
            mqtt->publish(topic + "/meter/power/reactivepower_Q2", String(data->getReactivePower_Q2()));
            mqtt->publish(topic + "/meter/power/reactivepower_Q3", String(data->getReactivePower_Q3()));
            mqtt->publish(topic + "/meter/power/reactivepower_Q4", String(data->getReactivePower_Q4()));
        }
        return true;
}

bool RawMqttHandler::publishRealtime(EnergyAccounting* ea) {
    if(full || mqtt10sec) {
        mqtt->publish(topic + "/realtime/import/hour", String(ea->getUseThisHour(), 3));
        mqtt->publish(topic + "/realtime/import/day", String(ea->getUseToday(), 2));
        mqtt->publish(topic + "/realtime/import/month", String(ea->getUseThisMonth(), 1));
        uint8_t peakCount = ea->getConfig()->hours;
        if(peakCount > 5) peakCount = 5;
        for(uint8_t i = 1; i <= peakCount; i++) {
            mqtt->publish(topic + "/realtime/import/peak/" + String(i, 10), String(ea->getPeak(i).value / 100.0, 10), true, 0);
        }
        mqtt->publish(topic + "/realtime/import/threshold", String(ea->getCurrentThreshold(), 10), true, 0);
        mqtt->publish(topic + "/realtime/import/monthmax", String(ea->getMonthMax(), 3), true, 0);
        mqtt->publish(topic + "/realtime/export/hour", String(ea->getProducedThisHour(), 3));
        mqtt->publish(topic + "/realtime/export/day", String(ea->getProducedToday(), 2));
        mqtt->publish(topic + "/realtime/export/month", String(ea->getProducedThisMonth(), 1));
            // EHorvat new for last_counter_value
    mqtt->publish(topic + "/realtime/import/cost_kwh", String(ea->getPriceForHour(0)));
    mqtt->publish(topic + "/realtime/import/last_counter_value", String(ea->getLast_Counter_Value()));
    mqtt->publish(topic + "/realtime/import/last_counter_info", String(ea->getLast_Counter_Info()));
    mqtt->publish(topic + "/realtime/import/last_counter_diff", String(ea->getLast_Counter_Diff()));
    mqtt->publish(topic + "/realtime/import/last_counter_costs", String(ea->getCostsLastCounterValue()));
    //
    mqtt->publish(topic + "/realtime/export/refund_kwh", String(ea->getIncomeRefundForHour(0)));
    mqtt->publish(topic + "/realtime/export/last_counter_value", String(ea->getLast_expCounter_Value()));
    mqtt->publish(topic + "/realtime/export/last_counter_info", String(ea->getLast_expCounter_Info()));
    mqtt->publish(topic + "/realtime/export/last_counter_diff", String(ea->getLast_expCounter_Diff()));
    mqtt->publish(topic + "/realtime/export/last_counter_refund", String(ea->getCostsLastexpCounterValue()));
    }
    return true;
}
/*
bool RawMqttHandler::publishTemperatures(AmsConfiguration* config, HwTools* hw) {
    uint8_t c = hw->getTempSensorCount();
    if(full || mqtt10sec) {
        for(int i = 0; i < c; i++) {
            TempSensorData* data = hw->getTempSensorData(i);
            if(data != NULL && data->lastValidRead > -85) {
                if(data->changed || full) {
                    mqtt->publish(topic + "/temperature/" + toHex(data->address), String(data->lastValidRead, 2));
                    data->changed = false;
                }
            }
        }
    }
    return c > 0;
}
*/
bool RawMqttHandler::publishPrices(EntsoeApi* eapi) {
	if(topic.isEmpty() || !mqtt->connected())
		return false;
	if(eapi->getValueForHour(0) == ENTSOE_NO_VALUE)
		return false;

	time_t now = time(nullptr);

	float min1hr = 0.0, min3hr = 0.0, min6hr = 0.0;
	int8_t min1hrIdx = -1, min3hrIdx = -1, min6hrIdx = -1;
	float min = INT16_MAX, max = INT16_MIN;
	float values[34];
    for(int i = 0;i < 34; i++) values[i] = ENTSOE_NO_VALUE;
	for(uint8_t i = 0; i < 34; i++) {
		float val = eapi->getValueForHour(now, i);
		values[i] = val;

        if(i > 23) continue;
		if(val == ENTSOE_NO_VALUE) break;
		
		if(val < min) min = val;
		if(val > max) max = val;

		if(min1hrIdx == -1 || min1hr > val) {
			min1hr = val;
			min1hrIdx = i;
		}

		if(i >= 2) {
			i -= 2;
			float val1 = values[i++];
			float val2 = values[i++];
			float val3 = val;
			if(val1 == ENTSOE_NO_VALUE || val2 == ENTSOE_NO_VALUE || val3 == ENTSOE_NO_VALUE) continue;
			float val3hr = val1+val2+val3;
			if(min3hrIdx == -1 || min3hr > val3hr) {
				min3hr = val3hr;
				min3hrIdx = i-2;
			}
		}

		if(i >= 5) {
			i -= 5;
			float val1 = values[i++];
			float val2 = values[i++];
			float val3 = values[i++];
			float val4 = values[i++];
			float val5 = values[i++];
			float val6 = val;
			if(val1 == ENTSOE_NO_VALUE || val2 == ENTSOE_NO_VALUE || val3 == ENTSOE_NO_VALUE || val4 == ENTSOE_NO_VALUE || val5 == ENTSOE_NO_VALUE || val6 == ENTSOE_NO_VALUE) continue;
			float val6hr = val1+val2+val3+val4+val5+val6;
			if(min6hrIdx == -1 || min6hr > val6hr) {
				min6hr = val6hr;
				min6hrIdx = i-5;
			}
		}

	}

	char ts1hr[24];
	if(min1hrIdx > -1) {
        time_t ts = now + (SECS_PER_HOUR * min1hrIdx);
		tmElements_t tm;
        breakTime(ts, tm);
		sprintf(ts1hr, "%04d-%02d-%02dT%02d:00:00Z", tm.Year+1970, tm.Month, tm.Day, tm.Hour);
	}
	char ts3hr[24];
	if(min3hrIdx > -1) {
        time_t ts = now + (SECS_PER_HOUR * min3hrIdx);
		tmElements_t tm;
        breakTime(ts, tm);
		sprintf(ts3hr, "%04d-%02d-%02dT%02d:00:00Z", tm.Year+1970, tm.Month, tm.Day, tm.Hour);
	}
	char ts6hr[24];
	if(min6hrIdx > -1) {
        time_t ts = now + (SECS_PER_HOUR * min6hrIdx);
		tmElements_t tm;
        breakTime(ts, tm);
		sprintf(ts6hr, "%04d-%02d-%02dT%02d:00:00Z", tm.Year+1970, tm.Month, tm.Day, tm.Hour);
	}
    if(full || mqtt10sec) {
        for(int i = 0; i < 34; i++) {
            float val = values[i];
            if(val == ENTSOE_NO_VALUE) {
                mqtt->publish(topic + "/price/" + String(i), "", true, 0);
            } else {
                mqtt->publish(topic + "/price/" + String(i), String(val, 4), true, 0);
            }
            mqtt->loop();
            delay(10);
        }
        if(min != INT16_MAX) {
            mqtt->publish(topic + "/price/min", String(min, 4), true, 0);
        }
        if(max != INT16_MIN) {
            mqtt->publish(topic + "/price/max", String(max, 4), true, 0);
        }

        if(min1hrIdx != -1) {
            mqtt->publish(topic + "/price/cheapest/1hr", String(ts1hr), true, 0);
        }
        if(min3hrIdx != -1) {
            mqtt->publish(topic + "/price/cheapest/3hr", String(ts3hr), true, 0);
        }
        if(min6hrIdx != -1) {
            mqtt->publish(topic + "/price/cheapest/6hr", String(ts6hr), true, 0);
        }
    }
    return true;
}

bool RawMqttHandler::publishSystem(HwTools* hw, EntsoeApi* eapi, EnergyAccounting* ea) {
	if(topic.isEmpty() || !mqtt->connected())
		return false;

	mqtt->publish(topic + "/id", WiFi.macAddress(), true, 0);
//	mqtt->publish(topic + "/uptime", String((unsigned long) millis64()/1000)); //EHorvat moved this line to publishList1
	float vcc = hw->getVcc();
	if(vcc > 0) {
		mqtt->publish(topic + "/vcc", String(vcc, 2));
	}
	mqtt->publish(topic + "/mem", String(ESP.getFreeHeap()));
	mqtt->publish(topic + "/rssi", String(hw->getWifiRssi()));
//    if(hw->getTemperature() > -85) {
//		mqtt->publish(topic + "/temperature", String(hw->getTemperature(), 2));
//    }
    return true;
}

bool RawMqttHandler::loop() {
    bool ret = mqtt->loop();
    delay(10);
    yield();
	#if defined(ESP32)
		esp_task_wdt_reset();
	#elif defined(ESP8266)
		ESP.wdtFeed();
	#endif
    return ret;
}
