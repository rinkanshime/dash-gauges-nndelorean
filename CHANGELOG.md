/*  Changelog
 *   
 *  TODO: Way to make device say IP address stand-alone
 *  
 *  2023/01/04 (A10001986)
 *    - Read millis() instead of using static variable in main loop (too many subs 
 *      to keep track)
 *  2023/12/21 (A10001986)
 *    - Correct voltage for Simpson Roentgens meter to 14mV. TODO: Find a suitable
 *      resistor value for driving it with a reasonable voltage. 140mV is ridiculous.
 *  2023/12/21 (A10001986)
 *    - Add hardware config for original Simpson Roentgen meter (0-0.14V)
 *  2023/12/16 (A10001986)
 *    - Make DoorSwitch support a compile time option in order to allow using GPIO
 *      for other purposes
 *  2023/12/08 (A10001986)
 *    - Add option to trigger a BTTFN-wide TT when pressing the TT button (instead
 *      of a stand-alone TT).
 *    - Fix wakeup vs. SS logic
 *  2023/11/30 (A10001986)
 *   - Some better sounds
 *   - Fix end of "special" LED signal
 *  2023/11/22 (A10001986)
 *    - Wake up only if "speed" is from RotEnc, not when from GPS
 *  2023/11/20 (A10001986)
 *    - Wake up on GPS speed/RotEnc changes
 *  2023/11/06 (A10001986)
 *    - Abort audio file installer on first error
 *  2023/11/05 (A10001986)
 *    - Settings: (De)serialize JSON from/to buffer instead of file
 *    - Fix corrupted Shuffle setting
 *  2023/11/04 (A10001986)
 *    - Unmount filesystems before reboot
 *  2023/11/02 (A10001986)
 *    - Start CP earlier to reduce startup delay caused by that darn WiFi scan upon
 *      CP start.
 *    * WiFiManager: Disable pre-scanning of WiFi networks when starting the CP.
 *      Scanning is now only done when accessing the "Configure WiFi" page.
 *      To do that in your own installation, set _preloadwifiscan to false
 *      in WiFiManager.h
 *  2023/11/01 (A10001986)
 *    - Change default volume to fixed, level 6; fix saving from CP.
 *    - Stop audio earlier before rebooting when saving CP settings
 *  2023/10/31 (A10001986)
 *    - BTTFN: User can now enter TCD's hostname instead of IP address. If hostname
 *      is given, TCD must be on same local network. Uses multicast, not DNS.
 *    - Add "binary" gauges types; "binary" means the gauges only know "empty" and "full".
 *      Two types added: One for when gauges have separate pins, one when gauges are 
 *      interconnected. This is meant for gauge types with higher voltages that are 
 *      driven through relays.
 *  2023/10/29 (A10001986)
 *    - Fixes for saving volume (cp value not copied; copy sec.settings)
 *  2023/10/26 (A10001986)
 *    - New startup sound, played with delay
 *  2023/10/17 (A10001986)
 *    - Add Plutonium-unrelated "door switch" facility. Connect a door switch to 
 *      IO27 (active low; wires to door switch need to be GND and IO27), and the Panel 
 *      will play a "door" sound whenever the switch activates (NC/NO selectable in CP), 
 *      with optional delay.
 *    - Early-init side & door switches and do not trigger event until next change
 *  2023/10/14 (A10001986)
 *    - Disable s-s upon entering new "full" percentages
 *    - Correct max voltage for VU meter to 1.6V
 *  2023/10/05-10 (A10001986)
 *    - Add support for "wakeup" command (BTTFN/MQTT)
 *    - Make "empty" level configurable
 *    - Correct VU meter max voltage to 1.66. VU meter is manually adjusted to "0"
 *      on the green "Roentgens" scale, which is a bit into the original VU scale.
 *    - Some screen-saver logic fixes
 *  2023/10/04 (A10001986)
 *    - Fix audio playback from flash FS
 *  2023/09/30 (A10001986)
 *    - Extend remote commands to 32 bit
 *    - Fix volume control (CP vs TCD-remote commands)
 *  2023/09/29 (A10001986)
 *    - Add emercengy procedure for deleting static IP and AP password (hold TT while
 *      powering up, switch side switch twice (empty LED lits), then release TT button.
 *    - Add volume control in CP
 *  2023/09/28 (A10001986)
 *    - New sounds; complete installer; add volume control
 *  2023/09/27 (A10001986)
 *    - First version of TT
 *  2023/09/26 (A10001986)
 *    - Make TCD-alarm sound optional
 *    - Make refill more robust; better LED handling; many other changes.
 *    - Refactor gauge handling for easily adding other gauge types
 *  2023/09/25 (A10001986)
 *    - Add option to handle TT triggers from wired TCD without 5s lead. Respective
 *      options on TCD and external props must be set identically.
 *  2023/09/23 (A10001986)
 *    - Add remote control facility through TCD keypad (requires BTTFN connection 
 *      with TCD). Commands for Dash Gauges are 9000-9999.
 *  2023/09/22 (A10001986)
 *    - Read DAC EEPROM data and reset if not properly set
 *    - lots of other additions
 *  2023/09/21 (A10001986)
 *    - Initial version
 */