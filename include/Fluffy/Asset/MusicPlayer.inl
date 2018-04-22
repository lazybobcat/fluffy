//
// Fluffy
// @author Lo-X
// @website http://www.loicboutter.fr
// @copyright 2016 All rights reserved
// File created by loic on 20/04/18.
//

#include <Fluffy/Asset/MusicPlayer.hpp>
#include <cassert>

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

template <typename Identifier>
void MusicPlayer<Identifier>::load(Identifier song, const std::string &file)
{
    mLibrary[song] = file;
}

template <typename Identifier>
void MusicPlayer<Identifier>::play(Identifier song, bool loop)
{
    auto found = mLibrary.find(song);
    assert(found != mLibrary.end());

    if (!mMusic.openFromFile(mLibrary[song])) {
        throw std::runtime_error("MusicPlayer failed to load asset from file " + mLibrary[song]);
    }

    mMusic.setVolume(mVolume);
    mMusic.setLoop(loop);
    mMusic.play();
}

