#include "sidebar.h"
#include <string>

#include "constants.h"

Sidebar::Sidebar(sf::Font &f):
    font(f),
    score(0),
    game_time(0),
    fps_timer(0),
    fps(0),
    game_name_label(" Space\nShooter", f, sf::Vector2i(GAME_WIDTH + SIDEBAR_WIDTH/2, 80), 0.5, 30),
    boss_bg(sf::Vector2f(SIDEBAR_WIDTH - 20, BOSS_BAR_HEIGHT)),
    score_label(
        "Score\n",
        f,
        sf::Vector2i(GAME_WIDTH + 10, SCREEN_HEIGHT - 150),
        0, 16, sf::Color::White, std::string(SCORE_DIGITS, '0')
    ),
    hp_label(
        "Health:\n",
        f,
        sf::Vector2i(GAME_WIDTH + 10, SCREEN_HEIGHT - 100),
        0, 16, sf::Color::White, std::to_string(START_HEALTH)
    ),
    time_label(
        "Game time:\n",
        f,
        sf::Vector2i(GAME_WIDTH + 10, SCREEN_HEIGHT - 60),
        0, 16, sf::Color::White, "0"
    ),
    fps_label(
        "Fps: ",
        f,
        sf::Vector2i(GAME_WIDTH + 10, SCREEN_HEIGHT - 20),
        0, 12, sf::Color::Yellow, "0"
    ),
    rectangle(sf::Vector2f(SCREEN_WIDTH - GAME_WIDTH, SCREEN_HEIGHT))
{
    rectangle.setPosition(GAME_WIDTH, 0);
    rectangle.setFillColor(sf::Color(47, 47, 47));
    rectangle.setOutlineColor(sf::Color::White);
    rectangle.setOutlineThickness(2);

    boss_bg.setPosition(GAME_WIDTH + 10, 150);
    boss_bg.setFillColor(sf::Color::Black);
    boss_bg.setOutlineColor(sf::Color::Red);
    boss_bg.setOutlineThickness(2);

    boss_fg.setPosition(GAME_WIDTH + 10, 150);
    boss_fg.setFillColor(sf::Color::Red);
}

void Sidebar::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(rectangle);
    target.draw(game_name_label);
    if(!boss.expired())
    {
        target.draw(boss_bg);
        target.draw(boss_fg);
    }
    target.draw(hp_label);
    target.draw(score_label);
    target.draw(time_label);
    target.draw(fps_label);
}

void Sidebar::update(float elapsed_time)
{
    game_time += elapsed_time;
    fps_timer += elapsed_time;
    time_label.updateData(std::to_string((int)game_time));
    fps++;
    if(fps_timer >= 1)
    {
        fps_label.updateData(std::to_string(fps));
        fps = 0;
        fps_timer -= 1;
    }
    updateBossHp();
}

void Sidebar::updateBossHp()
{
    if(boss.expired())
        return;
    std::shared_ptr<Boss> b = std::dynamic_pointer_cast<Boss>(boss.lock());
    float hp = b->getHp();
    float max_hp = b->getMaxHp();
    boss_fg.setSize(sf::Vector2f(boss_bg.getSize().x * hp / max_hp, BOSS_BAR_HEIGHT));
}

void Sidebar::updateHp(Player &p)
{
    hp_label.updateData(std::to_string(p.getHealth()));
}

void Sidebar::updateScore(int points)
{
    score += points;
    std::string s = std::to_string(score);
    score_label.updateData(std::string(SCORE_DIGITS - s.length(), '0') + s);
}

void Sidebar::setBoss(std::shared_ptr<Enemy> b)
{
    boss = b;
}

int Sidebar::getScore()
{
    return score;
}
