#ifndef SIDEBAR
#define SIDEBAR

#include <SFML/Graphics.hpp>
#include <memory>

#include "labels.h"
#include "player.h"
#include "enemies.h"

// klasa zarządzająca panelem po prawej stronie okna gry
class Sidebar: public sf::Drawable
{
    sf::Font &font;
    unsigned int score, fps;
    float game_time, fps_timer;
    DataLabel hp_label, score_label, time_label, fps_label;
    Label game_name_label;
    sf::RectangleShape rectangle, boss_bg, boss_fg;
    std::weak_ptr<Enemy> boss;

    void updateBossHp();
public:
    Sidebar(sf::Font &f);

    void update(float elapsed_time);

    void updateHp(Player &p);
    void updateScore(int points = 1);
    void setBoss(std::shared_ptr<Enemy> b);

    int getScore();

    void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};

#endif
