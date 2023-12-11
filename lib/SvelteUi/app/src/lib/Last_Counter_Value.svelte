<script>
    export let last_Counter_Info;
    export let last_Counter_Value;
    export let last_Counter_Costs;    
    export let last_Counter_Diff;
    export let last_expCounter_Info;
    export let last_expCounter_Value;
    export let last_expCounter_Costs;    
    export let last_expCounter_Diff;
    export let hasExport;
    export let currency;
</script>

<div class="mx-2 text-sm">
    <strong>Letzte Abrechnung</strong>
    <br/><br/>
    <strong>f&uuml;r Bezug</strong>
    <div class="grid grid-cols-2 mb-3">
        <div>Info zu Bezug</div>
        <div class="text-right">{last_Counter_Info}</div>       
        <div>Z&auml;hlerstand</div>
        <div class="text-right">{typeof last_Counter_Value !== 'undefined' ? last_Counter_Value.toFixed(0) : '-'} kWh</div>
        <div>Verbrauch</div>
        <div class="text-right">{typeof last_Counter_Diff !== 'undefined' ? last_Counter_Diff.toFixed(0) : '-'} kWh</div>
        <div>Kosten</div>
        <div class="text-right">{typeof last_Counter_Costs !== 'undefined' ? last_Counter_Costs.toFixed(2) : '-'} {currency}</div>
    </div>
    {#if hasExport}
        <strong>f&uuml;r Export</strong>
        <div class="grid grid-cols-2 mb-3">
            <div>Info zu Export</div>
            <div class="text-right">{last_expCounter_Info}</div>       
            <div>Z&auml;hlerstand</div>
            <div class="text-right">{typeof last_expCounter_Value !== 'undefined' ? last_expCounter_Value.toFixed(0) : '-'} kWh</div>
            <div>Export</div>
            <div class="text-right">{typeof last_expCounter_Diff !== 'undefined' ? last_expCounter_Diff.toFixed(0) : '-'} kWh</div>
            <div>Einnahmen</div>
            <div class="text-right">{typeof last_expCounter_Costs !== 'undefined' ? last_expCounter_Costs.toFixed(2) : '-'} {currency}</div>
        </div>
    {/if}
</div>

