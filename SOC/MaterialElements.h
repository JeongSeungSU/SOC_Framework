#pragma once

#include "Color.h"

namespace Rendering
{

	struct MaterialElements
	{
		Color ambientColor;
		Color diffuseColor;
		Color specularColor;
		Color emissive;

		float transparentFactor;
		float reflectionFactor;

		MaterialElements()
		{
			reflectionFactor = 20.0f;
			transparentFactor = 1.0f;

			ambientColor = Color::gray();
			diffuseColor = Color::white();
			specularColor = Color::white();
			emissive = Color::black();
		}

		MaterialElements(Color ambientColor, Color diffuseColor, Color specularColor, float reflectionFactor, float transparentFactor = 1.0f)
		{
			this->ambientColor = ambientColor;
			this->diffuseColor = diffuseColor;
			this->specularColor = specularColor;
			this->emissive = Rendering::Color::black();

			this->transparentFactor = transparentFactor;
			this->reflectionFactor = reflectionFactor;
		}

		MaterialElements(Color ambientColor, Color diffuseColor, Color specularColor, Color emissive, float reflectionFactor, float transparentFactor = 1.0f)
		{
			this->ambientColor = ambientColor;
			this->diffuseColor = diffuseColor;
			this->specularColor = specularColor;
			this->emissive = emissive;

			this->transparentFactor = transparentFactor;
			this->reflectionFactor = reflectionFactor;
		}
	};

}