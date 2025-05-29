/*
* �v���C���̍��r�N���X
*/
#pragma once
#include "Game/Player/PlayerPartsBase.h"

namespace WataLib
{
	class Animation;
}


// �u�C���v�N���X���`����
class PlayerLeftArm : public PlayerPartsBase
{
private:
	//�p�[�c��
	static constexpr const char PARTSNAME[] = "LeftArm";

public:
	//�R���X�g���N�^
	PlayerLeftArm(CommonResources* resources, 
		CharacterEntity* parent
		, const DirectX::SimpleMath::Vector3& scale
		, const DirectX::SimpleMath::Vector3& position
		, const DirectX::SimpleMath::Quaternion& rotation);
	//�f�X�g���N�^
	~PlayerLeftArm() override;


	//������
	void Initialize() override;


};

