/*
* �v���C���̍����N���X
*/
#pragma once
#include "Game/Player/PlayerPartsBase.h"

namespace WataLib
{
	class Animation;
}


// �u�C���v�N���X���`����
class PlayerLeftFeet : public PlayerPartsBase
{
private:

	//�p�[�c��
	static constexpr const char PARTSNAME[] = "LeftFeet";

public:
	//�R���X�g���N�^
	PlayerLeftFeet(CommonResources* resources, 
		CharacterEntity* parent,
		DirectX::SimpleMath::Vector3 scale,
		DirectX::SimpleMath::Vector3 position,
		DirectX::SimpleMath::Quaternion rotation);
	//�f�X�g���N�^
	~PlayerLeftFeet() override;


	//IObject
	//������
	void Initialize() override;



};

