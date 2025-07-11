/*
	�N���X��     : Sky
	����         : �V��
	�⑫�E���ӓ_ :
*/
#pragma once
#include "GameBase/Actor.h"

class Camera;
class ModelComponent;

class Sky : public Actor
{
public:
	//�R���X�g���N
	Sky(Scene* scene);
	//�f�X�g���N�^
	~Sky() override;

private:

	void Render(const Camera& camera);

private:
	//���f���R���|�[�l���g
	ModelComponent* m_modelComponent;


};
