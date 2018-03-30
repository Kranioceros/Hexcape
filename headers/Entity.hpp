/* Copyright (C) 2018 Ramiro Garay - Ignacio Fucksmann
 * You may use, distribute and modify this code under the
 * terms of the GNU GPL 3 license.
 *
 * You should have received a copy of the GPL license with
 * this file. If not, please visit the GitHub page of this project:
 * https://github.com/Kranioceros/Hexcape
 */

#ifndef ENTITY_H
#define ENTITY_H
#include <SFML/Graphics/RenderWindow.hpp>
#include <vector>

class Entity {
public:
virtual void update(float elapsed) = 0;
virtual void draw(sf::RenderWindow &w) = 0;
virtual ~Entity() {};
};

#endif

