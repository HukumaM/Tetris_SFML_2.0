#include "AssetManager.hpp"

namespace Engine
{
    std::map<int16_t, std::string> AssetManager::asset_path{
        {0x01, "assets/textures/tiles_seas.png"},
        {0x02, "assets/textures/tiles_seas_shadow.png"},
        {0x03, "assets/textures/tiles_rainbow.png"},
        {0x04, "assets/textures/tiles_rainbow_shadow.png"},
        {0x05, "assets/textures/tiles.png"},
        {0x06, "assets/textures/tiles_shadow.png"},
        {0x07, "assets/textures/background.jpg"},
        {0x08, "assets/textures/digits.png"},
        {0x09, "assets/textures/game_over.png"},
        {0x0A, "assets/fonts/Oswald-Regular.ttf"},
        {0x0B, "assets/audio/title.ogg"},
        {0x0C, "assets/audio/a_type_music.ogg"},
        {0x0D, "assets/audio/b_type_music.ogg"},
        {0x0E, "assets/audio/c_type_music.ogg"},
        {0x0F, "assets/audio/game_over.ogg"},
        {0x10, "assets/audio/fall.wav"},
        {0x11, "assets/audio/line.wav"},
        {0x12, "assets/audio/selection.wav"},
        {0x13, "assets/audio/stage_clear.ogg"}};

    std::map<int16_t, std::unique_ptr<sf::Music>> AssetManager::music{};
    std::map<int16_t, std::unique_ptr<sf::Sound>> AssetManager::sounds{};
    std::map<int16_t, std::unique_ptr<sf::SoundBuffer>> AssetManager::sound_buffer{};

    namespace Colors
    {
        sf::Color letter = sf::Color(240, 245, 205);
        sf::Color button = sf::Color(40, 40, 60);
        sf::Color selected_button = sf::Color(40, 40, 100);
        sf::Color background = sf::Color(0, 40, 60);
    }
    
    void
    AssetManager::loadTexture(int16_t id, const std::string &file_path,
                              bool want_repeated)
    {
        auto texture = std::make_unique<sf::Texture>();

        if (texture->loadFromFile(file_path))
        {
            texture->setRepeated(want_repeated);
            textures[id] = std::move(texture);
        }
        else
        {
            throw std::runtime_error("Failed to load image \"" + file_path +
                                     "\". Reason: Unable to open file");
        }
    }

    const sf::Texture &
    AssetManager::getTexture(int16_t id) const
    {
        return *(textures.at(id).get());
    }

    const std::pair<sf::Texture, sf::Texture> &
    AssetManager::getTileTexture() const
    {
        return texture_tile;
    }

    void
    AssetManager::setTileTexture(int16_t id)
    {
        texture_tile.first = *(textures.at(id).get());
        texture_tile.second = *(textures.at(++id).get());
    }

    void
    AssetManager::loadFont(int16_t id, const std::string &file_path)
    {
        auto font = std::make_unique<sf::Font>();

        if (font->loadFromFile(file_path))
        {
            fonts[id] = std::move(font);
        }
        else
        {
            throw std::runtime_error("Failed to load font \"" + file_path +
                                     "\". Reason: Unable to open file");
        }
    }

    const sf::Font &
    AssetManager::getFont(int16_t id) const
    {
        return *(fonts.at(id).get());
    }

    void
    AssetManager::loadMusic(int16_t id, const std::string &file_path, bool loop_it)
    {
        auto pmusic = std::make_unique<sf::Music>();

        if (pmusic->openFromFile(file_path))
        {
            music[id] = std::move(pmusic);
            music[id]->setLoop(loop_it);
        }
        else
        {
            throw std::runtime_error("Failed to load music file \"" + file_path +
                                     "\". Reason: Unable to open file");
        }
    }

    void
    AssetManager::changeMusicVolume(int16_t value)
    {
        for (auto &music_t : music)
        {
            music_t.second->setVolume(value);
        }
    }

    void
    AssetManager::playMusic(int16_t id)
    {
        if (music.at(id)->getStatus() != sf::SoundSource::Status::Playing)
        {
            music.at(id)->play();
        }
    }

    void
    AssetManager::stopMusic(int16_t id)
    {
        music.at(id)->stop();
    }

    void
    AssetManager::pauseMusic(int16_t id)
    {
        music.at(id)->pause();
    }

    void
    AssetManager::loadSound(int16_t id, const std::string &file_path)
    {
        auto psound_buffer = std::make_unique<sf::SoundBuffer>();
        auto sound = std::make_unique<sf::Sound>();

        if (psound_buffer->loadFromFile(file_path))
        {
            sound_buffer[id] = std::move(psound_buffer);
            sound->setBuffer(*(sound_buffer.at(id).get()));
            sounds[id] = std::move(sound);
        }
        else
        {
            throw std::runtime_error("Failed to load sound file \"" + file_path +
                                     "\". Reason: Unable to open file");
        }
    }

    void
    AssetManager::changeSoundVolume(int16_t value)
    {
        for (auto &sound_t : sounds)
        {
            sound_t.second->setVolume(value);
        }
    }

    void
    AssetManager::playSound(int16_t id)
    {
        sounds.at(id)->play();
    }

} // namespace Engine