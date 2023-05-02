<script>
    import { fmtnum } from "./Helpers";


    export let data;
    export let currency;
    export let hasExport;

    let hasCost = false;
    let cols = 3
    $: {
        hasCost = data && data.h && (data.h.c || data.d.c || data.m.c || data.h.i || data.d.i || data.m.i);
        cols = hasCost ? 3 : 2;
    }
</script>

<div class="mx-2 text-sm">
    <strong>Aktuelle Daten</strong>
    <br/><br/>

    {#if data}
        {#if hasExport}
            <strong>Bezug</strong>
            <div class="grid grid-cols-{cols} mb-3">
                <div>Stunde</div>
                <div class="text-right">{fmtnum(data.h.u,2)} kWh</div>
                {#if hasCost}<div class="text-right">{fmtnum(data.h.c,2)} {currency}</div>{/if}
                <div>Tag</div>
                <div class="text-right">{fmtnum(data.d.u,1)} kWh</div>
                {#if hasCost}<div class="text-right">{fmtnum(data.d.c,1)} {currency}</div>{/if}
                <div>Monat</div>
                <div class="text-right">{fmtnum(data.m.u)} kWh</div>
                {#if hasCost}<div class="text-right">{fmtnum(data.m.c)} {currency}</div>{/if}
            </div>
            <strong>Export</strong>
            <div class="grid grid-cols-{cols}">
                <div>Stunde</div>
                <div class="text-right">{fmtnum(data.h.p,2)} kWh</div>
                {#if hasCost}<div class="text-right">{fmtnum(data.h.i,2)} {currency}</div>{/if}
                <div>Day</div>
                <div class="text-right">{fmtnum(data.d.p,1)} kWh</div>
                {#if hasCost}<div class="text-right">{fmtnum(data.d.i,1)} {currency}</div>{/if}
                <div>Monat</div>
                <div class="text-right">{fmtnum(data.m.p)} kWh</div>
                {#if hasCost}<div class="text-right">{fmtnum(data.m.i)} {currency}</div>{/if}
            </div>
        {:else}
            <strong>Bezug</strong>
            <div class="grid grid-cols-2 mb-3">
                <div>Stunde</div>
                <div class="text-right">{fmtnum(data.h.u,2)} kWh</div>
                <div>Tag</div>
                <div class="text-right">{fmtnum(data.d.u,1)} kWh</div>
                <div>Monat</div>
                <div class="text-right">{fmtnum(data.m.u)} kWh</div>
            </div>
            {#if hasCost}
                <strong>Kosten</strong>
                <div class="grid grid-cols-2">
                    <div>Stunde</div>
                    <div class="text-right">{fmtnum(data.h.c,2)} {currency}</div>
                    <div>Tag</div>
                    <div class="text-right">{fmtnum(data.d.c,1)} {currency}</div>
                    <div>Monat</div>
                    <div class="text-right">{fmtnum(data.m.c)} {currency}</div>
                </div>
            {/if}
        {/if}
    {/if}
</div>