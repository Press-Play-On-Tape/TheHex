#include "../../HexBlocks.h"
#include "../../utils/Constants.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;

void Game::renderParticles() {

    for (uint8_t i = 0; i < PARTICLE_MAX; i++) {

        Particle &particle = this->particles[i];

        if (particle.isActive()) {

            particle.update();
            uint8_t digits[5] = {};

            if (particle.render()) {

                uint8_t pSize = particle.getSize();

                switch (pSize) {

                    case 0:
                        PD::setColor(particle.getColour());
                        PD::drawRect(particle.getX(), particle.getY(), 1, 1);
                        break;

                    case 1:
                        PD::drawBitmap(particle.getX(), particle.getY(), Images::Particles_Medium[particle.getColour()]);
                        break;

                    case 2:
                        PD::drawBitmap(particle.getX(), particle.getY(), Images::Particles_Large[particle.getColour()]);
                        break;

                }

            }

        }

    }

    PD::setColor(8, 0);

}

void Game::launchParticles(const uint16_t x, const uint16_t y, const ExplosionSize explosionSize) {

    for (Particle &particle : this->particles) {

        if (!particle.isActive()) {

            switch (explosionSize) {

                case ExplosionSize::Medium:
                    particle.setX(x);
                    particle.setY(y);
                    particle.setVelX(random(-3, 5));
                    particle.setVelY(random(6));
                    particle.setCounter(random(10, 46));
                    particle.setSize(random(0, 3));
                    particle.setColour(random(0, 10));
                    break;

                case ExplosionSize::Large:
                    particle.setX(x);
                    particle.setY(y);
                    particle.setVelX(random(-7, 8));
                    particle.setVelY(random(4, 8));
                    particle.setCounter(random(20, 86));
                    particle.setSize(random(0, 3));
                    particle.setColour(random(0, 10));
                    break;


            }

            break;

        }

    }

}
