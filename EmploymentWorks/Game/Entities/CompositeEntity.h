/*
* �v���C���N���X�@
*/

#pragma once

#include "CharacterEntity.h"
#include "Game/Observer/EventParams.h"

class CompositeEntity : public CharacterEntity
{
public:

	//�p�[�c�̎擾
	std::vector<std::unique_ptr<CompositeEntity>>& GetParts() { return m_parts; }

public:
	//�R���X�g���N
	CompositeEntity(CommonResources* resources
		, const DirectX::SimpleMath::Vector3& scale
		, const DirectX::SimpleMath::Vector3& position
		, const DirectX::SimpleMath::Quaternion& rotation);
	//�f�X�g���N�^
	~CompositeEntity() override;
	//�q�̒ǉ�
	void AddChild(std::unique_ptr<CompositeEntity> parts);


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
	void SetAnimationData(const std::string& animationType
		, std::unordered_map<std::string, std::unordered_map<std::string, WataLib::Json::AnimationData>> datas
		, const std::string& partsName = ""
		, bool isNormalAnimation = false) override ;
	//�A�j���[�V�����̕ύX
	void ChangeAnimation(const std::string& animationType) override ;

	//�p�[�c�ɑ΂��ă��b�Z�[�W�𑗂�@
	virtual void NotifyParts(PartMessageType type) { UNREFERENCED_PARAMETER(type); };

private:

	//�p�[�c
	std::vector<std::unique_ptr<CompositeEntity>> m_parts;


};

