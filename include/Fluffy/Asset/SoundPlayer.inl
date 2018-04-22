//
// Fluffy
// @author Lo-X
// @website http://www.loicboutter.fr
// @copyright 2016 All rights reserved
// File created by loic on 20/04/18.
//

#include <Fluffy/Asset/SoundPlayer.hpp>

using namespace Fluffy::Asset;

template <typename Identifier>
void SoundPlayer<Identifier>::load(Identifier id, const std::string &file)
{
    mSoundBuffers.load(id, file);
}

template <typename Identifier>
void SoundPlayer<Identifier>::play(Identifier id)
{
    play(id, getListenerPosition());
}

template <typename Identifier>
void SoundPlayer<Identifier>::play(Identifier id, sf::Vector3f position, float pitch)
{
    mSounds.push_back(sf::Sound());
    sf::Sound& sound = mSounds.back();

    sound.setBuffer(mSoundBuffers.get(id));
    sound.setPosition(position);
    sound.setAttenuation(Attenuation);
    sound.setMinDistance(MinDistance3D);
    sound.setPitch(pitch);

    sound.play();
}

template <typename Identifier>
void SoundPlayer<Identifier>::removeStoppedSounds()
{
    mSounds.remove_if([](const sf::Sound& s) {
        return s.getStatus() == sf::Sound::Stopped;
    });
}

template <typename Identifier>
void SoundPlayer<Identifier>::setListenerPosition(sf::Vector3f position)
{
    sf::Listener::setPosition(position.x, -position.y, ListenerZ);
}

template <typename Identifier>
sf::Vector3f SoundPlayer<Identifier>::getListenerPosition() const
{
    return sf::Listener::getPosition();
}
