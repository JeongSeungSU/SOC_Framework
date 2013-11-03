#pragma once

#include "Map.h"
#include "VBElements.h"
#include "MaterialElements.h"

namespace Rendering
{
	struct MeshDatas
	{
		Mesh::VBElements	vb;
		Material::MaterialElements	material;
		MeshTextureNames	textureNames;

		MeshDatas(){}
		~MeshDatas(){}
	};

class MeshDataManager : public Map<MeshDatas>
{
};

}