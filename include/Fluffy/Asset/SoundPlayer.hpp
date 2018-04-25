//
// Fluffy
// @author Lo-X
// @website http://www.loicboutter.fr
// @copyright 2016 All rights reserved
// File created by loic on 20/04/18.
//

#ifndef FLUFFY_SOUNDPLAYER_HPP
#define FLUFFY_SOUNDPLAYER_HPP

#include <Fluffy/Asset/AssetHolder.hpp>
#include <Fluffy/Utility/NonCopyable.hpp>
#include <SFML/Audio/Listener.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <list>
#include <string>

namespace Fluffy {
namespace Asset {

template <typename Identifier>
class SoundPlayer : public Fluffy::Utility::NonCopyable
{
public:
    typedef AssetHolder<sf::SoundBuffer, Identifier> SoundHolder;
    static constexpr float ListenerZ     = 300.f;
    static constexpr float Attenuation   = 8.f;
    static constexpr float MinDistance2D = 200.f;
    static constexpr float MinDistance3D = 360.f; //std::sqrt(MinDistance2D * MinDistance2D + ListenerZ * ListenerZ);

public:
    SoundPlayer() = default;

    void load(Identifier id, const std::string& filename);

    void play(Identifier id);
    void play(Identifier id, sf::Vector3f position, float pitch = 1.f);

    void removeStoppedSounds();
    void setListenerPosition(sf::Vector3f position);
    sf::Vector3f getListenerPosition() const;

private:
    SoundHolder          mSoundBuffers;
    std::list<sf::Sound> mSounds;
};

#include <Fluffy/Asset/SoundPlayer.inl>
}
}

#endif //FLUFFY_SOUNDPLAYER_HPP
