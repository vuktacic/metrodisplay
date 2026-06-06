# MD Journal

## June 5th, 2026

Started working on my project. This has been on my mind for quite a while: an led matrix board that displays subway timetables.

I've seen quite a few projects of this online, but they all use low resolution led matrices, or use them from overpriced suppliers (sorry adafruit).

First thing I did was find the led matrix I wanted to use. I found a 128x64 led matrix on aliexpress for ~$35CAD. Sounds expensive, but a 64x32 from adafruit is twice as expensive for 1/4th the pixels, so I think it's a pretty sweet deal.

![](./assets/2026-06-05_22-10-36.png)

I then built a schematic centered around my esp32 devboard to run this display.

The matrix uses a 2x8 IDC pinout, presumed to be 2.54mm pitch. I added a button for control, an led for status, level shifters for the data lines (to upgrade the 3.3V logic from the esp32 to 5V for the display), and lots and lots of decoupling capacitors (including a BEEFY 2200uF cap for the display).

![](./assets/2026-06-05_22-06-23.png)

As you can see the level shifting schematic is a bit of a mess because of how many lines there are. I added solder jumpers just in case I'm unable to use the level shifters, and the display still works with 3.3V logic.

About that capacitor: I found several boxes full of these in my school's shops (I'm talking maybe 100+ of these things). I don't think they've ever been used for something other than students blowing them up for fun, so I'm pretty excited to have a practical usecase for one of them.

![](./assets/image.png)


I then assigned footprints and brought everything into the editor. (No errors!). I set a 100mmx100mm box (JLC price limit), and started arranging the components. I wasn't worried about precise alignments, as the goal was just to see if everything could fit nicely.

![](./assets/2026-06-05_22-06-08.png)

Well, there is quite a lot of room there. I will still need to add vias for some of the solder jumpers though.

I also put down 5mm wide traces for the led 5v/gnd rails. Overkill? Yeah. But I'm not taking any chances when this matrix flicks on and pulls a billion amps.

In the following days I'll put down the actual aligned placements of all of these components, and then start routing. After that, I'll design the case for the pcb and display, and then write the firmware for it (I'm considering a webserver).

Time today: 6.0 hours  
**Time total: 6.0 hours**  
_(I'm probably going to include lapse links from now on.)_