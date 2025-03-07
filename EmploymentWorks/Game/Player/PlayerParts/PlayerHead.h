/*
* �v���C���̓��N���X
*/
#pragma once
#include "Game/Player/PlayerPartsBase.h"

namespace WataLib
{
	class Animation;
}
// �u�C���v�N���X���`����
class PlayerHead : public PlayerPartsBase
{
private:
	static constexpr const char PARTSNAME[] = "Head";

public:
	//�R���X�g���N�^
	PlayerHead(CommonResources* resources, 
		CharacterEntity* parent,
		DirectX::SimpleMath::Vector3 scale,
		DirectX::SimpleMath::Vector3 position,
		DirectX::SimpleMath::Quaternion rotation);
	//�f�X�g���N�^
	~PlayerHead() override;



	//������
	void Initialize() override;

};

