#include <Adafruit_NeoPixel.h>

#define ColorPin 19
#define ColorButtonPin 3
const int ColorModes = 17;
uint8_t  colorMode   = 0; // Current Color

int ColorButtonPreviousState=HIGH;

//The class which keeps track of RGB values
class Color3
{
  public:int R;
  public:int G;
  public:int B;

  public:int FadeToR;
  public:int FadeToG;
  public:int FadeToB;

  public: Color3()
  {
  }
  
  public: SetColor(int r, int g, int b)
    {
    R=r;
    G=g;
    B=b;
  }
  public: SetFadeToColor(int r, int g, int b)
    {
    FadeToR=r;
    FadeToG=g;
    FadeToB=b;
  }
    public: Fade()
    {
      if(R<FadeToR)
      R++;
      if(R>FadeToR)
      R--;
      if(G<FadeToG)
      G++;
      if(G>FadeToG)
      G--;
      if(B<FadeToB)
      B++;
      if(B>FadeToB)
      B--;
  }

  public: bool EqualsColor(int r, int g, int b)
  {
    if(r != R)
      return false;
    if(g != G)
      return false;
    if(b != B)
      return false;
    return true;
  }

    public: SetColor(uint32_t rgb)
  {
    SetColor(((rgb >> 16) & 0xFF) / 255.0,((rgb >> 8) & 0xFF) / 255.0,((rgb) & 0xFF) / 255.0);
  }
    public: SetFadeToColor(int rgb)
  {
    SetFadeToColor(((rgb >> 16) & 0xFF) / 255.0,((rgb >> 8) & 0xFF) / 255.0,((rgb) & 0xFF) / 255.0);
  }
    public: bool EqualsColor(int rgb)
  {
  EqualsColor(((rgb >> 16) & 0xFF) / 255.0,((rgb >> 8) & 0xFF) / 255.0,((rgb) & 0xFF) / 255.0);
  }
};

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(32, ColorPin);
Color3 Color = Color3();
bool rbFade =false;
bool biFade =false;
bool prideFade =false;
bool americaFade =false;
bool rbClick =false;
bool biClick =false;
bool prideClick =false;
bool americaClick =false;
int delaySpeed = 10;
int clickSpeed = 400;
int delayEnd = 0; //Millisecond at which the delay ends. 

void setDelay(int delayLength)
{
delayEnd= millis() + delayLength;
}

bool checkDelay()
{
  if (delayEnd <= millis())
  {
    return true;
  }
  return false;
}
void setup() {
  //Setup Color Button
  pinMode(ColorButtonPin, INPUT_PULLUP);

  pixels.begin();
  pixels.show();

}

