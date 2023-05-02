<script>
    export let importInstant;
    export let exportInstant;
    export let importTotal;
    export let exportTotal;
</script>

<div class="mx-2 text-sm">
    <strong>Blindleistung</strong>
    
    <div class="grid grid-cols-2 mt-4">
        <div>Aktueller Bezug</div>
        <div class="text-right">{typeof importInstant !== 'undefined' ? importInstant.toFixed(0) : '-'} VAr</div>
        <div>Aktueller Export</div>
        <div class="text-right">{typeof exportInstant !== 'undefined' ? exportInstant.toFixed(0) : '-'} VAr</div>
    </div>
    
    <div class="grid grid-cols-2 mt-4">
        <div>Gesamt Bezug</div>
        <div class="text-right">{typeof importTotal !== 'undefined' ? importTotal.toFixed(1) : '-'} kVArh</div>
        <div>Gesamt Export</div>
        <div class="text-right">{typeof exportTotal !== 'undefined' ? exportTotal.toFixed(1) : '-'} kVArh</div>
    </div>
</div>