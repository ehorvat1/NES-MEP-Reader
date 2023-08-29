<script>
    import { pricesStore, dayPlotStore, monthPlotStore, minutePlotStore, hourPlotStore } from './DataStores.js'; //EHorvat added: , hourPlotStore
    import { importcol, exportcol, metertype, uiVisibility } from './Helpers.js';
    import PowerGauge from './PowerGauge.svelte';
    import FreqPlot from './FreqPlot.svelte';
    import VoltPlot from './VoltPlot.svelte';
    import AmpPlot from './AmpPlot.svelte';
    import AccountingData from './AccountingData.svelte';
    import Last_Counter_Value from './Last_Counter_Value.svelte';
    import ReactiveData from './ReactiveData.svelte';
    import PricePlot from './PricePlot.svelte';
    import DayPlot from './DayPlot.svelte';
    import MonthPlot from './MonthPlot.svelte';    
    import MinutePlot from './MinutePlot.svelte';//EHorvat Minute plot added line
    import HourPlot from './HourPlot.svelte';//EHorvat hour plot added line
//    import TemperaturePlot from './TemperaturePlot.svelte';
    import TariffPeakChart from './TariffPeakChart.svelte';

    export let data = {}
    export let sysinfo = {}
    let prices = {}
    let dayPlot = {}
    let monthPlot = {}
    let minutePlot = {} //EHorvat minute plot added line    
    let hourPlot = {} //EHorvat hour plot added line
//    let temperatures = {};
    pricesStore.subscribe(update => {
        prices = update;
    });
    dayPlotStore.subscribe(update => {
        dayPlot = update;
    });
    monthPlotStore.subscribe(update => {
        monthPlot = update;
    });    
    minutePlotStore.subscribe(update => {  //EHorvat minute plot
        minutePlot = update;
    });    
    hourPlotStore.subscribe(update => {     //EHorvat hour plot
        hourPlot = update;
    });
//    temperaturesStore.subscribe(update => {
//        temperatures = update;
//    });
</script>

<div class="grid 2xl:grid-cols-6 xl:grid-cols-5 lg:grid-cols-4 md:grid-cols-3 sm:grid-cols-2">
    {#if uiVisibility(sysinfo.ui.i, data.i)}
        <div class="cnt">
            <div class="grid grid-cols-2">
                <div class="col-span-2"><!-- EHorvat translated to german: Import to Bezug -->
                    <PowerGauge val={data.i ? data.i : 0} max={data.im ? data.im : 15000} unit="W" label="Bezug" sub={data.p} subunit={data.pc} colorFn={importcol}/>
                </div>
                <div>{data.mt ? metertype(data.mt) : '-'}</div>
                <div class="text-right">{data.ic ? data.ic.toFixed(1) : '-'} kWh</div>
            </div>
        </div>
    {/if}
    {#if uiVisibility(sysinfo.ui.e, data.om || data.e > 0)}
        <div class="cnt">
            <div class="grid grid-cols-2">
                <div class="col-span-2"> <!-- EHorvat next line: show fixed income refund ...added  sub={data.pi} subunit={data.pc} -->
                    <PowerGauge val={data.e ? data.e : 0} max={data.om ? data.om * 1000 : 10000} unit="W" label="Export" sub={data.pi} subunit={data.pc} colorFn={exportcol}/>
                </div>
                <div></div>
                <div class="text-right">{data.ec ? data.ec.toFixed(1) : '-'} kWh</div>
            </div>
        </div>
    {/if}
    {#if uiVisibility(sysinfo.ui.f, data.frq)}
        <div class="cnt">
            <FreqPlot frq={data.frq}/>
         </div>
    {/if}
    {#if uiVisibility(sysinfo.ui.v, data.u1 > 100 || data.u2 > 100 || data.u3 > 100)}
        <div class="cnt">
            <VoltPlot u1={data.u1} u2={data.u2} u3={data.u3} ds={data.ds}/>
        </div>
    {/if}
    {#if uiVisibility(sysinfo.ui.a, data.i1 > 0.01 || data.i2 > 0.01 || data.i3 > 0.01)}
        <div class="cnt">
            <AmpPlot u1={data.u1} u2={data.u2} u3={data.u3} i1={data.i1} i2={data.i2} i3={data.i3} max={data.mf ? data.mf : 32}/>
        </div>
    {/if}
    {#if uiVisibility(sysinfo.ui.c, data.ea)}
        <div class="cnt">
            <AccountingData sysinfo={sysinfo} data={data.ea} currency={data.pc} hasExport={data.om > 0 || data.e > 0}/>
        </div>
    {/if}
    {#if uiVisibility(sysinfo.ui.l, data.py)}
        <div class="cnt">
            <Last_Counter_Value last_Counter_Value={data.py} last_Counter_Info={data.pd} last_Counter_Costs={data.pl} last_Counter_Diff={data.pa} last_expCounter_Value={data.pz} last_expCounter_Info={data.pg} last_expCounter_Costs={data.pj} last_expCounter_Diff={data.pk} hasExport={uiVisibility(sysinfo.ui.e, data.om || data.e > 0)}/>
        </div>
    {/if}
    {#if uiVisibility(sysinfo.ui.r, data.ri > 0 || data.re > 0 || data.ric > 0 || data.rec > 0)}
        <div class="cnt">
            <ReactiveData importInstant={data.ri} exportInstant={data.re} importTotal={data.ric} exportTotal={data.rec} PowerFactorL1={data.f1} PowerFactorL2={data.f2} PowerFactorL3={data.f3} AparentPower={data.va} ReactivePower_Q1={data.rq1} ReactivePower_Q2={data.rq2} ReactivePower_Q3={data.rq3} ReactivePower_Q4={data.rq4}/>
        </div>
    {/if}
    {#if uiVisibility(sysinfo.ui.t, data.pr && (data.pr.startsWith("10YNO") || data.pr == '10Y1001A1001A48H'))}
        <div class="cnt h-64">
            <TariffPeakChart />
        </div>
    {/if}
    {#if uiVisibility(sysinfo.ui.p, data.pe && !Number.isNaN(data.p))}
        <div class="cnt gwf">
            <PricePlot json={prices}/>
        </div>
    {/if}
    {#if uiVisibility(sysinfo.ui.q, minutePlot)}
    <div class="cnt gwf">
        <MinutePlot json={minutePlot} />
    </div>
    {/if}
    {#if uiVisibility(sysinfo.ui.h, hourPlot)}
    <div class="cnt gwf">
        <HourPlot json={hourPlot} />
    </div>
    {/if}
    {#if uiVisibility(sysinfo.ui.d, dayPlot)}
        <div class="cnt gwf">
            <DayPlot json={dayPlot} />
        </div>
    {/if}
    {#if uiVisibility(sysinfo.ui.m, monthPlot)}
        <div class="cnt gwf">
            <MonthPlot json={monthPlot} />
        </div>
    {/if}
</div>