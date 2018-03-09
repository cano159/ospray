// ======================================================================== //
// Copyright 2009-2018 Intel Corporation                                    //
//                                                                          //
// Licensed under the Apache License, Version 2.0 (the "License");          //
// you may not use this file except in compliance with the License.         //
// You may obtain a copy of the License at                                  //
//                                                                          //
//     http://www.apache.org/licenses/LICENSE-2.0                           //
//                                                                          //
// Unless required by applicable law or agreed to in writing, software      //
// distributed under the License is distributed on an "AS IS" BASIS,        //
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. //
// See the License for the specific language governing permissions and      //
// limitations under the License.                                           //
// ======================================================================== //

#include "common/Material.h"
#include "common/Data.h"
#include "texture/Texture2D.h"
#include "math/spectrum.h"
#include "Principled_ispc.h"

namespace ospray {
  namespace pathtracer {

    struct Principled : public ospray::Material
    {
      //! \brief common function to help printf-debugging
      /*! Every derived class should overrride this! */
      virtual std::string toString() const override
      { return "ospray::pathtracer::Principled"; }

      Principled()
      {
        ispcEquivalent = ispc::PathTracer_Principled_create();
      }

      //! \brief commit the material's parameters
      virtual void commit() override
      {
        MaterialParam3f baseColor = getMaterialParam3f("baseColor", vec3f(0.8f));
        MaterialParam3f edgeColor = getMaterialParam3f("edgeColor", vec3f(1.f));
        MaterialParam1f metallic = getMaterialParam1f("metallic", 0.f);
        MaterialParam1f specular = getMaterialParam1f("specular", 1.f);
        MaterialParam1f ior = getMaterialParam1f("ior", 1.52f);
        MaterialParam1f transmission = getMaterialParam1f("transmission", 0.f);
        MaterialParam3f transmissionColor = getMaterialParam3f("transmissionColor", vec3f(1.f));
        float transmissionDepth = getParam1f("transmissionDepth", 1.f);
        MaterialParam1f roughness = getMaterialParam1f("roughness", 0.5f);
        MaterialParam1f normal = getMaterialParam1f("normal", 1.f);

        MaterialParam1f coat = getMaterialParam1f("coat", 0.f);
        MaterialParam1f coatIor = getMaterialParam1f("coatIor", 1.5f);
        MaterialParam3f coatColor = getMaterialParam3f("coatColor", vec3f(1.f));
        MaterialParam1f coatThickness = getMaterialParam1f("coatThickness", 1.f);
        MaterialParam1f coatRoughness = getMaterialParam1f("coatRoughness", 0.f);
        MaterialParam1f coatNormal = getMaterialParam1f("coatNormal", 1.f);

        MaterialParam1f opacity = getMaterialParam1f("opacity", 1.f);

        bool thin = getParam1i("thin", 0);
        MaterialParam1f thickness = getMaterialParam1f("thickness", 1.f);

        float outsideIor = getParamf("outsideIor", 1.f);
        vec3f outsideTransmissionColor = getParam3f("outsideTransmissionColor", vec3f(1.f));
        float outsideTransmissionDepth = getParamf("outsideTransmissionDepth", 1.f);

        ispc::PathTracer_Principled_set(getIE(),
          (const ispc::vec3f&)baseColor.factor, baseColor.map ? baseColor.map->getIE() : nullptr, (const ispc::AffineSpace2f&)baseColor.xform,
          (const ispc::vec3f&)edgeColor.factor, edgeColor.map ? edgeColor.map->getIE() : nullptr, (const ispc::AffineSpace2f&)edgeColor.xform,
          metallic.factor, metallic.map ? metallic.map->getIE() : nullptr, (const ispc::AffineSpace2f&)metallic.xform,
          specular.factor, specular.map ? specular.map->getIE() : nullptr, (const ispc::AffineSpace2f&)specular.xform,
          ior.factor, ior.map ? ior.map->getIE() : nullptr, (const ispc::AffineSpace2f&)ior.xform,
          transmission.factor, transmission.map ? transmission.map->getIE() : nullptr, (const ispc::AffineSpace2f&)transmission.xform,
          (const ispc::vec3f&)transmissionColor.factor, transmissionColor.map ? transmissionColor.map->getIE() : nullptr, (const ispc::AffineSpace2f&)transmissionColor.xform,
          transmissionDepth,
          roughness.factor, roughness.map ? roughness.map->getIE() : nullptr, (const ispc::AffineSpace2f&)roughness.xform,
          normal.factor, normal.map ? normal.map->getIE() : nullptr, (const ispc::AffineSpace2f&)normal.xform, (const ispc::LinearSpace2f&)normal.rot,
          coat.factor, coat.map ? coat.map->getIE() : nullptr, (const ispc::AffineSpace2f&)coat.xform,
          coatIor.factor, coatIor.map ? coatIor.map->getIE() : nullptr, (const ispc::AffineSpace2f&)coatIor.xform,
          (const ispc::vec3f&)coatColor.factor, coatColor.map ? coatColor.map->getIE() : nullptr, (const ispc::AffineSpace2f&)coatColor.xform,
          coatThickness.factor, coatThickness.map ? coatThickness.map->getIE() : nullptr, (const ispc::AffineSpace2f&)coatThickness.xform,
          coatRoughness.factor, coatRoughness.map ? coatRoughness.map->getIE() : nullptr, (const ispc::AffineSpace2f&)coatRoughness.xform,
          coatNormal.factor, coatNormal.map ? coatNormal.map->getIE() : nullptr, (const ispc::AffineSpace2f&)coatNormal.xform, (const ispc::LinearSpace2f&)coatNormal.rot,
          opacity.factor, opacity.map ? opacity.map->getIE() : nullptr, (const ispc::AffineSpace2f&)opacity.xform,
          thin,
          thickness.factor, thickness.map ? thickness.map->getIE() : nullptr, (const ispc::AffineSpace2f&)thickness.xform,
          outsideIor,
          (const ispc::vec3f&)outsideTransmissionColor,
          outsideTransmissionDepth);
      }
    };

    OSP_REGISTER_MATERIAL(Principled,PathTracer_Principled);
  }
}
