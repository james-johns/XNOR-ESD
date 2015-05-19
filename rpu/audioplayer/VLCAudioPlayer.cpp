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
  vlc = libvlc_new(0, NULL); //Create VLC instance

  std::string url = "rtsp://";
  url += (ipaddr != NULL) ? ipaddr : "127.0.0.1";
  url += ":5540/test";
  
  vlc_m = libvlc_media_new_location(vlc, url.c_str());
  vlc_mp = libvlc_media_player_new_from_media(vlc_m);
  
  libvlc_media_release(vlc_m);
}

/*! VLCAudioPlayer::VLCAudioPlayer(const char *ipaddr)
 * @author Rob Shepherd
 * @brief VLCAudioPlayer destructor
 *
 * @details Stops playback and releases media player and vlc instances
 */
VLCAudioPlayer::~VLCAudioPlayer()
{
  libvlc_media_player_stop(vlc_mp);
  libvlc_media_player_release(vlc_mp);
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


/*! VLCAudioPlayer::stop()
 * @author Rob Shepherd
 * @brief Stop playback
 *
 * @details Stop the VLC media player
 */
void VLCAudioPlayer::stop()
{
  libvlc_media_player_stop(vlc_mp);
}

/*! VLCAudioPlayer::pause()
 * @author Rob Shepherd
 * @brief Pause playback
 *
 * @details Toggles pausing the VLC media player's playback
 */
void VLCAudioPlayer::pause()
{
  libvlc_media_player_pause(vlc_mp);
}

/*! VLCAudioPlayer::play()
 * @author Rob Shepherd
 * @brief Begin / resume playback
 *
 * @details Start media player playback
 */
void VLCAudioPlayer::play()
{
  libvlc_media_player_play(vlc_mp);
}

/*! VLCAudioPlayer::playpause()
 * @author Rob Shepherd
 * @brief Toggle between play and pause
 *
 */
void VLCAudioPlayer::playpause()
{
  pause(); //VLC function already toggles pause
}

/*! VLCAudioPlayer::isPlaying()
 * @author Rob Shepherd
 * @brief Check if the media player is playing
 * @returns True if media player is playing, else false.
 */
bool VLCAudioPlayer::isPlaying()
{
  return libvlc_media_player_is_playing(vlc_mp) == 1;
}

/*! VLCAudioPlayer::rewind()
 * @author Rob Shepherd
 * @brief Rewind the media palyer playback
 *
 * @details rewind playback by 5 seconds, or to the beginning of the track; 
 */
void VLCAudioPlayer::rewind()
{
  libvlc_time_t currentTime = libvlc_media_player_get_time(vlc_mp); //Time in ms
  libvlc_time_t targetTime;

  if(currentTime < 5000)
    targetTime = 0;
  else
    targetTime = currentTime - 5000;
    
  libvlc_media_player_set_time(vlc_mp, targetTime);
}

void VLCAudioPlayer::fastForward()
{
  libvlc_time_t currentTime = libvlc_media_player_get_time(vlc_mp);
  libvlc_time_t targetTime;

  targetTime = currentTime + 5000;

  libvlc_media_player_set_time(vlc_mp, targetTime);
}
