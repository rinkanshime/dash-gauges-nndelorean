# The DIY Dash Gauges

Note that this is a custom built prop; there is no kit available.

![Dash Gauges](https://github.com/realA10001986/Dash-Gauges/assets/76924199/e01aeb44-ea61-4685-95ee-d673b1e654ff)

The Panel consists of several parts:
- Aluminum (Aluminium for non-Americans) enclosure; the measurements are in the ["enclosure"](DIY/enclosure) folder of this repository.
- The gauges: The smaller gauges are H&P 631-14672 (built by Phaostron) and the "Plutonium chamber" gauge is a Simpson 49L VU Meter, all driven by a MCP4728 quad-DAC (on an Adafruit breakout board). Movie-accurate faces for these gauges are in the ["faces-labels"](DIY/faces-labels) folder of this repository.
- A Switch Board, which is mounted on the smaller gauges' back side; it carries the interface for the gauges, the lights and switches, as well as some connectors for external switches/buttons. This Switch Board is easy to assemble, it only carries some resistors and connectors. The gerbers as well as an EasyEDA file are in the ["electronics"](DIY/electronics) folder of this repository, JLCPCB can make this board for you. A BOM is available as well.
- A Control Board: In lack of a dedicated control board (which to design unfortunately is beyond my abilities), the heart of the device is a slightly modified TCD control board from [CircuitSetup](https://circuitsetup.us/product/time-circuits-display-control-board-with-keypad-trw-style-lenses/).

### Control board

The control board is a modified TCD control board from CircuitSetup:

- The ENTER button is removed from the PCB and its pins serve as the "Side Switch".
- The white LED serves as the "Empty" LED in the "Roentgens" meter; it needs to desoldered.
- The other LEDS are removed from the PCB as they stick out and are not needed.
- The volume pot can be removed; this is, of course, optional, but since this board is assumingly hidden somewhere, the pot would be inaccessible anyway.
- The i2c, audio and IO connectors were relocated to the front side of the PCB (they are normally on the back)

![ControlBoard](https://github.com/realA10001986/Dash-Gauges/assets/76924199/82f25c22-d60b-493c-a785-5c8b78f2ca32)

As regards the cabling, two remarks:
- I used each 2 wires for GND and 5V (black/white, green/blue), since the wires I used are quite thin.
- I put each a wire of GND (brown, orange) between and beside the SDA/SCL wires to avoid crosstalk.

### Switch board

For the very gauges hardware I used, I designed a simple "switch board" which mounts on the smaller gauges. It carries the MCP4728 breakout board, a single channel relay board, all resistors for the gauges and LEDs, the LEDs for the smaller gauges and connectors for cables to the control board and to the "Roentgens" gauge. Also, it has connectors for an external Time Travel button and the door switches.

![SwitchBoard1.7](https://github.com/realA10001986/Dash-Gauges/assets/76924199/1adf1639-6e81-44df-b56d-0eba04ba26b8)

The Switch Board is mounted on the smaller gauges like this:

![Mounted](https://github.com/realA10001986/Dash-Gauges/assets/76924199/33c10828-7aa2-4724-a9f2-575e57dd31e3)

It carries this relay module for the lights (desolder the screw terminals, put in pin socket, pitch 5mm, 3 positions, for example Samtec HPF-03-01-T-S):

![relay](https://github.com/realA10001986/Dash-Gauges/assets/76924199/eef6cc62-21e1-4700-99df-499739c4ea61)

This module is not the most elegant solution but the easiest one if you, like me, are using real lamps instead of LEDs: also, it allows for an external power source for the lights.

The Switch Board also carries the Adafruit MCP4728 break-out board; just solder pin sockets to both lines of pads on the PCB (pitch 2.54mm, 6 positions, for example Samtec SSW-106-01-F-S).

Parts on Switch Board:
- R1, R2: Resistors for center gauge. Depend on gauge and supply voltage; for H&P 631-14672 470R, 8k2
- R3, R4: Resistors for left gauge. Depend on gauge and supply voltage; for H&P 631-14672 470R, 8k2
- R5, R6: Resistors for Roentgens gauge. Depend on gauge and supply voltage; for Simpson 49L VU meter total 3k6 (3k3+330R, for instance)
- R7, R8: Resistors for LEDs of left and center gauge. Voltage is 5V, depends on LED type and desired brightness (eg 150R)
- R11: Resistor for Roentgens backlight. If using lamps, just bridge. Voltage is 5V.

Connectors on the Switch Board:
- Audio: This allows connecting the audio from the Control Board; the signal is directed to the top-left audio connector, where a speaker is to be attached.
- Data (from left to right):
  * 3_3V: 3.3V from the Control Board
  * SW: From the ENTER button of the Control Board
  * E-LED: From the white LED on the Control Board
  * IO14: From "IO14" on the Control Board
  * IO13: From "IO13" on the Control Board
  * IO27: From "IO27" on the Control Board
 
- 5V/GND: 5V and GND from the Control Board. There are two connectors for power on the Switch Board; you can choose which one suits you better.

- SCL/SDA: The i2c signal from he Control Board.

A connection diagram is [here](DIY/electronics/connection%20diagram.png). Please note that when using a Control Board version 1.3, the IO connectors are at different locations, but still carry their "IOxx" name in all cases on the PCB. IO13 is on the "Fake PWR" connector, IO14 and IO27 are on the "Time Travel" connector.

### Gauges

The gauges are connected through an Adafruit MCP4728 breakout board, which is an i2c-driven quad-DAC and mounted on the switch board. This DAC allows arbitrary voltages up to 5V, but the gauges used here use much lower voltages. If you use different gauges, you need to add your configuration to the firmware. More on this below.

*Important*: When using the MCP4728 in your project, do not connect the actual gauges until you selected the right hardware type in the Config Portal and have powered-down and powered-up the device once afterwards. This power-cycle is needed to reset the MCP4728's EEPROM to the correct settings and to avoid a power output too high at boot.

#### "Primary", "Percent Power"

For the smaller gauges I used two H&P 631-14672 (built by Phaostron), which are (were?) oddly available in volumes on ebay. The pointers on these are red, but an Edding permanent marker was quickly able to change them to black. These gauges have a scale from 0 to 0.5V, but can't cope with 0.5V, they need a resistor in series. I found 8k2 + 470R to be the best value (R1+R2, R3+R4 on the Switch Board).

Those two gauges are driven by channels A and B of the MCP4728. They show nearly identical readings at 10% and at 90%, in the middle they differ a bit, despite the voltage being identical. But since the idea here is not to actually measure voltage, that is still ok, the "full" percentage is configurable after all.

The movie-accurate dials of those gauges are available in the [DIY/faces-labels](DIY/faces-labels) folder in this repository.

For the backlight, I drilled a hole in the rear of the metal enclosure, center bottom, and put a 5mm yellow LED (590nm) on the Switch Board (LED1, LED2, with suitable resistors (R7/R8; depending on LED, probably around 150R). Most replicas use white LEDs, but I think on the A-Car as shown in the Petersen Museum, there are yellow ones used, and I found white ones too bright. The LEDs are mounted on the Switch Board so that they stick out 12mm from PCB to the LED's top.

#### "Roentgens"

The big "Roentgens" gauge is more of a problem. The original in the movie was a real Roentgens meter from a CP95 radiac. Such devices are hard to find, let alone one with the correct Simpson meter. The CP95 was built over a long period of time and they used meters from different manufacturers.

Since I could not find a properly equipped CP95, I searched for an alternative ... and came across a lot of Simpson meters that looked good (while not identical). However: One - quite important - issue is that most Simpson meters are not illuminated. Because of this, their front is thinner, the glass is closer to the dial, and that is a problem because the movie-accurate "Empty" light won't fit.

A word on Simpson model numbers: Their main model number means "case style", not "type of meter". "Model 49" therefore only means "4.5 inch case", but not whether this is a VU meter, a voltmeter, or what not:

<img width="985" alt="Simpson meters" src="https://github.com/realA10001986/Dash-Gauges/assets/76924199/24336a00-b8af-431c-b720-0a833c483d11">

The only Simpson meters that came with illumination - apart from the Roentgens meters - were apparently their VU meters, models 49L ("L" for "light"; not listed above) and 142 (10470, 10540). Model 49L has the correct front dimensions; depending on their build date, they have either the three bands of "stripes" (like in the movie), or one thicker band of "stripes" in the center. (Later models, unfortunately using the same model number, look entirely different.)

I was lucky to score a **Simpson model 49L VU-meter** with the movie-accurate front, which is operated with a 3k6 resistor in series (R5+R6 on the Switch Board). Its lighting is through two 6V lamps (run at 5V) which need no resistor; R11 on the Switch Board is therefore bridged with a wire. If you prefer install LEDs, put a suitable resistor in place instead. The additional red pointer was added by drilling a hole into the front and putting a pointer from another meter inside. This red pointer is not moving, so it is reasonably easy to add.

The **model 142 VU-meters**, while perfectly usable electronically, are a bit smaller (4.25x3.9" vs 4.66x4.2") and look a bit different on the back; their barrel is thicker (3.25" vs 2.78" in diameter), and the screws are not at the outer corners but closer to the barrel. Unfortunately, the barrel is so big that it does not allow for a hole for the "Empty" light; this must be done another way. There is a special drawing in the DIY/enclosure folder for model 142 dimensions.

If you can't find a VU-meter or consider the 142 too far off, you could try going with a Simpson voltmeter or ammeter (models 29, 39, 49, 59, or 79 fit size-wise). These meters mostly are for voltages/currents beyond what we have available directly, but: Most of those meters have built-in resistors that reduce the voltage for the coil to something far lower: For instance, the **Simpson model 49 voltmeter 0-50V DC (SK 525-447)** has a 50K resistor inside; if this resistor is bridged, the meter shows full scale at 0.0375V. With a 5K6 or so resistor is shows full scale at approx 5V, which is perfectly usable for our purposes. But again: You also need to compromise on the "Empty" light, since non-illuminated Simpson meters are too thin.

Speaking of the "Empty" light: I used a light like this one, available from aliexpress:

![emptylight](https://github.com/realA10001986/Dash-Gauges/assets/76924199/46731b85-ddb7-45f9-8091-a70262e9968f)

There are also buttons that look identical:

![emptybutton](https://github.com/realA10001986/Dash-Gauges/assets/76924199/53187b70-9399-44a4-bd78-090f055a3423)

The LED in those lights/buttons is driven with 12V using a resistor; this resistor needs to be removed. No need to take out the blue part for this modification; just remove the red cover and pull out the LED; then desolder the LED and bridge the resistor.

Most Simpson meters have a drop-shaped pointer top which I was not able to remove (in fact, I didn't even try; I don't think the pointer top would have ended up properly straight); although I mounted the "Empty" light as high on the scale as possible, the pointer was still too long and collided with the light. My solution was to change the bends of the pointer where it leaves the driving mechanism more into an "S" shape, and I could thereby make it ever so short enough to pass the light. Another way would be to cut off the drop part, but that would make the pointer a tad too short in my opinion.

About the hole for the "Empty" light: Above light/button requires a 16mm hole. I started off drilling that hole into the dial. Then I mounted the dial into the meter and marked the hole on the plastic enclosure with a pencil. The next step was to remove the dial again, wrap the mechanism in plastic to keep dust out, and drill a smaller hole (7mm) into the enclosure. Then I milled that hole into a bigger one, until the button fit. The plastic of the enclosure is quite brittle and breaks easily. Drilling a 16mm hole appeared too risky. Hence the drill/mill method.

### Enclosure

The enclosure consists of three parts: The front and two side pieces. Measurements are in the [DIY/enclosure](DIY/enclosure) folder of this repository.

You can buy an enclosure at [CircuitSetup](https://circuitsetup.us/product/delorean-time-machine-dash-plutonium-gauge-bezel/); note that it is for a model 49 panel meter ('Roentgens'); a model 142 won't fit.

### Connecting a Time Travel button

The Time Travel button can be connected to the Control Board or the Switch Board:

On the Control Board, connect the button to "IO13" and "5V" of the "IO13" connector. In case of a Control Board 1.3, connect the button to "PWR Trigger (IO13)" and "GND" of the "Fake PWR" connector.

On the Switch Board, connect the button to "IN" and "3_3V" of the "TIME TRAVEL" connector.

### Adapting the firmware to your gauges

The MCP4728 can deliver up to 5V. Since your gauges probably will not cover exactly this voltage spread, the firmware can be adapted to limit the maximum voltage put out. This is done in dg_main.c, and there are some examples listed there. You can, of course, contact me if you need assistance with the firmware. *In fact, I would like to know about your hardware and include your specific type to the list, so that you don't have to patch stuff on firmware updates.*

### Connecting a TCD to the Dash Gauges by wire

If you want to connect a TCD to the Dash Gauges by wire (such as mentioned [here](https://github.com/realA10001986/Dash-Gauges/tree/main#connecting-a-tcd-by-wire)), you have two options on the Dash Gauges' side: Either the Control Board, or the Switch Board. 

When connecting to the Dash Gauges' Control Board, there are four possible configurations, depending which version of the TCD control board you are using the both the Dash Gauges as well as the TCD itself:

<table>
    <tr>
     <td align="center">Dash Gauges:<br>Control board 1.2</td>
     <td align="center">Dash Gauges:<br>Control board 1.3</td>
     <td align="center">TCD with control board 1.2</td>
     <td align="center">TCD with control board 1.3</td>
    </tr>
   <tr>
     <td align="center">GND of "IO13" connector</td>
     <td align="center">GND of "Fake PWR" connector</td>
     <td align="center">GND of "IO14" connector</td>
     <td align="center">GND on "Time Travel" connector</td>
    </tr>
    <tr>
     <td align="center">IO13 of "IO13" connector</td>
     <td align="center">"PWR Trigger (IO13)" of "Fake PWR" connector</td>
     <td align="center">IO14 of "IO14" connector</td>
     <td align="center">TT OUT on "Time Travel" connector</td>
    </tr>
</table>

For when connecting to the Switch Board, here are only two ways, depending on which Control Board you are using in your TCD:

<table>
    <tr>
     <td align="center">Dash Gauges:<br>Switch Board</td>
     <td align="center">TCD with control board 1.2</td>
     <td align="center">TCD with control board 1.3</td>
    </tr>
   <tr>
     <td align="center">GND of "TIME TRAVEL" connector</td>
     <td align="center">GND of "IO14" connector</td>
     <td align="center">GND on "Time Travel" connector</td>
    </tr>
    <tr>
     <td align="center">IN of "TIME TRAVEL" connector</td>
     <td align="center">IO14 of "IO14" connector</td>
     <td align="center">TT OUT on "Time Travel" connector</td>
    </tr>
</table>


