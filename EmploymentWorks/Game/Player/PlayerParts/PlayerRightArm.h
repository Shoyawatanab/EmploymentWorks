/*
* �v���C���̉E�A�r�N���X
*/
#pragma once
#include "Game/Player/PlayerPartsBase.h"

namespace WataLib
{
	class Animation;
}

// �u�C���v�N���X���`����
class PlayerRightArm : public PlayerPartsBase
{
private :

	//�p�[�c��
	static constexpr const char PARTSNAME[] = "RightArm";

public:
	//�R���X�g���N�^
	PlayerRightArm(CommonResources* resources, 
		CharacterEntity* parent,
		DirectX::SimpleMath::Vector3 scale,
		DirectX::SimpleMath::Vector3 position,
		DirectX::SimpleMath::Quaternion rotation);
	//�f�X�g���N�^
	~PlayerRightArm() override;


	//IObject
	//������
	void Initialize() override;


};

