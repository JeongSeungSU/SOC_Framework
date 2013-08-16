#pragma once

#include "Object.h"
#include "Rect.h"
#include "Frustum.h"
#include "Skybox.h"

namespace Rendering
{
	class Camera : private Object
	{
	public:
		enum TYPE { TYPE_PERSPECTIVE, TYPE_ORTHOGRAPHIC };
		enum CLEAR_FLAG { CLEAR_FLAG_SKYBOX, CLEAR_FLAG_SOLIDCOLOR, CLEAR_FLAG_TARGET, CLEAR_FLAG_DONT_CLAR };
		//CLEAR_FLAG_DEPTHONLY�� ������. ��� �����϶�°��� �� �𸣰��� -��-;

	private:
		Frustum *frustum;
		LPDIRECT3DDEVICE9 device;

	private:
		Common::Rect<float>	  normalizedViewPortRect;
		std::vector<Object*>* sceneObjects;

	public:  //���� private�� �� �ʿ�� ����.
		float				FOV;
		float				clippingNear;
		float				clippingFar;
		CLEAR_FLAG			clearFlag;
		TYPE				camType;
		float				aspect;
		D3DCOLOR			clearColor;
		Skybox				*skybox;
		//1. hdr�� ���⼭ ó���ϴµ�? ���� ���� �дϱ�..
		/*2. �ø� ����ũó������ �������� �±׸� ������ �� �־�.
		     �׷� �±� �ý����� �ٲ�� �Ѵ� �Ҹ��� ��.. */
		//3. ���� �ؽ��� ����. �̰� ���� �Ұ� �ƴϾ�

	public:
		Camera(LPDIRECT3DDEVICE9 device, Skybox *skybox,std::vector<Object*>* sceneObjects, Object *parent = NULL);
		~Camera(void);

	private:
		void CalcAspect();

	public:
		void Clear();

	public:
		void GetPerspectiveMatrix(D3DXMATRIX *outMatrix, float farGap);
		void GetOrthoGraphicMatrix(D3DXMATRIX *outMatrix);
		void GetProjectionMatrix(D3DXMATRIX *outMatrix, float farGap = 0);
		void GetViewMatrix(D3DXMATRIX *outMatrix){GetMatrix(outMatrix);}

	public:
		bool Render();

	public:
		void SetViewPort(Common::Rect<float> rect);
		
		static void SetMainCamera(Camera *camera);
		static Camera* GetMainCamera();
	};

}