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
	PlayerRightArm(CommonResources* resources
		,CharacterEntity* parent
		, const DirectX::SimpleMath::Vector3& scale
		, const DirectX::SimpleMath::Vector3& position
		, const DirectX::SimpleMath::Quaternion& rotation);
	//�f�X�g���N�^
	~PlayerRightArm() override;


	//IObject
	//������
	void Initialize() override;


};

