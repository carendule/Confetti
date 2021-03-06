#include "TexturedParticle.h"

#include "Appearance.h"
#include "Emitter.h"
#include "Environment.h"

#include <glm/glm.hpp>

namespace Confetti
{
// Vertex shader data declaration info

// D3DVERTEXELEMENT11 const TexturedParticle::aVSDataDeclarationInfo_[] =
// {
//     { 0,  0,  D3DDECLTYPE_FLOAT3,   D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
//     { 0, 12,  D3DDECLTYPE_D3DCOLOR, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR, 0 },
//     { 0, 16,  D3DDECLTYPE_FLOAT2,   D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },
//     { 0, 24,  D3DDECLTYPE_FLOAT1,   D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 1 },
//     { 0, 28,  D3DDECLTYPE_FLOAT1,   D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 2 },
//     D3DDECL_END()
// };

//! @param	lifetime		How long the particle lives.
//! @param	age				Initial age.
//! @param	position		Position at birth.
//! @param	velocity		Velocity at birth.
//! @param	color			Color at birth.
//! @param	radius			Radius at birth.
//! @param	rotation		Rotation at birth.

TexturedParticle::TexturedParticle(float             lifetime,
                                   float             age,
                                   glm::vec3 const & position,
                                   glm::vec3 const & velocity,
                                   glm::vec4 const & color,
                                   float             radius,
                                   float             rotation /* = 0.0f*/)
    : Particle(lifetime, age, position, velocity, color)
    , initialRadius_(radius)
    , radius_(radius)
    , initialRotation_(rotation)
    , rotation_(rotation)
{
}

//! @param	lifetime		How long the particle lives.
//! @param	age				Initial age.
//! @param	position		Position at birth.
//! @param	velocity		Velocity at birth.
//! @param	color			Color at birth.
//! @param	radius			Radius at birth.
//! @param	rotation		Rotation at birth.

void TexturedParticle::Initialize(float             lifetime,
                                  float             age,
                                  glm::vec3 const & position,
                                  glm::vec3 const & velocity,
                                  glm::vec4 const & color,
                                  float             radius,
                                  float             rotation)
{
    Particle::initialize(lifetime, age, position, velocity, color);

    initialRadius_   = radius;
    initialRotation_ = rotation;

    radius_   = radius;
    rotation_ = rotation;
}

//!
//! @param	dt	The amount of time that has passed since the last update

bool TexturedParticle::update(float dt)
{
    // Update base class

    bool const reborn = Particle::update(dt);

    if (reborn)
    {
        radius_   = initialRadius_;
        rotation_ = initialRotation_;
        dt        = age_;
    }

    std::shared_ptr<Appearance> pA = emitter_->appearance();

    // Update size and rotation

    radius_   += dt * pA->radiusRate;
    rotation_ += dt * pA->angularVelocity;

    return reborn;
}

void TexturedParticle::draw(std::shared_ptr<Vkx::Device> device) const
{
    // Nothing to do because the particle is drawn by the emitter. This function should not be called.
    assert(false);
}
} // namespace Confetti
