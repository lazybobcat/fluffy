//
// Fluffy
// @author Lo-X
// @website http://www.loicboutter.fr
// @copyright 2016 All rights reserved
// File created by loic on 20/04/18.
//

#ifndef FLUFFY_MUSICPLAYER_HPP
#define FLUFFY_MUSICPLAYER_HPP

#include <Fluffy/Utility/NonCopyable.hpp>
#include <SFML/Audio/Music.hpp>
#include <map>
#include <string>

namespace Fluffy {
namespace Asset {

template <typename Identifier>
class MusicPlayer : public Fluffy::Utility::NonCopyable
{
public:
    MusicPlayer();

    void load(Identifier song, const std::string& file);

    void play(Identifier song, bool loop = true);
    void stop();
    void pause(bool flag = true);
    void setVolume(float volume);

private:
    sf::Music mMusic;
    float     mVolume;
    std::map<Identifier, std::string> mLibrary;
};

#include <Fluffy/Asset/MusicPlayer.inl>
}
}

#endif //FLUFFY_MUSICPLAYER_HPP
