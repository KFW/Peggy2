/* AR_scroll
   scrolls AR logo
*/

#include <Peggy2.h>

Peggy2 frame1;         // Make a frame buffer object called frame1

int scrollspeed = 75;  // higher number scrolls more slowly
int textrows = 93;    // # of rows (functionally columns) in message text/ changes with each message
unsigned long scrolltext[] = {0, 0x3FCFF0, 0x3FCFF0, 0xCC30, 0xCC30, 0xCC30, 0x4430, 0x30, 0x3FCFF0, 0x3FCFF0, 
                              0x30C000, 0x32CFF0, 0x36CFF0, 0x36C030, 0x16C030, 0x7C030, 0x7C010, 0, 0x3FCFF0, 
                              0x3FCFF0, 0x30CC30, 0x30CC30, 0x30CC30, 0x10CC30, 0xCC10, 0x3FC000, 0x3FCFFE, 0xFFE, 
                              0x3FC030, 0x3FC030, 0x30C030, 0x30CFF0, 0x30CFF0, 0x30C000, 0x304000, 0, 0x3FF000, 
                              0x3FF000, 0x30C000, 0x304000, 0, 0, 0xC000,0xF000,0xF800,0x60F800,0x7BC000,0x7F8000,
                              0x7F8000,0x7BC000,0x60F800,0xF800,0xF000,0xC000,
                              0, 0x3FC000, 
                              0x3FC000, 0xC000, 0xC000, 0xC000, 0x4000, 0, 0, 0x300000, 0x3C0000, 0x3E0000, 
                              0x3FC000, 0x3FF000, 0x7F800, 0xFE00, 0x1F00, 0x7C0, 0x2E01E0, 0x2A0070, 0x3A0018, 
                              0xC, 0x2000C, 0x3E000C, 0x2000C, 0x18, 0x3E0070, 0x2001E0, 0x2007C0, 0x1F00, 0xFE00, 
                              0x7F800, 0x1FF000, 0x3FC000, 0x3E0000, 0x3C0000, 0x300000, 0, 0
                             };
                             
void setup()                  // run once, when the sketch starts
{
    frame1.HardwareInit();    // Call this once to init the hardware. 
                              // (Only needed once, even if you've got lots of frames.)
                              
}  // End void setup()  

void loop()
{

  int leadrow = 0;
  int leadtext = 0;
  int activerow;
  int activetext;
  
  while (leadrow < 25)  // this gets us to far side of the screen since Peggy2 rows number 0-24; leadtext stays 0
  {
    frame1.Clear();            // clear framebuffer
    int countback = min(textrows,(leadrow+1));  // determine how far back in scrolltext to count
    activerow = leadrow;
    activetext = leadtext;
    for (int i = 0; i < countback; i ++)
    {
     frame1.WriteRow(activerow, scrolltext[activetext]);
     activerow--;              // since count down from lead row
     activetext++;             // since scrolltext counts up
    }                          // end for
    frame1.RefreshAll(scrollspeed);
    leadrow ++;

  } // end while
  
  leadrow = 24;  // leadrow now stays at highest row number to keep text at end of screen
  leadtext = 1;  // leadtext will now have to start counting up to get through message text
  
  while (leadtext < textrows) //
  {
    frame1.Clear(); 
    int countback = min((textrows - leadtext),25);  // determine how far back in scrolltext to count, max is 25 rows for Peggy2
    activerow = leadrow;
    activetext = leadtext;
    for (int i = 0; i < countback; i ++)
    {
     frame1.WriteRow(activerow, scrolltext[activetext]);
     activerow --;              // since count down from lead row
     activetext ++;             // since scrolltext counts up
    }                          // end for
    frame1.RefreshAll(scrollspeed); 
    leadtext ++;
  } // end while 
  
} // End void loop()
