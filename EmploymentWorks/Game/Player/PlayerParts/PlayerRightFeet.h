/*
* �v���C���̉E���N���X
*/
#pragma once
#include "Game/Player/PlayerPartsBase.h"

namespace WataLib
{
	class Animation;
}


// �u�C���v�N���X���`����
class PlayerRightFeet : public PlayerPartsBase
{
private:

	//�p�[�c��
	static constexpr const char PARTSNAME[] = "RightFeet";

public:
	//�R���X�g���N�^
	PlayerRightFeet(CommonResources* resources, 
		CharacterEntity* parent,
		DirectX::SimpleMath::Vector3 scale,
		DirectX::SimpleMath::Vector3 position,
		DirectX::SimpleMath::Quaternion rotation);
	//�f�X�g���N�^
	~PlayerRightFeet() override;


	//IObject
	//������
	void Initialize() override;


};

