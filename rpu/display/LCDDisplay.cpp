

#include <LCDDisplay.h>

LCDDisplay::LCDDisplay() : Display()
{

}

LCDDisplay::~LCDDisplay()
{

}

void LCDDisplay::refresh()
{
  /* char displayOptionMode[1] = {254};//Special character to enable option mode
  char blockNumber1[1]={128};//first character of the display
  char blockNumber2[1]={129};//2nd character of the display
  char blockNumber3[1]={137};//10th character of the display
  char blockNumber4[1]={192};//17th character of the display
  char blockNumber5[1]={200}//25th character of the display
  
  write(displayDevice,displayOptionMode,sizeof(displayOptionMode));
  write(displayDevice,blockNumber1,sizeof(blockNumber1));
  write(displayDevice,displayContent1,sizeof(displayContent1));

  write(displayDevice,displayOptionMode,sizeof(displayOptionMode));
  write(displayDevice,blockNumber2,sizeof(blockNumber2));
  write(displayDevice,displayContent2,sizeof(displayContent2));

  rite(displayDevice,displayOptionMode,sizeof(displayOptionMode));
  write(displayDevice,blockNumber3,sizeof(blockNumber3));
  write(displayDevice,displayContent3,sizeof(displayContent3));

  write(displayDevice,displayOptionMode,sizeof(displayOptionMode));
  write(displayDevice,blockNumber5,sizeof(blockNumber5));
  write(displayDevice,displayContent5,sizeof(displayContent5));
  */
}

