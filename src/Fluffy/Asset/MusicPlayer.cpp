//
// Fluffy
// @author Lo-X
// @website http://www.loicboutter.fr
// @copyright 2016 All rights reserved
// File created by loic on 20/04/18.
//

#include <Fluffy/Asset/MusicPlayer.hpp>

using namespace Fluffy::Asset;

template <typename Identifier>
MusicPlayer<Identifier>::MusicPlayer()
  : mMusic()
  , mVolume(100.f)
  , mLibrary()
{
}

template <typename Identifier>
void MusicPlayer<Identifier>::stop()
{
    mMusic.stop();
}

template <typename Identifier>
void MusicPlayer<Identifier>::pause(bool flag)
{
    if (flag) {
        mMusic.pause();
    } else {
        mMusic.play();
    }
}

template <typename Identifier>
void MusicPlayer<Identifier>::setVolume(float volume)
{
    mVolume = volume;
    mMusic.setVolume(mVolume);
}
