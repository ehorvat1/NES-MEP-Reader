<script>
    import { Link } from "svelte-navigator";
    import { sysinfoStore, getGitHubReleases, gitHubReleaseStore } from './DataStores.js';
    import { upgrade, getNextVersion, upgradeWarningText } from './UpgradeHelper';
    import { boardtype, hanError, mqttError, priceError, isBusPowered, wiki, bcol } from './Helpers.js';
    import AmsleserSvg from "./../assets/favicon.svg";
    import GitHubLogo from './../assets/github.svg';
    import Uptime from "./Uptime.svelte";
    import Badge from './Badge.svelte';
    import Clock from './Clock.svelte';
    import GearIcon from './GearIcon.svelte';
    import InfoIcon from "./InfoIcon.svelte";
    import HelpIcon from "./HelpIcon.svelte";
    import DownloadIcon from "./DownloadIcon.svelte";

    export let data = {}
    let sysinfo = {}

    let nextVersion = {};
 
    function askUpgrade() {
        if(confirm('Do you want to upgrade this device to ' + nextVersion.tag_name + '?')) {
          if(!isBusPowered(sysinfo.board) || confirm(upgradeWarningText(boardtype(sysinfo.chip, sysinfo.board)))) {
                sysinfoStore.update(s => {
                    s.upgrading = true;
                    return s;
                });
                upgrade(nextVersion.tag_name);
            }
        }
    }
    sysinfoStore.subscribe(update => {
      sysinfo = update;
      if(update.fwconsent === 1) {
        getGitHubReleases();
      }
    });

    gitHubReleaseStore.subscribe(releases => {
      nextVersion = getNextVersion(sysinfo.version, releases);
    });
</script>

<nav class="bg-violet-600 p-1 rounded-md mx-2">
      <div class="flex flex-wrap space-x-4 text-sm text-gray-300">
        <div class="flex text-lg text-gray-100 p-2">
          <Link to="/">NES Stromzaehler v2.0</Link>
        </div>
        <div class="flex-none my-auto p-2 flex space-x-4">
          <div class="flex-none my-auto"><Uptime epoch={data.u}/></div>
          {#if data.t > -50}
          <div class="flex-none my-auto">{ data.t > -50 ? data.t.toFixed(1) : '-' }&deg;C</div>
          {/if}
          <div class="flex-none my-auto">Freier RAM: {data.m ? (data.m/1000).toFixed(1) : '-'}kb</div>
        </div>
        <div class="flex-auto flex-wrap my-auto justify-center p-2">
          <Badge title="ESP" text={sysinfo.booting ? 'Booting' : data.v > 2.0 ? data.v.toFixed(2)+"V" : "ESP"} color={bcol(sysinfo.booting ? 2 : data.em)}/>
          <Badge title="MEP" text="MEP" color={bcol(sysinfo.booting ? 9 : data.hm)}/>
          <Badge title="WiFi" text={data.r ? data.r.toFixed(0)+"dBm" : "WiFi"} color={bcol(sysinfo.booting ? 9 : data.wm)}/>
          <Badge title="MQTT" text="MQTT" color={bcol(sysinfo.booting ? 9 : data.mm)}/>
        </div>
        {#if data.he < 0 || data.he > 0}
        <div class="bd-red">{ 'MEP: ' + hanError(data.he) }</div>
        {/if}
        {#if data.me < 0}
        <div class="bd-red">{ 'MQTT: ' + mqttError(data.me) }</div>
        {/if}
        {#if data.ee > 0 || data.ee < 0}
        <div class="bd-red">{ 'PriceAPI: ' + priceError(data.ee) }</div>
        {/if}
      <div class="flex-auto p-2 flex flex-row-reverse flex-wrap">
          <div class="flex-none">
            <a class="float-right" href='https://github.com/ehorvat1/NES-MEP-Reader' target='_blank' rel="noreferrer" aria-label="GitHub"><img class="gh-logo" src={GitHubLogo} alt="GitHub repo"/></a>
          </div>
          <div class="flex-none my-auto px-2">
            <Clock timestamp={ data.c ? new Date(data.c * 1000) : new Date(0) } fullTimeColor="text-red-500" />
          </div>
          {#if sysinfo.vndcfg && sysinfo.usrcfg}
          <div class="flex-none px-1 mt-1" title="Configuration">
            <Link to="/configuration"><GearIcon/></Link>
          </div>
          <div class="flex-none px-1 mt-1" title="ESP Information">
            <Link to="/status"><InfoIcon/></Link>
          </div>
          {/if}
        </div> 
      </div>
</nav>