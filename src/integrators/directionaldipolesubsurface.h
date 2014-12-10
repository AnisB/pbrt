
/*
    Author: Anis Benyoub
    Inspired from the pbrt dipole subsurface scattering code
*/

#if defined(_MSC_VER)
#pragma once
#endif

#ifndef PBRT_INTEGRATORS_DIRECTIONAL_DIPOLESUBSURFACE_H
#define PBRT_INTEGRATORS_DIRECTIONAL_DIPOLESUBSURFACE_H

// integrators/dipolesubsurface.h*
#include "pbrt.h"
#include "integrator.h"
#include "kdtree.h"
#include "renderers/surfacepoints.h"
struct DirectionalSubsurfaceOctreeNode;

// DirectionalDipoleSubsurfaceIntegrator Helper Declarations
struct DirectionalIrradiancePoint {
    DirectionalIrradiancePoint() { }
    DirectionalIrradiancePoint(const SurfacePoint &sp, const Spectrum &ee)
        : p(sp.p), n(sp.n), E(ee), area(sp.area),
          rayEpsilon(sp.rayEpsilon) { }
    Point p;
    Normal n;
    Spectrum E;
    float area, rayEpsilon;
};



// DirectionalDipoleSubsurfaceIntegrator Declarations
class DirectionalDipoleSubsurfaceIntegrator : public SurfaceIntegrator {
public:
    // DirectionalDipoleSubsurfaceIntegrator Public Methods
    DirectionalDipoleSubsurfaceIntegrator(int mdepth, float merror, float mindist,
                               const string &fn) {
        maxSpecularDepth = mdepth;
        maxError = merror;
        minSampleDist = mindist;
        filename = fn;
        octree = NULL;
    }
    ~DirectionalDipoleSubsurfaceIntegrator();
    Spectrum Li(const Scene *scene, const Renderer *renderer,
        const RayDifferential &ray, const Intersection &isect, const Sample *sample,
        RNG &rng, MemoryArena &arena) const;
    void RequestSamples(Sampler *sampler, Sample *sample, const Scene *scene);
    void Preprocess(const Scene *, const Camera *, const Renderer *);
private:
    // DirectionalDipoleSubsurfaceIntegrator Private Data
    int maxSpecularDepth;
    float maxError, minSampleDist;
    string filename;
    vector<DirectionalIrradiancePoint> irradiancePoints;
    BBox octreeBounds;
    DirectionalSubsurfaceOctreeNode *octree;
    MemoryArena octreeArena;

    // Declare sample parameters for light source sampling
    LightSampleOffsets *lightSampleOffsets;
    BSDFSampleOffsets *bsdfSampleOffsets;
};


DirectionalDipoleSubsurfaceIntegrator *CreateDirectionalDipoleSubsurfaceIntegrator(const ParamSet &params);

#endif // PBRT_INTEGRATORS_DIRECTIONAL_DIPOLESUBSURFACE_H
