#pragma once

#include "LightForm.h"

namespace Rendering
{
	namespace Light
	{
		class PointLight : public LightForm
		{
		public:
			PointLight();

		public:
			virtual bool Intersect(Intersection::Sphere &sphere);
		};

	}
}