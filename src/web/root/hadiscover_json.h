static const char HADISCOVER_JSON[] PROGMEM = R"=="==({"name":"%s","stat_t":"%s%s","uniq_id":"%s_%s","obj_id":"%s_%s","unit_of_meas":"%s","val_tpl":"{{ value_json.%s | is_defined }}","dev_cla":"%s","dev":{"ids":["%s"],"name":"%s","mdl":"%s","sw":"%s","mf":"%s","cu":"%s"}%s%s})=="==";
const int HADISCOVER_JSON_LEN PROGMEM = 222;