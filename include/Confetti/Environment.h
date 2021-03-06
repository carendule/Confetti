#if !defined(CONFETTI_ENVIRONMENT_H)
#define CONFETTI_ENVIRONMENT_H

#pragma once

#include <glm/glm.hpp>
#include <random>
#include <vector>
#include <Vkx/Random.h>

namespace Confetti
{
//! An external (to any particle or emitter) set of factors that affect a particle's position and velocity.
//!
//! @ingroup	Controls
//!
//!
//! An environment contains the following factors. All factors are optional.
//!
//!     - gravity: Particles will accelerate according to the gravity acceleration vector.
//!     - air friction: Particles will decelerate in the direction of motion according to the air friction value. This value is used
//!                     to compute a terminal velocity, specifically wind velocity plus sqrt(gravity/airFriction). It represents a
//!                     combination of the mass of the particle, the drag coefficient, the density of the air, and the projected
//!                     area of the particle.
//!     - wind: Particles can be affected by a wind that consists of a constant speed and direction modified randomly according to
//!             the gustiness factor. Gustiness is a constant acceleration applied to the wind velocity in a random direction.
//!

class Environment
{
public:

    //! A plane that the particles bounce against.
    struct Surface
    {
        glm::vec4 plane = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);   //!< The plane
        float dampening = 1.0f;                                //!< Ratio of post-bounce velocity to pre-bounce velocity.

        Surface(glm::vec4 const & p, float d)
            : plane(p)
            , dampening(d)
        {
            /* no idea why I need this */
        }
    };

    //! A plane that clips particles.
    using Clipper = glm::vec4;

    //! A list of Surfaces.
    using SurfaceList = std::vector<Surface>;

    //! A list of Clippers.
    using ClipperList = std::vector<Clipper>;

    //! Constructor.
    explicit Environment(glm::vec3 const &   gravity      = { 0.0f, 0.0f, 0.0f },
                         float               airFriction  = 0.0f,
                         glm::vec3 const &   windVelocity = { 0.0f, 0.0f, 0.0f },
                         float               gustiness    = 0.0f,
                         SurfaceList const & bpl          = SurfaceList(),
                         ClipperList const & cpl          = ClipperList());

    //! Sets gravity.
    void setGravity(glm::vec3 const & gravity) { gravity_ = gravity; }

    //! Returns gravity.
    glm::vec3 gravity() const { return gravity_; }

    //! Sets air friction
    void setAirFriction(float airFriction) { airFriction_ = airFriction; }

    //! Returns air friction
    float airFriction() const { return airFriction_; }

    //! Sets wind velocity
    void setWindVelocity(glm::vec3 const & wind) { windVelocity_ = wind; }

    //! Returns wind velocity
    glm::vec3 windVelocity() const { return currentWindVelocity_; }

    //! Sets gustiness
    void setGustiness(float gustiness) { gustiness_ = gustiness; }

    //! Returns gustiness
    float gustiness() const { return gustiness_; }

    //! Sets the list of surface
    void setSurfaces(SurfaceList const & bpl) { surfaces_ = bpl; }

    //! Returns the list of surface
    SurfaceList const & surfaces() const { return surfaces_; }

    //! Sets the list of clip planes
    void setClippers(ClipperList const & cpl) { clippers_ = cpl; }

    //! Returns the list of clip planes
    ClipperList const & clippers() const { return clippers_; }

    //! Updates the environment.
    void update(float dt);

    //! Returns the terminal velocity
    glm::vec3 terminalVelocity() const { return terminalVelocity_; }

    //! Returns the distance traveled by a particle at terminal velocity during the last update.
    glm::vec3 terminalDistance() const { return terminalDistance_; }

    //! Returns the value 1.0f - exp( -airFriction_ * dt ) calculated during the last update.
    float ect1() const { return ect1_; }

private:

    glm::vec3 gravity_;                     // Gravity.
    glm::vec3 windVelocity_;                // Constant wind velocity component of the current wind velocity.
    float airFriction_;                     // Friction factor.
    float gustiness_;                       // Gustiness factor.
    SurfaceList surfaces_;                  // A list of planes that the particles bounce against.
    ClipperList clippers_;                  // A list of planes that clip the particles.
    Vkx::RandomDirection gustDirection_;    // Direction generator for gusts
    glm::vec3 gust_;                        // Gust component of the current wind velocity.
    glm::vec3 currentWindVelocity_;         // Current wind velocity.
    glm::vec3 terminalVelocity_;            // Terminal velocity.
    glm::vec3 terminalDistance_;            // Movement of a particle traveling at terminal velocity.
    float ect1_;                            // The value 1.0f - exp( -airFriction_ * dt ) calculated during the last update.
    std::minstd_rand rng_;                  // The RNG for environments
};
} // namespace Confetti

#endif // !defined(CONFETTI_ENVIRONMENT_H)
