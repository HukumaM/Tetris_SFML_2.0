#include "Tetris.hpp"
#include "MenuState.hpp"

Tetris::Tetris()
    : context(std::make_shared<Context>())
{
    context->window->create(sf::VideoMode(WIDTH, HEIGHT), "Tetris",
                            sf::Style::Titlebar | sf::Style::Close);

    context->window->setPosition(sf::Vector2i(660, 180));

    load_assets();

    context->assets->setTileTexture(Engine::TextureID::Tile_Sea);
    context->states->pushState(std::make_unique<MenuState>(context));
}

void Tetris::load_assets()
{
    using namespace Engine;
    try
    {
        context->assets->loadTexture(TextureID::Background, AssetManager::asset_path[TextureID::Background]);
        context->assets->loadTexture(TextureID::Digits, AssetManager::asset_path[TextureID::Digits]);
        context->assets->loadTexture(TextureID::Game_Over, AssetManager::asset_path[TextureID::Game_Over]);
        context->assets->loadTexture(TextureID::Tile_Original, AssetManager::asset_path[TextureID::Tile_Original]);
        context->assets->loadTexture(TextureID::Tile_Original_SDW, AssetManager::asset_path[TextureID::Tile_Original_SDW]);
        context->assets->loadTexture(TextureID::Tile_Rainbow, AssetManager::asset_path[TextureID::Tile_Rainbow]);
        context->assets->loadTexture(TextureID::Tile_Rainbow_SDW, AssetManager::asset_path[TextureID::Tile_Rainbow_SDW]);
        context->assets->loadTexture(TextureID::Tile_Sea, AssetManager::asset_path[TextureID::Tile_Sea]);
        context->assets->loadTexture(TextureID::Tile_Sea_SDW, AssetManager::asset_path[TextureID::Tile_Sea_SDW]);

        context->assets->loadMusic(MusicID::Title_Music, AssetManager::asset_path[MusicID::Title_Music], true);
        context->assets->loadMusic(MusicID::A_Stage, AssetManager::asset_path[MusicID::A_Stage]);
        context->assets->loadMusic(MusicID::B_Stage, AssetManager::asset_path[MusicID::B_Stage]);
        context->assets->loadMusic(MusicID::C_Stage, AssetManager::asset_path[MusicID::C_Stage]);

        context->assets->loadSound(SoundID::Selection, AssetManager::asset_path[SoundID::Selection]);
        context->assets->loadSound(SoundID::Clear_Line, AssetManager::asset_path[SoundID::Clear_Line]);
        context->assets->loadSound(SoundID::Clear_Stage, AssetManager::asset_path[SoundID::Clear_Stage]);
        context->assets->loadSound(SoundID::Fall, AssetManager::asset_path[SoundID::Fall]);
        context->assets->loadSound(SoundID::Game_Over_Sound, AssetManager::asset_path[SoundID::Game_Over_Sound]);

        context->assets->loadFont(FontID::Title_Font, AssetManager::asset_path[FontID::Title_Font]);
    }
    catch (std::runtime_error &error)
    {
        std::cerr << error.what() << std::endl;
        std::cerr << "The game's source files are corrupted." << std::endl;
    }
}

void Tetris::Run()
{
    //  The clock variable required to determine the elapsed time per cycle
    sf::Clock clock;
    //  A variable required to store the time elapsed since the last frame
    sf::Time time_since_last_frame{sf::Time::Zero};

    while (context->window->isOpen())
    {
        time_since_last_frame += clock.restart();
        while (time_since_last_frame > this->TIME_PER_FRAME)
        {
            time_since_last_frame -= this->TIME_PER_FRAME;
            context->states->processStateChange();
            context->states->getState()->processInput();
            context->states->getState()->update(this->TIME_PER_FRAME);
            context->states->getState()->draw();
        }
    }
}
