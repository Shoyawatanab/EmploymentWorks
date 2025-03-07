/*
* �v���C���N���X�@
*/

#pragma once

#include "CharacterEntity.h"


class CompositeEntity : public CharacterEntity
{
public:


	CompositeEntity(CommonResources* resources
		, const DirectX::SimpleMath::Vector3& scale
		, const DirectX::SimpleMath::Vector3& position
		, const DirectX::SimpleMath::Quaternion& rotation);

	~CompositeEntity() override;

	void AddChild(std::unique_ptr<CharacterEntity> parts);

	std::vector<std::unique_ptr<CharacterEntity>>& GetParts() { return m_parts; }


//BaseEntity
	//������
	void Initialize();
	//�X�V����
	void  Update(const float& elapsedTime)  override;
	//�`��
	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection);
//CollisionEntity
		//�����������ɌĂяo�����
	void OnCollisionEnter(CollisionEntity* object, CollisionTag tag) override;

//CharactorEntity
	//�A�j���[�V�����̓o�^
	void SetAnimationData(std::string animationType
		, std::unordered_map<std::string, std::unordered_map<std::string, WataLib::Json::AnimationData>> datas
		, const std::string& partsName = ""
		, bool isNormalAnimation = false) override ;
	//�A�j���[�V�����̕ύX
	void ChangeAnimation(std::string animationType) override ;


private:

	//�p�[�c
	std::vector<std::unique_ptr<CharacterEntity>> m_parts;


};


