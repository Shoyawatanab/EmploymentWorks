#pragma once
#ifndef ICollisionObject_DEFINED
#define ICollisionObject_DEFINED

class CollisionManager;
class Bounding;

static const uint32_t bit = 1 << 0;


static enum  class CollsionObjectTag
{

	None = 0
	, Player = 1 << 0
	, Enemy = 1 << 1
	, Boomerang = 1 << 2
	, NotMoveObject = 1 << 3     //�X�e�[�W�̏��ƕǈȊO�̓����Ȃ��I�u�W�F�N�g
	, Wall = 1 << 4
	, Floor = 1 << 5



};

//�����蔻��̎�� OR�Ŕ��肷��
enum class CollisionType
{

	Player_Enemy = static_cast<uint32_t>(CollsionObjectTag::Player) | static_cast<uint32_t>(CollsionObjectTag::Enemy)

	, Player_Boomerang = static_cast<uint32_t>(CollsionObjectTag::Player) | static_cast<uint32_t>(CollsionObjectTag::Boomerang)
	, Enemy_Boomerang = static_cast<uint32_t>(CollsionObjectTag::Enemy) | static_cast<uint32_t>(CollsionObjectTag::Boomerang)

	, Player_NotMoveObject = static_cast<uint32_t>(CollsionObjectTag::Player) | static_cast<uint32_t>(CollsionObjectTag::NotMoveObject)
	, Enemy_NotMoveObject = static_cast<uint32_t>(CollsionObjectTag::Enemy) | static_cast<uint32_t>(CollsionObjectTag::NotMoveObject)
	, Boomerang_NotMoveObject = static_cast<uint32_t>(CollsionObjectTag::Boomerang) | static_cast<uint32_t>(CollsionObjectTag::NotMoveObject)

	, Player_Wall = static_cast<uint32_t>(CollsionObjectTag::Player) | static_cast<uint32_t>(CollsionObjectTag::Wall)
	, Enemy_Wall = static_cast<uint32_t>(CollsionObjectTag::Enemy) | static_cast<uint32_t>(CollsionObjectTag::Wall)
	, Boomerang_Wall = static_cast<uint32_t>(CollsionObjectTag::Boomerang) | static_cast<uint32_t>(CollsionObjectTag::Wall)

	, Player_Floor = static_cast<uint32_t>(CollsionObjectTag::Player) | static_cast<uint32_t>(CollsionObjectTag::Floor)
	, Enemy_Floor = static_cast<uint32_t>(CollsionObjectTag::Enemy) | static_cast<uint32_t>(CollsionObjectTag::Floor)
	, Boomerang_Floor = static_cast<uint32_t>(CollsionObjectTag::Boomerang) | static_cast<uint32_t>(CollsionObjectTag::Floor)


};


// ICollisionObject�C���^�t�F�[�X���`����(GOF State�p�^�[��)
class ICollisionObject
{
public:
	/// <summary>
	/// �����蔻��N���X�ɓo�^����
	/// </summary>
	/// <param name="collsionManager">�����蔻��N���X</param>
	virtual void RegistrationCollionManager(CollisionManager* collsionManager) = 0;


	/// <summary>
	/// �o�E���f�B���O�N���X�̎擾
	/// </summary>
	/// <returns>�o�E���f�B���O�N���X</returns>
	virtual Bounding* GetBounding() const = 0;


	/// <summary>
	/// �^�O�̎擾
	/// </summary>
	/// <returns>�^�O</returns>
	virtual CollsionObjectTag GetCollsionTag() const = 0;

	/// <summary>
	/// �����������ɌĂяo���֐�
	/// </summary>
	/// <param name="tag">�����������̑���̃^�O</param>
	virtual void OnCollisionEnter(CollsionObjectTag& PartnerTag, DirectX::SimpleMath::Vector3 Pos1) = 0;

	virtual void SetPos(DirectX::SimpleMath::Vector3& Pos) = 0;

	virtual DirectX::SimpleMath::Vector3 GetPos() = 0;

	////�����Ɠ����������Ɍp���I�ɌĂ΂��Update
	//virtual void OnCollisionUpdate(float elapsdTime) = 0;

};

#endif		// ICollisionObject_DEFINED
