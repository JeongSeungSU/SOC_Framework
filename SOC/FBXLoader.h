#pragma once

#define FBXSDK_NEW_API

#include <fbxsdk.h>
#pragma comment(lib, "libfbxsdk-md.lib")

#include "MaterialElements.h"

namespace Rendering
{
	namespace Loader
	{
		class FBXLoader
		{
		private:
			FbxManager	*manager;
			FbxScene	*scene;

		public:
			FBXLoader(void)
			{
				manager = nullptr;
				scene = nullptr;
			}

			~FBXLoader(void)
			{
			}

		public:
			bool Initialize(const char *sceneName)
			{
				manager = FbxManager::Create();

				if(manager == nullptr)
					return false;

				FbxIOSettings *ioSetting = FbxIOSettings::Create(manager, IOSROOT);
				manager->SetIOSettings(ioSetting);

				FbxString path = fbxsdk_2014_1::FbxGetApplicationDirectory();

#if defined (FBXSDK_ENV_WIN)
				FbxString IExtension = "dll";
#elif defined (FBXSDK_ENV_MAC)
				FbxString IExtension = "dylib";				
#elif defined (FBXSDK_ENV_LINUX)
				FbxString IExtension = "so";
#endif

				manager->LoadPluginsDirectory(path.Buffer(), IExtension.Buffer());
				scene = FbxScene::Create(manager, sceneName);

				return scene != nullptr;
			}

			bool LoadScene(const char *fileName, const char *password = nullptr)
			{
				int fileMajor, fileMinor, fileRevision;
				int sdkMajor, sdkMinor, sdkRevision;

//				int  animStackCount;
				bool status;
//				char password[1024];

				//������ ������ȣ�� sdk�� ���� �����˴ϴ�?
				//Get the file version number generate by the FBX SDK
				FbxManager::GetFileFormatVersion(sdkMajor, sdkMinor, sdkRevision);

				//�����͸� �����մϴ�.
				FbxImporter* importer = FbxImporter::Create(manager, "");

				//���� �̸��� �����Ͽ� �����͸� �ʱ�ȭ ��ŵ�ϴ�.
				bool importStatus = importer->Initialize(fileName, -1, manager->GetIOSettings());

				//����� �뵵�̱� �ѵ�, �� ���� ������ �����״� �� ��
				//���� �����ְ���
				importer->GetFileVersion(fileMajor, fileMinor, fileRevision);

				if(importStatus == false)
				{
					FbxString error = importer->GetStatus().GetErrorString();
					// error ������, error Buffer��
				}

				if(importer->IsFBX())
				{
//					animStackCount = importer->GetAnimStackCount();

					//for(int i = 0; i < animStackCount; ++i)
					//{
					//	FbxTakeInfo* takeInfo = importer->GetTakeInfo(i);
					//	//������ ��� �� ��
					//}


					manager->GetIOSettings()->SetBoolProp(IMP_FBX_MATERIAL,        true);
					manager->GetIOSettings()->SetBoolProp(IMP_FBX_TEXTURE,         true);
					manager->GetIOSettings()->SetBoolProp(IMP_FBX_LINK,            true);
					manager->GetIOSettings()->SetBoolProp(IMP_FBX_SHAPE,           true);
					manager->GetIOSettings()->SetBoolProp(IMP_FBX_GOBO,            true);
					manager->GetIOSettings()->SetBoolProp(IMP_FBX_ANIMATION,       true);
					manager->GetIOSettings()->SetBoolProp(IMP_FBX_GLOBAL_SETTINGS, true);
				}

				status = importer->Import(scene);

				if(status == false && 
					importer->GetStatus().GetCode() == FbxStatus::ePasswordError)
				{
					//�н����尡 �ʿ��Դϴ�? ����
					FbxString str(password);
					manager->GetIOSettings()->SetStringProp(IMP_FBX_PASSWORD, str);
					manager->GetIOSettings()->SetBoolProp(IMP_FBX_PASSWORD_ENABLE, true);

					status = importer->Import(scene);

					if(status == false && importer->GetStatus().GetCode() == FbxStatus::ePasswordError)
						return false;
				}

				importer->Destroy();

				return status;
			}

			bool AllNodes(FbxNode *node)
			{
				if( node == nullptr )
					return false;

				FbxNodeAttribute *attribute = node->GetNodeAttribute();

				if(attribute != nullptr)
				{
					FbxNodeAttribute::EType type = attribute->GetAttributeType();

					if(type == FbxNodeAttribute::eMesh)
					{}
					else if(type == FbxNodeAttribute::eSkeleton)
					{}
					else
					{

					}

					//camera nurb patch ���� ����
				}

				int childCount = node->GetChildCount();
				for(int i=0; i<childCount; ++i)
				{

				}

				return true;
			}

