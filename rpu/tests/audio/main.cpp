
#include <stdio.h>
#include <unistd.h>
#include <iostream>

#include <VLCAudioPlayer.h>

int main()
{
  AudioPlayer *player = new VLCAudioPlayer("127.0.0.1");

  player->play();

  while(1) 
    {
      printf("%d\n", player->isPlaying());
      sleep(1);
    }

  return 0;
}
