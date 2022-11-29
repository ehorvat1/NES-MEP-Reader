static const char DOMOTICZ_HTML[] PROGMEM = R"=="==(<form method=post  action="/save"> <input type=hidden  name=dc  value=true /> <div class="my-3 p-3 bg-white rounded shadow"> <div class="d-flex flex-row flex-wrap"> <div class="m-2 input-group input-group-sm" style="width: 200px;"> <div class=input-group-prepend > <span class=input-group-text >Electricity IDX</span> </div> <input type=number  class=form-control  name=elidx  value="%d" min=0  max=65535 /> </div> <div class="m-2 input-group input-group-sm" style="width: 240px;"> <div class=input-group-prepend > <span class=input-group-text >Current (3 Phase) IDX</span> </div> <input type=number  class=form-control  name=cl1idx  value="%d" min=0  max=65535 /> </div> </div> <div class="d-flex flex-row flex-wrap"> <div class="m-2 input-group input-group-sm" style="width: 200px;"> <div class=input-group-prepend > <span class=input-group-text >Voltage L1 IDX</span> </div> <input type=number  class=form-control  name=vl1idx  value="%d" min=0  max=65535 /> </div> <div class="m-2 input-group input-group-sm" style="width: 200px;"> <div class=input-group-prepend > <span class=input-group-text >Voltage L2 IDX</span> </div> <input type=number  class=form-control  name=vl2idx  value="%d" min=0  max=65535 /> </div> <div class="m-2 input-group input-group-sm" style="width: 200px;"> <div class=input-group-prepend > <span class=input-group-text >Voltage L3 IDX</span> </div> <input type=number  class=form-control  name=vl3idx  value="%d" min=0  max=65535 /> </div> </div> </div> <hr/> <div class="row form-group"> <div class=col-6 > <a href="/mqtt" class="btn btn-outline-secondary">Back</a> </div> <div class="col-6 text-right"> <button class="btn btn-primary">Save</button> </div> </div> </form>)=="==";
const int DOMOTICZ_HTML_LEN PROGMEM = 1701;