			bool AssignMesh(FbxMesh *mesh)
			{
				//vertex buffer aryCount
				int vertexCount = mesh->GetControlPointsCount();
				int polygonCount = mesh->GetPolygonCount();

				//�ε��� ���� ����
				SOC_uint indexedsCount = 0;
				for(int i=0; i<polygonCount; ++i)
				{
					int polygonSize = mesh->GetPolygonSize(i);

					if(polygonSize == 3)
						indexedsCount += 3;
					else if(polygonSize == 4) //4������ 3���� 2���� ����
						indexedsCount += 6;
					else //������
					{
						return false;
					}
				}

				//meshinfo.vertexcscount vertexcount
				//mi.vtxs = new vtx[vsize];
				//mi.idxcount = idxcount
				//mi.idex = new uint[count]

				//���ؽ�
				for(int i=0; i<vertexCount; ++i)
				{
					//control point�� vertex�ε� �� ���̷� ��
					FbxVector4 v = mesh->GetControlPointAt(i);
					//������ ����
				}

				

				return true;
			}

			bool AssignBone(FbxSkeleton *skeleton)
			{
				if(skeleton == nullptr)
					return false;

				FbxNode *boneNode = skeleton->GetNode();


				return true;
			}

			bool AssignMaterials(FbxNode *node)
			{
				if(node == nullptr)
					return false;

				int count = node->GetMaterialCount();

				for(int i=0; i<count; ++i)
				{
					FbxSurfaceMaterial *fbxMaterial = node->GetMaterial(i);
					if(fbxMaterial)
					{
						//Material material;
						FbxClassId id = fbxMaterial->GetClassId();

						//Shading
						if( id.Is(FbxSurfacePhong::ClassId) )
						{
							FbxSurfacePhong *phong = static_cast<FbxSurfacePhong*>(fbxMaterial);
							//ambient color ����, factor diffuse specular emissive ����
							//TransparentColor factor�� ���� reflection�� specular�ε� -;
							//reflectionfactor, shininess???
							//������ �� �ٽ� ¥�߰ھ�
							//���� ���̴��� ��� �ִµ� �� �ٲ�߰ڴ�
						}
						else if(id.Is(FbxSurfaceLambert::ClassId))
						{
							FbxSurfaceLambert *lambert = static_cast<FbxSurfaceLambert*>(fbxMaterial);
							//ambient, diffuse, emissive, transparent, bump(?), bumpfactor, vectorDisplacementColor, Factor
						}

						FbxProperty fbxProperty = fbxMaterial->GetFirstProperty();
						for(; fbxProperty.IsValid(); fbxMaterial->GetNextProperty(fbxProperty))
						{
							//AssignTexture
						}
						//mesh.push(material);
					}

					return true;
				}
			}

			bool AssignTextures(FbxProperty *fbxProperty)
			{
				int layeredTextureCount = fbxProperty->GetSrcObjectCount<FbxLayeredTexture>();

				if(layeredTextureCount > 0)
				{
					FbxLayeredTexture *layeredTexture;
					
					for(int i=0; i<layeredTextureCount; ++i)
					{
						layeredTexture = fbxProperty->GetSrcObject<FbxLayeredTexture>();

						if(layeredTexture == nullptr)
							continue;

						//texture list
						int count = layeredTexture->GetSrcObjectCount<FbxTexture>();
						for(int j=0; j<count; ++j)
						{
							FbxTexture *texture = layeredTexture->GetSrcObject<FbxTexture>(j);
							if(texture == nullptr)
								continue;

							FbxFileTexture *fileTexture = FbxCast<FbxFileTexture>(texture);
							if(fileTexture)
								continue;

							FbxLayeredTexture::EBlendMode blendMode;
							if(layeredTexture->GetTextureBlendMode(j, blendMode))
							{
								//texture set blend mode
							}

							double alpha = 0.0f;
							if(layeredTexture->GetTextureAlpha(j, alpha))
							{
								//texture set alpha
							}

							//texture �����ٰ� ������
							//name�� �ƴϱ� �� ������� ������ �����ϰ�? relativeFileName�� �ְ�
							//�̸��� �ƴϱ�, ���� �Ŵ������� ���ٰ� ���� �ɵ� �;�
							//�׸���, texture list�� add��
						}
						//���׸��� ���̾���ؽ��Ŀ� �� ����Ʈ�� �߰��϶�µ�?
						//���� ��������
					}
				}
				else
				{
					int count  = fbxProperty->GetSrcObjectCount<FbxTexture>();

					for(int i=0; i<count; ++i)
					{
						FbxTexture *texture = fbxProperty->GetSrcObject<FbxTexture>();
						if(texture == nullptr)
							continue;

						FbxFileTexture *fileTexture = FbxCast<FbxFileTexture>(texture);
						if(fileTexture)
							continue;

						//�� ó�� texture Mgr �޾ƿͼ� ó�� ����
					}
				}

				return true;
			}



			void GetPolygon(FbxMesh *fbxMesh)
			{

			}

			void Destroy()
			{
				if(manager)
				{
					manager->Destroy();
					manager = nullptr;
				}

				if(scene)
				{
					scene->Destroy();
					scene = nullptr;
				}
			}
		};
	}
}