//------------------------------------------------------------------------------------------
//  Author      : Nikita Mashtalirov
//  Created     : 16.07.2021
//  Description : A class that manages all of the app's assets: sprites, text, and textures.
//------------------------------------------------------------------------------------------

#pragma once

#include <map>
#include <memory>
#include <string>

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>

#include <SFML/Audio/Music.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>

namespace Engine
{
    enum TextureID
    {
        Tile_Sea = 0x01,
        Tile_Sea_SDW = 0x02,

        Tile_Rainbow = 0x03,
        Tile_Rainbow_SDW = 0x04,

        Tile_Original = 0x05,
        Tile_Original_SDW = 0x06,

        Background = 0x07,
        Digits = 0x08,
        Game_Over = 0x09
    };

    enum FontID
    {
        Title_Font = 0x0A
    };

    enum MusicID
    {
        Title_Music = 0x0B,
        A_Stage = 0xC,
        B_Stage = 0xD,
        C_Stage = 0xE
    };

    enum SoundID
    {
        Game_Over_Sound = 0x0F,
        Fall = 0x10,
        Clear_Line = 0x11,
        Selection = 0x12,
        Clear_Stage = 0x13
    };

    namespace Colors
    {
        extern sf::Color letter;
        extern sf::Color button;
        extern sf::Color selected_button;
        extern sf::Color background;
    }

    class AssetManager
    {
    private:
        //  A member field that stores a map of the texture ID values and a pointer to it
        std::map<int16_t, std::unique_ptr<sf::Texture>> textures;

        std::pair<sf::Texture, sf::Texture>
            texture_tile;

        //  A member field that stores a map of the font ID values and a pointer to it
        std::map<int16_t, std::unique_ptr<sf::Font>> fonts;

        static std::map<int16_t, std::unique_ptr<sf::Music>> music;
        static std::map<int16_t, std::unique_ptr<sf::Sound>> sounds;
        static std::map<int16_t, std::unique_ptr<sf::SoundBuffer>> sound_buffer;

    public:
        AssetManager() = default;
        ~AssetManager() = default;

    public:
        /** @brief 
         * 
        */
        static std::map<int16_t, std::string> asset_path;

        /** @brief                  Loads a texture to the texture map by its ID
         *  @param  id              Texture ID
         *  @param  file_path       The path to the specified texture.
         *                          Must be specified relative to the current project folder
         *  @param  want_repeated   A flag indicating whether the texture should repeat over the entire specified rectangle
         */
        void
        loadTexture(int16_t id, const std::string &file_path, bool want_repeated = false);

        /** @brief                  Returns the texture by specified id
         *  @param  id              Texture ID
         *  @return                 Constant reference to the texture of the corresponding identifier
         */
        const sf::Texture &
        getTexture(int16_t id) const;

        /** @brief                  Returns the texture by specified id
         *  @param  id              Texture ID
         *  @return                 Constant reference to the texture of the corresponding identifier
         */
        const std::pair<sf::Texture, sf::Texture> &
        getTileTexture() const;

        /** @brief                  Returns the texture by specified id
         *  @param  id              Texture ID
         *  @return                 Constant reference to the texture of the corresponding identifier
         */
        void
        setTileTexture(int16_t id);

    public:
        /** @brief                  Loads a font to the font map by its ID
         *  @param id               Font ID
         *  @param file_path        The path to the specified font.
         *                          Must be specified relative to the current project folder
         */
        void
        loadFont(int16_t id, const std::string &file_path);

        /** @brief                  Returns the font by specified id
         *  @param  id              Font ID
         *  @return                 Constant reference to the font of the corresponding identifier
         */
        const sf::Font &
        getFont(int16_t id) const;

    public:
        void
        loadMusic(int16_t id, const std::string &file_path, bool loop_it = false);

        // static sf::Music &
        // getMusic(int16_t id);

        void
        changeMusicVolume(int16_t value = 10);

        void
        playMusic(int16_t id);

        void
        stopMusic(int16_t id);

        void
        pauseMusic(int16_t id);

    public:
        void
        loadSound(int16_t id, const std::string &file_path);

        // static sf::Sound &
        // getSound(int16_t id);

        void
        changeSoundVolume(int16_t value = 10);

        void
        playSound(int16_t id);
    };

} //namespace Engine