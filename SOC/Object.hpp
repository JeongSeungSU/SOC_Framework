
namespace Rendering
{
	//template<class ComponentType>
	//ComponentType* AddComponent()
	//{
	//	typename std::vector<Component*>::iterator iter;
	//	for(iter = components.begin(); iter != components.end(); ++iter)
	//	{
	//		if( (*iter)->GetComponentType() < Component::Type::User )
	//			return dynamic_cast<ComponentType*>(*iter);
	//	}

	//	ComponentType *compo = new ComponentType;

	//	//���� ���� ������Ʈ�� �ߺ� ����
	//	compo->Initialize();
	//	components.push_back(compo);

	//	return compo;
	//}

	//template<class ComponentType>
	//ComponentType* Object::GetComponent()
	//{
	//	typename std::vector<Component*>::iterator iter;
	//	for(iter = components.begin(); iter != components.end(); ++iter)
	//	{
	//		if((*iter)->ComponentType == ComponentType::ComponentType)
	//			return (*iter);
	//	}

	//	return nullptr;
	//}

	//template<class ComponentType>
	//std::vector<ComponentType*> Object::GetComponents()
	//{
	//	std::vector<Component*> v;
	//	typename std::vector<Component*>::iterator iter;
	//	for(iter = components.begin(); iter != components.end(); ++iter)
	//	{
	//		if((*iter)->ComponentType == ComponentType::ComponentType)
	//			v.push_back((*iter));
	//	}

	//	return v;
	//}
}