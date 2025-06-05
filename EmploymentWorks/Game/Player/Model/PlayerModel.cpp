#include "pch.h"
#include "PlayerModel.h"
#include "Game/Player/PlayerPartss.h"
#include "GameBase/Component/Transform/Transform.h"
#include "Game/Params.h"

PlayerModel::PlayerModel(Scene* scene)
	:
	Actor(scene)
	,m_parts{}
{

	//Body�̍쐬
	auto body = GetScene()->AddActor<PlayerBody>(GetScene());
	//�e�̓o�^
	body->GetTransform()->SetParent(GetTransform());

	auto parts = body->GetAllDescendants();

	AddParts(parts);

	GetTransform()->SetScale(Params::PLAYER_SCALE);
	GetTransform()->Translate(Params::PLAYER_POSITION);
	GetTransform()->SetRotate(Params::PLAYER_ROTATION);

}

/// <summary>
/// �ŃX�g�����O
/// </summary>
PlayerModel::~PlayerModel()
{
	//�N���A
	m_parts.clear();
}

/// <summary>
/// �p�[�c�̓o�^
/// </summary>
/// <param name=""></param>
void PlayerModel::AddParts(std::vector<ModelBase*> partss)
{

	for (auto& parts : partss)
	{
		//�p�[�c���̎擾
		auto name = parts->GetPartsName();
		//�o�^���ꂽ�p�[�c�������邩
		auto sertchParts = m_parts.find(name);
		//�����
		if (sertchParts != m_parts.end())
		{
			continue;
		}

		m_parts[name] = parts;


	}

}
