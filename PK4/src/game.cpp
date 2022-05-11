#include "game.h"
#include "gameOver.h"
#include "additionalUtilities.h"

Game::Game(sf::Font &f):
    font(f), data(),
    player(data.getPlayerTexture(), data.getPlayerImmortalTexture(), data.getPlayerBulletsTypes(), data.getPlayerBulletsCooldown()),
    bar(f), state(Game::states::PLAY),
    spawner(data, enemies, power_ups, bar),
    collisions_manager(enemies, bullets, power_ups, player, bar)
{}

void Game::run(sf::RenderWindow &window)
{
    sf::Clock clock;
    sf::Mouse::setPosition(sf::Vector2i(GAME_WIDTH/2, SCREEN_HEIGHT - 50), window);
    window.setMouseCursorVisible(false);
    do
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed ||
                (event.type == sf::Event::KeyPressed &&
                    event.key.code == sf::Keyboard::Escape))
                state = states::EXIT;
        }
        float elapsed_time = clock.restart().asSeconds();
        bar.update(elapsed_time);
        for(auto &e : enemies)
            e->update(bullets, elapsed_time);
        for(auto &b : bullets)
            b->update(elapsed_time);
        for(auto &p : power_ups)
            p.update(elapsed_time);
        spawner.spawn(bar.getScore(), elapsed_time);
        player.update(sf::Mouse::getPosition(window), bullets, elapsed_time);
        if(collisions_manager.check() == CollisionStatus::PLAYER_DEAD)
            state = states::OVER;
        draw(window);
    }while(state == states::PLAY);
    window.setMouseCursorVisible(true);
    if(state == states::OVER)
        GameOver(font, bar.getScore()).display(window);
}

void Game::draw(sf::RenderWindow &window)
{
    window.clear();
    std::vector<PowerUp>::iterator power_ups_end = power_ups.end();
    for(auto pu = power_ups.begin(); pu != power_ups_end; pu++)
        window.draw(*pu);
    std::vector<std::shared_ptr<Enemy>>::iterator enemies_end = enemies.end();
    for(auto e = enemies.begin(); e != enemies_end; e++)
        window.draw(**e);
    std::vector<std::shared_ptr<Bullet>>::iterator bullets_end = bullets.end();
    for(auto b = bullets.begin(); b != bullets_end; b++)
        window.draw(**b);
    window.draw(player);
    window.draw(bar);
    window.display();
}
