#ifndef STEERINGSFEST_SCENE_HPP
#define STEERINGSFEST_SCENE_HPP


#include <vector>
#include <SFML/Graphics/RenderWindow.hpp>
#include "Vehicle.hpp"
#include "Track.hpp"
#include "elements/Boid.hpp"

class Scene {
private:
    std::vector<Boid*> vehicles;
    Track track;

public:
    Scene(Vector2 circuit[], int size);
    ~Scene();

    void addVehicle(int x, int y);

    void handleVehiclesCollisions();
    void updateVehiclesPositions();

    void update();
    void draw(sf::RenderWindow* window);
};


#endif //STEERINGSFEST_SCENE_HPP