void loop() {
//Read the color button
 int ColorButtonCurrentState = digitalRead(ColorButtonPin);
//If the button has been pressed change the color
 if(ColorButtonCurrentState!=ColorButtonPreviousState)//State changed
 {
   ColorButtonPreviousState=ColorButtonCurrentState;
      if(ColorButtonCurrentState == LOW) //Button Pressed
      {
      colorMode++;
      if(colorMode >= ColorModes)
        {
        colorMode=0;
        }
      }
 }

//Color3* Color = new Color3();
//Set the color
switch (colorMode) 
{
  case 0: //red
  prideFade=false;
  Color.SetColor(255,0,0);
  break;

  case 1: //orange
  Color.SetColor(255,165,0);
  break;

  case 2: //Yellow
  Color.SetColor(255,255,0);
  break;

  case 3: //Green
  Color.SetColor(0,255,0);
  break;

  case 4: //Cyan
  Color.SetColor(0,255,255);
  break;

  case 5: //Blue
  Color.SetColor(0,0,255);
  break;

  case 6: //Fuschia
  Color.SetColor(255,0,255);
  break;

  case 7: //Pink
  Color.SetColor(255,20,147);
  break;

  case 8: //White
  Color.SetColor(255,255,255);
  break;

  case 9: //Red-> Blue fade
  if(checkDelay())
  {
    if(rbFade==false)
    {
      Color.SetColor(255,0,0);
      Color.SetFadeToColor(0,0,255);
      rbFade=true;
      setDelay(delaySpeed);
    }
    else
    {
      Color.Fade();
      if(Color.EqualsColor(0, 0, 255)) //If blue fade to red
        Color.SetFadeToColor(255,0,0);
      else if(Color.EqualsColor(255, 0, 0)) //if red fade to blue
        Color.SetFadeToColor(0,0,255);
      setDelay(delaySpeed);
    }
  }
  break;

  case 10: //Bi Flag
  if(checkDelay())
  {
    rbFade=false;
    if(biFade==false)
    {
      Color.SetColor(209,0,110); //pink
      Color.SetFadeToColor(153,78,149); //purple
      biFade=true;
      setDelay(delaySpeed);
    }
    else
    {
      Color.Fade();
      if(Color.EqualsColor(8,57,167)) //If blue fade to pink
        Color.SetFadeToColor(209,0,110);
      else if(Color.EqualsColor(209,0,110)) //if pink fade to purple
        Color.SetFadeToColor(153,78,149);
      else if(Color.EqualsColor(153,78,149)) //if purple fade to blue
        Color.SetFadeToColor(8,57,167);
      setDelay(delaySpeed);
    }
  }
  break;

  case 11: //Pride Flag
  if(checkDelay())
  {
    biFade=false;
    if(prideFade==false)
    {
      Color.SetColor(255,0,0); //red
      Color.SetFadeToColor(255,165,0); //Orange
      prideFade=true;
      setDelay(delaySpeed);
    }
    else
    {
      Color.Fade();
      if(Color.EqualsColor(255,165,0)) //If orange fade to yellow
        Color.SetFadeToColor(255,255,0);
      else if(Color.EqualsColor(255,255,0)) //if yellow fade to green
        Color.SetFadeToColor(0,255,0);
      else if(Color.EqualsColor(0,255,0)) //if green fade to cyan
        Color.SetFadeToColor(0,255,255);
      else if(Color.EqualsColor(0,255,255)) //if cyan fade to blue
        Color.SetFadeToColor(0,0,255);
      else if(Color.EqualsColor(0,0,255)) //if blue fade to fuschia
        Color.SetFadeToColor(255,0,255);
      else if(Color.EqualsColor(255,0,255)) //if fuschia fade to red
        Color.SetFadeToColor(255,0,0);
      else if(Color.EqualsColor(255,0,0)) //if red fade to orange
        Color.SetFadeToColor(255,165,0);
      setDelay(delaySpeed);
    }
  }
  break;

  case 12: //America!
  if(checkDelay())
  {
    prideFade=false;
    if(americaFade==false)
    {
      Color.SetColor(255,0,0); //red
      Color.SetFadeToColor(255,255,255); //white
      americaFade=true;
      setDelay(delaySpeed);
    }
    else
    {
      Color.Fade();
      if(Color.EqualsColor(255,255,255)) //If white fade to blue
        Color.SetFadeToColor(0,0,255);
      else if(Color.EqualsColor(0,0,255)) //if blue fade to red
        Color.SetFadeToColor(255,0,0);
      else if(Color.EqualsColor(255,0,0)) //if red fade to white
        Color.SetFadeToColor(255,255,255);
      setDelay(delaySpeed);
    }
  }
  break;

  case 13: //Red Blue Click
  if(checkDelay())
  {
    americaFade =false;
    if(rbClick==false)
    {
      Color.SetColor(255,0,0); //pink
      rbClick=true;
      setDelay(clickSpeed);
    }
    else
    {
      if(Color.EqualsColor(255,0,0)) //If red click to blue
        Color.SetColor(0,0,255);
      else if(Color.EqualsColor(0,0,255)) //blue click to red
        Color.SetColor(255,0,0);
      setDelay(clickSpeed);
    }
  }
    break;

  case 14: //Bi Flag Click
  if(checkDelay())
  {
    rbClick=false;
    if(biClick==false)
    {
      Color.SetColor(209,0,110); //pink
      biClick=true;
      setDelay(clickSpeed);
    }
    else
    {
      if(Color.EqualsColor(8,57,167)) //If blue Click to pink
        Color.SetColor(209,0,110);
      else if(Color.EqualsColor(209,0,110)) //if pink Click to purple
        Color.SetColor(153,78,149);
      else if(Color.EqualsColor(153,78,149)) //if purple Click to blue
        Color.SetColor(8,57,167);
      setDelay(clickSpeed);
    }
  }
  break;

  case 15: //Pride Flag
  if(checkDelay())
  {
    biClick=false;
    if(prideClick==false)
    {
      Color.SetColor(255,0,0); //red
      prideClick=true;
      setDelay(clickSpeed);
    }
    else
    {
      if(Color.EqualsColor(255,165,0)) //If orange Click to yellow
        Color.SetColor(255,255,0);
      else if(Color.EqualsColor(255,255,0)) //if yellow Click to green
        Color.SetColor(0,255,0);
      else if(Color.EqualsColor(0,255,0)) //if green Click to cyan
        Color.SetColor(0,255,255);
      else if(Color.EqualsColor(0,255,255)) //if cyan Click to blue
        Color.SetColor(0,0,255);
      else if(Color.EqualsColor(0,0,255)) //if blue Click to fuschia
        Color.SetColor(255,0,255);
      else if(Color.EqualsColor(255,0,255)) //if fuschia Click to red
        Color.SetColor(255,0,0);
      else if(Color.EqualsColor(255,0,0)) //if red Click to orange
        Color.SetColor(255,165,0);
      setDelay(clickSpeed);
    }
  }
  break;

  case 16: //America!
  if(checkDelay())
  {
    prideClick=false;
    if(americaClick==false)
    {
      Color.SetColor(255,0,0); //red
      americaClick=true;
      setDelay(clickSpeed);
    }
    else
    {
      if(Color.EqualsColor(255,255,255)) //If white Click to blue
        Color.SetColor(0,0,255);
      else if(Color.EqualsColor(0,0,255)) //if blue Click to red
        Color.SetColor(255,0,0);
      else if(Color.EqualsColor(255,0,0)) //if red Click to white
        Color.SetColor(255,255,255);
      setDelay(clickSpeed);
    }
  }
  break;

}
  pixels.setPixelColor(0,Color.R,Color.G,Color.B);
  pixels.show();
}
