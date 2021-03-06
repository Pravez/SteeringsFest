//
// Created by howl on 03/10/17.
//

#include "Scene.hpp"

void Scene::draw(sf::RenderWindow *window) {
    this->track.draw(window);

    for (auto vehicle : this->vehicles) {
        vehicle->render(window);
    }
}

Scene::Scene(Vector2 circuit[], int size) : track(Track(circuit, size)) {

}

Scene::~Scene() {

}

void Scene::update() {
    for (auto v: vehicles) {
        v->update(&this->track, this->vehicles);
    }

    this->updateVehiclesPositions();
    this->handleVehiclesCollisions();
}

void Scene::handleVehiclesCollisions() {
    Vector2 offset;
    double approximateLength;
    double tempCompute;

    for (int i = 0; i < this->vehicles.size(); ++i) {
        for (int j = 0; j < this->vehicles.size(); ++j) {
            if (i != j) {
                offset = Vector2::diff(this->vehicles[j]->getCoords(), this->vehicles[i]->getCoords());
                approximateLength = offset.approximateLength();
                if (approximateLength != 0 &&
                    approximateLength <= this->vehicles[i]->getRadius() + this->vehicles[j]->getRadius() - 1) {
                    tempCompute = approximateLength * (this->vehicles[i]->getRadius() + this->vehicles[j]->getRadius());
                    this->vehicles[i]->setCoords(
                            Vector2(
                                    this->vehicles[i]->getCoords().getX() + offset.getX(),
                                    this->vehicles[i]->getCoords().getY() + offset.getY() / tempCompute));
                }
            }
        }
    }
}

void Scene::updateVehiclesPositions() {
    for (auto v : this->vehicles) {
        v->setSpeed(Vector2::add(v->getSpeed(), v->getForce()));
        double approximateLength = v->getSpeed().approximateLength();
        if (approximateLength > v->MAXSPEED) {
            v->setSpeed(Vector2::scalar(v->getSpeed(), v->MAXSPEED / approximateLength));
        }
        v->setCoords(
                Vector2(v->getCoords().getX() + v->getSpeed().getX(), v->getCoords().getY() + v->getSpeed().getY()));
    }

}

void Scene::addVehicle(int x, int y) {
    this->vehicles.push_back(new Boid(Vector2(x, y)));
    printf("Added vehicle at %d, %d\n", x, y);
}
