/*!
 * @file VLCAudioPlayer.cpp
 * @author Rob Shepherd
 */
#include <iostream>

#include <VLCAudioPlayer.h>


/*! VLCAudioPlayer::VLCAudioPlayer(const char *ipaddr)
 * @author Rob Shepherd
 * @brief VLCAudioPlayer constructor
 *
 * @param[in] ipaddr IP Address to connect to when receiving audio
 *
 * @details Creates VLC instance and connects via RTSP on port 5540
 */
VLCAudioPlayer::VLCAudioPlayer(const char *ipaddr) : AudioPlayer(ipaddr)
{
  const char *vlc_args[] = {"-q"};
  vlc = libvlc_new(1, vlc_args); //Create VLC instance

  counter = 0;

  url = "rtsp://";
  url += "127.0.0.1";
  url += ":5540/";
  //url += ipaddr;
  
  vlc_m = libvlc_media_new_location(vlc, (url+"broadcast").c_str());
  vlc_bc = libvlc_media_player_new_from_media(vlc_m);  

  vlc_m = libvlc_media_new_location(vlc, (url+ipaddr).c_str());
  vlc_str = libvlc_media_player_new_from_media(vlc_m);
}

/*! VLCAudioPlayer::VLCAudioPlayer(const char *ipaddr)
 * @author Rob Shepherd
 * @brief VLCAudioPlayer destructor
 *
 * @details Stops playback and releases media player and vlc instances
 */
VLCAudioPlayer::~VLCAudioPlayer()
{
  libvlc_media_player_stop(vlc_str);
  libvlc_media_player_release(vlc_str);
  libvlc_media_player_stop(vlc_bc);
  libvlc_media_player_release(vlc_bc);
  libvlc_media_release(vlc_m);
  libvlc_release(vlc);	
}

/*! VLCAudioPlayer::run()
 * @author Rob Shepherd
 * @brief Run the Gstreamer pipeline
 *
 * @details Empty; no functionality required here
 */
void VLCAudioPlayer::run()
{

}

bool VLCAudioPlayer::listen()
{
  if(counter == 500) {
    if(/*libvlc_media_player_will_play(vlc_bc) &&*/ libvlc_media_player_is_playing(vlc_bc)) {
      pause(); //Stop regular streaming
      libvlc_media_player_play(vlc_bc);
      return true;
    }
    else if(!libvlc_media_player_will_play(vlc_bc)) { //Try to connect
      play(); //Continue regular streaming
      libvlc_media_player_release(vlc_bc);
      vlc_m = libvlc_media_new_location(vlc, (url+"broadcast").c_str());
      vlc_bc = libvlc_media_player_new_from_media(vlc_m);  
      libvlc_media_release(vlc_m);
      libvlc_media_player_play(vlc_bc);
      return false;
    }
    counter = 0;
  }
  else {
    counter++;
  }
}

/*! VLCAudioPlayer::stop()
 * @author Rob Shepherd
 * @brief Stop playback
 *
 * @details Stop the VLC media player
 */
void VLCAudioPlayer::stop()
{
  libvlc_media_player_stop(vlc_str);
}

/*! VLCAudioPlayer::pause()
 * @author Rob Shepherd
 * @brief Pause playback
 *
 * @details Toggles pausing the VLC media player's playback
 */
void VLCAudioPlayer::pause()
{
  if(isPlaying()) {
    libvlc_media_player_pause(vlc_str);
  }
}

/*! VLCAudioPlayer::play()
 * @author Rob Shepherd
 * @brief Begin / resume playback
 *
 * @details Start media player playback
 */
void VLCAudioPlayer::play()
{
  libvlc_media_player_play(vlc_str);
}

/*! VLCAudioPlayer::playpause()
 * @author Rob Shepherd
 * @brief Toggle between play and pause
 *
 */
void VLCAudioPlayer::playpause()
{
  libvlc_media_player_pause(vlc_str); //VLC function already toggles pause
}

/*! VLCAudioPlayer::isPlaying()
 * @author Rob Shepherd
 * @brief Check if the media player is playing
 * @returns True if media player is playing, else false.
 */
bool VLCAudioPlayer::isPlaying()
{
  return libvlc_media_player_is_playing(vlc_str);
}

/*! VLCAudioPlayer::rewind()
 * @author Rob Shepherd
 * @brief Rewind the media player playback
 *
 * @details rewind playback by 5 seconds, or to the beginning of the track; 
 */
void VLCAudioPlayer::rewind()
{
  libvlc_time_t currentTime = libvlc_media_player_get_time(vlc_str); //Time in ms
  libvlc_time_t targetTime;

  if(currentTime < 5000)
    targetTime = 0;
  else
    targetTime = currentTime - 5000;
    
  libvlc_media_player_set_time(vlc_str, targetTime);
}

void VLCAudioPlayer::fastForward()
{
  libvlc_time_t currentTime = libvlc_media_player_get_time(vlc_str);
  libvlc_time_t targetTime;

  targetTime = currentTime + 5000;

  libvlc_media_player_set_time(vlc_str, targetTime);
}
