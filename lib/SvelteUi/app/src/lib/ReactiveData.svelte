<script>
    export let importInstant;
    export let exportInstant;
    export let importTotal;
    export let exportTotal;
    export let PowerFactorL1; //EHorvat new
    export let PowerFactorL2; //EHorvat new
    export let PowerFactorL3; //EHorvat new
    export let AparentPower; //EHorvat new
    export let ReactivePower_Q1; //EHorvat new
    export let ReactivePower_Q2; //EHorvat new
    export let ReactivePower_Q3; //EHorvat new
    export let ReactivePower_Q4; //EHorvat new
</script>

<div class="mx-2 text-sm">
    <strong>Blind-/Scheinleistung</strong>
    <div class="grid grid-cols-2 mt-4">
        <div>Scheinleistung</div>
        <div class="text-right">{typeof AparentPower !== 'undefined' ? AparentPower.toFixed(0) : '-'} VA</div>
        <div>BlindLeist. ind</div>
        <div class="text-right">{typeof importInstant !== 'undefined' ? importInstant.toFixed(0) : '-'} VAr</div>
        <div>BlindLeist. kap</div>
        <div class="text-right">{typeof exportInstant !== 'undefined' ? exportInstant.toFixed(0) : '-'} VAr</div>
    </div>
    <div class="grid grid-cols-2 mt-4">
        <div>Blindleist. Q1</div>
        <div class="text-right">{typeof ReactivePower_Q1 !== 'undefined' ? ReactivePower_Q1.toFixed(0) : '-'} VAr</div>        
        <div>Blindleist. Q2</div>
        <div class="text-right">{typeof ReactivePower_Q2 !== 'undefined' ? ReactivePower_Q2.toFixed(0) : '-'} VAr</div>        
        <div>Blindleist. Q3</div>
        <div class="text-right">{typeof ReactivePower_Q3 !== 'undefined' ? ReactivePower_Q3.toFixed(0) : '-'} VAr</div>        
        <div>Blindleist. Q4</div>
        <div class="text-right">{typeof ReactivePower_Q4 !== 'undefined' ? ReactivePower_Q4.toFixed(0) : '-'} VAr</div>        
        <div>Summe BL ind</div>
        <div class="text-right">{typeof importTotal !== 'undefined' ? importTotal.toFixed(1) : '-'} kVArh</div>
        <div>Summe BL kap</div>
        <div class="text-right">{typeof exportTotal !== 'undefined' ? exportTotal.toFixed(1) : '-'} kVArh</div>
    </div>    
    <div class="grid grid-cols-2 mt-4">
        <div>Cos Phi L1</div>
        <div class="text-right">{typeof PowerFactorL1 !== 'undefined' ? PowerFactorL1.toFixed(2) : '-'} W/VA</div>        
        <div>Cos Phi L2</div>
        <div class="text-right">{typeof PowerFactorL2 !== 'undefined' ? PowerFactorL2.toFixed(2) : '-'} W/VA</div>        
        <div>Cos Phi L3</div>
        <div class="text-right">{typeof PowerFactorL3 !== 'undefined' ? PowerFactorL3.toFixed(2) : '-'} W/VA</div>
    </div>
</div>