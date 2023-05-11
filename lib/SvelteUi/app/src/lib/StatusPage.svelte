<script>
    import { metertype, boardtype, isBusPowered, getResetReason } from './Helpers.js';
    import { getSysinfo, gitHubReleaseStore, sysinfoStore } from './DataStores.js';
    import { upgrade, getNextVersion, upgradeWarningText } from './UpgradeHelper';
    import DownloadIcon from './DownloadIcon.svelte';
    import { Link } from 'svelte-navigator';
    import Clock from './Clock.svelte';
    import Mask from './Mask.svelte';
  
    export let data;
    export let sysinfo;

    let cfgItems = [{
        name: 'WiFi',
        key: 'iw'
    },{
        name: 'MQTT',
        key: 'im'
    },{
        name: 'Web',
        key: 'ie'
    },{
        name: 'Meter',
        key: 'it'
    },{
        name: 'Thresholds',
        key: 'ih'
    },{
        name: 'GPIO',
        key: 'ig'
    },{
        name: 'NTP',
        key: 'in'
    },{
        name: 'Price API',
        key: 'is'
    }];
  
    let nextVersion = {};
/*  EHorvat disabled this start
    gitHubReleaseStore.subscribe(releases => {
      nextVersion = getNextVersion(sysinfo.version, releases);
      if(!nextVersion) {
        nextVersion = releases[0];
      }
    });

    function askUpgrade() {
        if(confirm('Do you want to upgrade this device to ' + nextVersion.tag_name + '?')) {
            if((sysinfo.board != 2 && sysinfo.board != 4 && sysinfo.board != 7) || confirm(upgradeWarningText(boardtype(sysinfo.chip, sysinfo.board)))) {
                sysinfoStore.update(s => {
                    s.upgrading = true;
                    return s;
                });
                upgrade(nextVersion.tag_name);
            }
        }
    }
  EHorvat disabled this end   */

    async function reboot() {
      const response = await fetch('/reboot', {
            method: 'POST'
        });
        let res = (await response.json())
    }

    const askReboot = function() {
      if(confirm('Wollen sie den ESP32 Microprozessor jetzt neu starten?')) {
        sysinfoStore.update(s => {
            s.booting = true;
            return s;
        });
        reboot();
      }
    }

    let firmwareFileInput;
    let firmwareFiles = [];
    let firmwareUploading = false;

    let configFileInput;
    let configFiles = [];
    let configUploading = false;

    getSysinfo();
</script>

<div class="grid xl:grid-cols-5 lg:grid-cols-3 md:grid-cols-2">
    <div class="cnt">
        <strong class="text-sm">ESP Information</strong>
        <div class="my-2">
            Chip: {sysinfo.chip}
        </div>
        <div class="my-2">
            Device: <Link to="/vendor">{boardtype(sysinfo.chip, sysinfo.board)}</Link>
        </div>
        <div class="my-2">
            MAC: {sysinfo.mac}
        </div>
        {#if sysinfo.apmac && sysinfo.apmac != sysinfo.mac}
        <div class="my-2">
            AP MAC: {sysinfo.apmac}
        </div>
        <div class="my-2">
            Letzter Neustart:
            {#if data.u > 0}
            <Clock timestamp={new Date(new Date().getTime() - (data.u * 1000))} fullTimeColor="" />
            {:else}
            -
            {/if}
        </div>
        <div class="my-2">
            Grund: {getResetReason(sysinfo)} ({sysinfo.boot_reason}/{sysinfo.ex_cause})
        </div>
        {/if}
        <div class="my-2">
            <button on:click={askReboot} class="text-xs py-1 px-2 rounded bg-yellow-500 text-white mr-3 float-right">Neustart</button>
        </div>
     </div>
    {#if sysinfo.meter}
    <div class="cnt">
        <strong class="text-sm">Stromzaehler</strong>
        <div class="my-2">
            Hersteller: {sysinfo.meter.id}
        </div>
        <div class="my-2">
            Model: {sysinfo.meter.model}
        </div>
        <div class="my-2">
            Seriennr.: {sysinfo.meter.ser}
        </div>
        <div class="my-2">
            Hardware Rev.: {sysinfo.meter.hwr}
        </div>
        <div class="my-2">
            Firmware Rev.: {sysinfo.meter.fwr}
        </div>
    </div>
    {/if}
    {#if sysinfo.net}
    <div class="cnt">
        <strong class="text-sm">Netzwerk</strong>
        <div class="my-2">
            IP: {sysinfo.net.ip}
        </div>
        <div class="my-2">
            Mask: {sysinfo.net.mask}
        </div>
        <div class="my-2">
            Gateway: {sysinfo.net.gw}
        </div>
        <div class="my-2">
            DNS: {sysinfo.net.dns1} {#if sysinfo.net.dns2}/ {sysinfo.net.dns2}{/if}
        </div>
    </div>
    {/if}
    <div class="cnt">
        <strong class="text-sm">Firmware</strong>
        <div class="my-2">
            Neue Firmware (*.bin) installieren:
        </div>
        {#if sysinfo.security == 0 || data.a}
        <div class="my-2 flex">
            <form action="/firmware" enctype="multipart/form-data" method="post" on:submit={() => firmwareUploading=true} autocomplete="off">
                <input style="display:none" name="file" type="file" accept=".bin" bind:this={firmwareFileInput} bind:files={firmwareFiles}>
                {#if firmwareFiles.length == 0}
                <button type="button" on:click={()=>{firmwareFileInput.click();}} class="btn-pri-sm float-right">Firmware File auswaehlen</button>
                {:else}
                File "{firmwareFiles[0].name}" 
                <button type="submit" class="btn-pri-sm2 float-right">Jetzt installieren</button>
                {/if}
            </form>
        </div>
        {/if}
    </div>
    {#if sysinfo.security == 0 || data.a}
    <div class="cnt">
        <strong class="text-sm">Konfiguration sichern & laden</strong>
        <form method="get" action="/configfile.cfg" autocomplete="off">
            <div class="grid grid-cols-2">
                {#each cfgItems as el}
                    <label class="my-1 mx-3"><input type="checkbox" class="rounded" name="{el.key}" value="true" checked/> {el.name}</label>
                {/each}
                <label class="my-1 mx-3 col-span-2"><input type="checkbox" class="rounded" name="ic" value="true"/> inkl. Passwoerter<br/><small>(SSID, PSK, passwords and tokens)</small></label>
            </div>
            {#if configFiles.length == 0}
            <button type="submit" class="btn-pri-sm float-right">Konfig. sichern</button>
            {/if}
        </form>
        <form action="/configfile" enctype="multipart/form-data" method="post" on:submit={() => configUploading=true} autocomplete="off">
            <input style="display:none" name="file" type="file" accept=".cfg" bind:this={configFileInput} bind:files={configFiles}>
            {#if configFiles.length == 0}
            <button type="button" on:click={()=>{configFileInput.click();}} class="btn-pri-sm">Waehle Konfig. File...</button>
            {:else}
            {configFiles[0].name}
            <button type="submit" class="btn-pri-sm2">Konfig. laden</button>
            {/if}
        </form>
    </div>
    {/if}
</div>
<Mask active={firmwareUploading} message="Firmware wird installiert, bitte warten ...."/>
<Mask active={configUploading} message="Konfiguration wird geladen, bitte warten ...."/>
