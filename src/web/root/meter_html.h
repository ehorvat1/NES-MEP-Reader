static const char METER_HTML[] PROGMEM = R"=="==(<div class="alert alert-warning">!!Note!!<br/>MEP Encryption key has to be entered in HEX String Format. Should be 40 characters long, just first 32 char are used.(Something similar to this: 31225670323B2C71446F5532426C4C5332745048 ). After saving a "0x" will show up at beginning. Zeros will fill string up to pos nr. 42</div> <form method=post  action="/save"> <input type=hidden  name=mc  value=true /> <div class="my-3 p-3 bg-white rounded shadow"> <h6>Meter</h6> <div class=row > <div class="col-lg-3 col-md-4 col-sm-6"> <div class="m-2 input-group input-group-sm"> <div class=input-group-prepend > <span class=input-group-text >Manufacturer</span> </div> <input class=form-control  value="{maf}" disabled/> </div> </div> <div class="col-lg-3 col-md-4 col-sm-6"> <div class="m-2 input-group input-group-sm"> <div class=input-group-prepend > <span class=input-group-text >Model</span> </div> <input class=form-control  value="{mod}" disabled/> </div> </div> <div class="col-lg-3 col-md-4 col-sm-6"> <div class="m-2 input-group input-group-sm"> <div class=input-group-prepend > <span class=input-group-text >ID</span> </div> <input class=form-control  value="{mid}" disabled/> </div> </div> </div> <div class=row > <div class="col-lg-3 col-md-4 col-sm-5"> <div class="m-2 input-group input-group-sm"> <div class=input-group-prepend > <span class=input-group-text >Baud rate</span> </div> <select class="form-control sd" name=b > <option value=2400  {b2400}>2400 <option value=4800  {b4800}>4800 <option value=9600  {b9600}>9600 <option value=19200  {b19200}>19200 <option value=38400  {b38400}>38400 <option value=57600  {b57600}>57600 <option value=115200  {b115200}>115200 </select> </div> </div> <div class="col-lg-2 col-md-3 col-sm-4 col-6"> <div class="m-2 input-group input-group-sm"> <div class=input-group-prepend > <span class=input-group-text >Parity</span> </div> <select class="form-control sd" name=c > <option value=2  {c2}>7N1 <option value=3  {c3}>8N1 <option value=10  {c10}>7E1 <option value=11  {c11}>8E1 </select> </div> </div> <div class="col-lg-2 col-md-4 col-sm-3 col-6"> <div class=m-2 > <label class=small ><input type=checkbox  name=i  value=true  {i}/> Invert <span class="d-none d-md-inline">signal</span></label> </div> </div> <div class="col-lg-4 col-sm-8"> <a href="https://github.com/gskjold/AmsToMqttBridge/wiki/Known-hardware-configurations" target=_blank >Known hardware configurations</a> </div> </div> <div class=row > <div class="col-xl-3 col-lg-4 col-md-5 col-sm-7"> <div class="m-2 input-group input-group-sm"> <div class=input-group-prepend > <span class=input-group-text >Distribution system</span> </div> <select class="form-control sd" name=d > <option value=0  {d0}> <option value=1  {d1}>IT or TT (230V) <option value=2  {d2}>TN (400V) </select> </div> </div> <div class="col-lg-3 col-md-4 col-sm-5"> <div class="m-2 input-group input-group-sm"> <div class=input-group-prepend > <span class=input-group-text >Main fuse</span> </div> <input class="form-control text-right" name=f  type=number  min=5  max=255  step=1  value="{f}"/> <div class=input-group-append > <span class=input-group-text >A</span> </div> </div> </div> <div class="col-xl-3 col-lg-4 col-md-5 col-sm-7"> <div class="m-2 input-group input-group-sm"> <div class=input-group-prepend > <span class=input-group-text >Production capacity</span> </div> <input class="form-control text-right" name=p  type=number  min=0  max=255  step=1  value="{p}"/> <div class=input-group-append > <span class=input-group-text >kWp</span> </div> </div> </div> </div> <div class=row > <div class=col-lg-6 > <div class="m-2 input-group input-group-sm"> <div class=input-group-prepend > <span class=input-group-text >MEP Encryption key</span> </div> <input class=form-control  name=e  type=text  value="{e}" placeholder="If applicable"/> </div> </div> <div class=col-lg-6 > <div class="m-2 input-group input-group-sm"> <div class=input-group-prepend > <span class=input-group-text >Authentication key</span> </div> <input class=form-control  name=a  type=text  value="{a}" placeholder="If applicable"/> </div> </div> </div> <div class="row mt-3"> <div class=col-sm-6 > <a href="/thresholds">Configure tariff thresholds</a> </div> <div class="col-sm-6 text-right"> <a href="/meteradvanced">Multipliers</a> </div> </div> </div> <hr/> <div class="row form-group"> <div class=col-6 > <a href="/" class="btn btn-outline-secondary">Back</a> </div> <div class="col-6 text-right"> <button class="btn btn-primary">Save</button> </div> </div> </form>)=="==";
const int METER_HTML_LEN PROGMEM = 4533;