#include <Adafruit_NeoPixel.h>
#ifdef __AVR_ATtiny85__ // Trinket, Gemma, etc.
  #include <avr/power.h>
#endif

#define PIN 0
#define NUMPIXELS 16
unsigned int NeoRed[NUMPIXELS];
unsigned int NeoGreen[NUMPIXELS];
unsigned int NeoBlue[NUMPIXELS];
int16_t  hue          =   0; // Initial hue around perimeter (0-1535)

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

/*add comments TBD */
void setup()
{
  pixels.begin();
  init_rainbow();
  pixels.setBrightness(100);
}

void loop()
{
    /* set ON one LED*/
    set_one_pixel();
   
    /* blink one LED */
    blink_one_pixel();

    /*set ON all*/
    set_all_pixels();

    /*blink all pixels */
    blink_all_pixels();
   
    /* spin one pixel */
    animation_spin_one();
    
    /* chase */
    animation_chase();
    
    /* rainbow */
    animation_spin_all_rainbow();
    
}

void set_one_pixel()
{
  pixels.clear();
  pixels.setPixelColor(PIN,pixels.Color(84,15,55)); //plum
  pixels.show();
  delay(1000);
}

void set_all_pixels()
{
  for(int i=0;i<NUMPIXELS;i++)
  {
    pixels.setPixelColor(i,pixels.Color(84,15,55)); //plum
    pixels.show();
    delay(50);
  }
  delay(1000);
}

void blink_one_pixel()
{
  for(int nr=0;nr<5;nr++)
  {
    pixels.clear(); 
  
    pixels.setPixelColor(PIN,pixels.Color(84,15,55)); //plum
    pixels.show();
    delay(500);
    pixels.setPixelColor(PIN,0); //off
    pixels.show();
    delay(500); 
  }
  
}

void blink_all_pixels()
{  
  //pixels.clear(); 
   for(int nr=0; nr<5; nr++)
   {
     for(int i=0;i<NUMPIXELS;i++)
    { 
        pixels.setPixelColor(i,pixels.Color(84,15,55)); //plum    
    }
    pixels.show();   
    delay(500);
    
    for(int i=0;i<NUMPIXELS;i++)
    { 
      pixels.setPixelColor(i,0); //off
    }
    
     pixels.show(); 
     delay(500);
   }

}

void animation_chase()
{
  for(int nr=0;nr<5; nr++)
  {
   for(int i=0;i<NUMPIXELS;i++)
   {
     pixels.clear();
     pixels.setPixelColor(i,pixels.Color(0,255,0));
     pixels.setPixelColor(i,pixels.Color(0,0,255));
     
     if(i<NUMPIXELS/2)
     {
        pixels.setPixelColor((NUMPIXELS/2)+i,pixels.Color(255,0,0));
     }else
     {
        pixels.setPixelColor(i-(NUMPIXELS/2),pixels.Color(255,0,0));
     }
     pixels.show();
     delay(50);   
   }
  }
}

void animation_spin_one()
{
  for(int nr=0;nr<5;nr++)
  {
   for(int i=0;i<NUMPIXELS;i++)
   {
     pixels.clear();
     pixels.setPixelColor(i,pixels.Color(0,255,0));
     pixels.show();
     delay(50);
   }
}
}

void init_rainbow()
{ 
  int h,i;
  uint8_t a;
  for(h=hue, i=0; i<NUMPIXELS; i++, h += 96) {
    a = h;
    /* take the MSB value; 6  hues in total ; this renders a glotating rainbow */
    switch((h >> 8) % 6) {
     case 0: NeoRed[i] = 255; NeoGreen[i] =   a; NeoBlue[i] = 0; break;
     case 1: NeoRed[i]  =  ~a; NeoGreen[i] = 255; NeoBlue[i] =   0; break;
     case 2: NeoRed[i]  =   0; NeoGreen[i] = 255; NeoBlue[i] =   a; break;
     case 3: NeoRed[i]  =   0; NeoGreen[i] =  ~a; NeoBlue[i] = 255; break;
     case 4: NeoRed[i] =   a; NeoGreen[i] =   0; NeoBlue[i] = 255; break;
     case 5: NeoRed[i] = 255; NeoGreen[i] =   0; NeoBlue[i] =  ~a; break;
    }
  }
  hue += 7;
  if(hue >= 1536) hue -= 1536;
  
}
void animation_spin_all_rainbow()
{ 
  for(int nr=0;nr<5;nr++)
  {
    pixels.clear();
     for(int i=0;i<NUMPIXELS;i++)
     {       
       pixels.setPixelColor(i,pixels.Color(NeoRed[i],NeoGreen[i],NeoBlue[i]));
       pixels.show();
       delay(50);
     }
     
    for(int i=0;i<NUMPIXELS-1;i++)
    {
      NeoGreen[i]=NeoGreen[i+1];
      NeoRed[i]=NeoRed[i+1];
      NeoBlue[i]=NeoBlue[i+1];
    }
    
    NeoGreen[NUMPIXELS-1]=NeoGreen[0];
    NeoRed[NUMPIXELS-1]=NeoRed[0];
    NeoBlue[NUMPIXELS-1]=NeoBlue[0];
  }
    
}
