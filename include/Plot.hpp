# pragma once
#include <SFML/Graphics.hpp>

/**
 * @brief Does all the drawings
 */

class Plot
{
public:
    Plot(sf::string title, int voltage, double time_t& );
    
    virtual ~Plot();

private:

    void update(int time_t);
    void drawOn (sf::RenderTarget& targetWindow) const;
    
     
};

