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
	PlayerLeftFeet(CommonResources* resources
		, CharacterEntity* parent
		, const DirectX::SimpleMath::Vector3& scale
		, const DirectX::SimpleMath::Vector3& position
		, const DirectX::SimpleMath::Quaternion& rotation);
	//�f�X�g���N�^
	~PlayerLeftFeet() override;


	//IObject
	//������
	void Initialize() override;



};

