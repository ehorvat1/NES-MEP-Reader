static const char RESET_HTML[] PROGMEM = R"=="==(<form method=post > <div class="my-3 p-3 bg-white rounded shadow"> <div class="alert alert-danger">Are you sure you want reset this device to factory settings? ALL configuration will be erased!</div> </div> <hr/> <div class="row form-group"> <div class=col-6 > <a href="javascript:history.back();" class="btn btn-outline-secondary">Back</a> </div> <div class="col-6 text-right"> <button class="btn btn-danger" name=perform  value=true >Perform factory reset</button> </div> </div> </form>)=="==";
const int RESET_HTML_LEN PROGMEM = 488;