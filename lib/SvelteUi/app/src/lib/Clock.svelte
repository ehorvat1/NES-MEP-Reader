<script>
    import { zeropad, monthnames } from './Helpers.js';

    export let timestamp;
    export let fullTimeColor;
</script>

{#if Math.abs(new Date().getTime()-timestamp.getTime()) < 300000 }
{`${zeropad(timestamp.getDate())}. ${monthnames[timestamp.getMonth()]} ${timestamp.getFullYear()} ${zeropad(timestamp.getHours())}:${zeropad(timestamp.getMinutes())}:${zeropad(timestamp.getSeconds())}`}
{:else}
<span class="{fullTimeColor}">{`${zeropad(timestamp.getDate())}.${zeropad(timestamp.getMonth()+1)}.${timestamp.getFullYear()} ${zeropad(timestamp.getHours())}:${zeropad(timestamp.getMinutes())}`}</span>
{/if}