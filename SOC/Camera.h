#pragma once

#include "Object.h"
#include "Rect.h"
#include "Frustum.h"
#include "Skybox.h"
#include "LightManager.h"
#include "DeviceDirector.h"

namespace Rendering
{
	class Camera : public Object
	{
	public:
		enum TYPE { TYPE_PERSPECTIVE, TYPE_ORTHOGRAPHIC };
		enum CLEAR_FLAG { CLEAR_FLAG_SKYBOX, CLEAR_FLAG_SOLIDCOLOR, CLEAR_FLAG_TARGET, CLEAR_FLAG_DONT_CLAR };
		//CLEAR_FLAG_DEPTHONLY�� ������. ��� �����϶�°��� �� �𸣰��� -��-;

	private:
		Frustum *frustum;
		Device::DeviceDirector *device;

	private:
		Common::Rect<float>	  normalizedViewPortRect;
		std::vector<Object*>* sceneObjects;
		Light::LightManager* sceneLights;

	public:  //���� private�� �� �ʿ�� ����.
		float				FOV;
		float				clippingNear;
		float				clippingFar;
		CLEAR_FLAG			clearFlag;
		TYPE				camType;
		float				aspect;
		Color				clearColor;
		Skybox				*skybox;
		//1. hdr�� ���⼭ ó���ϴµ�? ���� ���� �дϱ�..
		/*2. �ø� ����ũó������ �������� �±׸� ������ �� �־�.
		     �׷� �±� �ý����� �ٲ�� �Ѵ� �Ҹ��� ��.. */
		//3. ���� �ؽ��� ����. �̰� ���� �Ұ� �ƴϾ�

	public:
		Camera(Device::DeviceDirector *device, Skybox *skybox, 
			std::vector<Object*>* objectRoots, Light::LightManager* sceneLightMgr, 
			Object *parent = NULL);
		~Camera(void);

	private:
		Camera(const Camera &cam)
		{
		}

	private:
		void CalcAspect();

	public:
		void Clear();

	public:
		void GetPerspectiveMatrix(SOC_Matrix *outMatrix, float farGap);
		void GetOrthoGraphicMatrix(SOC_Matrix *outMatrix);
		void GetProjectionMatrix(SOC_Matrix *outMatrix, float farGap = 0);
		void GetViewMatrix(SOC_Matrix *outMatrix){GetMatrix(outMatrix);}

	public:
		bool Render();

	public:
		void SetViewPort(Common::Rect<float> rect);
		
		static void SetMainCamera(Camera *camera);
		static Camera* GetMainCamera();
	};

}