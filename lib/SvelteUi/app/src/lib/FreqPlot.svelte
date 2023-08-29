<script>
    import BarChart from './BarChart.svelte';
    import { hertzcol } from './Helpers.js';

    export let frq;

    let config = {};

    function point(Hz) {
        return {
            label: Hz.toFixed(2)+ 'Hz', 
            title: Hz.toFixed(2) + ' Hz',
            value: isNaN(Hz) ? 0 : Hz, 
            color: hertzcol(Hz ? Hz : 0) 
        };
    };

    $: {
        let xTicks = [];
        let points = [];
        if(frq > 0) {
            xTicks.push({ label: 'Netzfrequenz' });
            points.push(point(frq));
        }
        config = {
            padding: { top: 20, right: 15, bottom: 20, left: 35 },
            y: {
                min: 48.8,
                max: 51.2,
                ticks: [
                    { value: 49, label: '49.0' },
                    { value: 49.5, label: '49.5' } ,                   
                    { value: 50, label: '50 Hz' },
                    { value: 50.5, label: '50.5' },
                    { value: 51, label: '51.0' }
                ]
            },
            x: {
                ticks: xTicks
            },
            points: points
        };
    }
</script>
<BarChart config={config} />
