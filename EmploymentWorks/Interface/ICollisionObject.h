#pragma once
#ifndef ICollisionObject_DEFINED
#define ICollisionObject_DEFINED

class CollisionManager;
class Bounding;

static const uint32_t bit = 1 << 0;


enum  class CollsionObjectTag
{

	None = 0
	, Player = 1 << 0     //�v���C��
	, Enemy = 1 << 1     //�G
	, Boomerang = 1 << 2     //�u�[������
	, Stage = 1 << 3     //���ȊO�̃X�e�[�W�I�u�W�F�b�N�@�ǂ�V��
	, Floor = 1 << 4     //��
	, Pillar = 1 << 5     //��
	, Artillery = 1 << 6     //�C��
	, ArtilleryBullet = 1 << 7     //�C��̒e
	, EnemyParts = 1 << 8     //�G�̕��i
	, Beam = 1 << 9

};


//�����蔻��̎�� OR�Ŕ��肷��
enum class CollisionType
{

	Player_Enemy = static_cast<uint32_t>(CollsionObjectTag::Player) | static_cast<uint32_t>(CollsionObjectTag::Enemy)
	, Player_Boomerang = static_cast<uint32_t>(CollsionObjectTag::Player) | static_cast<uint32_t>(CollsionObjectTag::Boomerang)
	, Player_Stage = static_cast<uint32_t>(CollsionObjectTag::Player) | static_cast<uint32_t>(CollsionObjectTag::Stage)
	, Player_Floor = static_cast<uint32_t>(CollsionObjectTag::Player) | static_cast<uint32_t>(CollsionObjectTag::Floor)
	, Player_Pillar = static_cast<uint32_t>(CollsionObjectTag::Player) | static_cast<uint32_t>(CollsionObjectTag::Pillar)
	, Player_Artillery = static_cast<uint32_t>(CollsionObjectTag::Player) | static_cast<uint32_t>(CollsionObjectTag::Artillery)
	, Player_ArtilleryBullet = static_cast<uint32_t>(CollsionObjectTag::Player) | static_cast<uint32_t>(CollsionObjectTag::ArtilleryBullet)

	, Enemy_Boomerang = static_cast<uint32_t>(CollsionObjectTag::Enemy) | static_cast<uint32_t>(CollsionObjectTag::Boomerang)
	, Enemy_Stage = static_cast<uint32_t>(CollsionObjectTag::Enemy) | static_cast<uint32_t>(CollsionObjectTag::Stage)
	, Enemy_Floor = static_cast<uint32_t>(CollsionObjectTag::Enemy) | static_cast<uint32_t>(CollsionObjectTag::Floor)
	, Enemy_Pillar = static_cast<uint32_t>(CollsionObjectTag::Enemy) | static_cast<uint32_t>(CollsionObjectTag::Pillar)
	, Enemy_Artillery = static_cast<uint32_t>(CollsionObjectTag::Enemy) | static_cast<uint32_t>(CollsionObjectTag::Artillery)
	, Enemy_ArtilleryBullet = static_cast<uint32_t>(CollsionObjectTag::Enemy) | static_cast<uint32_t>(CollsionObjectTag::ArtilleryBullet)

	, Boomerang_Stage = static_cast<uint32_t>(CollsionObjectTag::Boomerang) | static_cast<uint32_t>(CollsionObjectTag::Stage)
	, Boomerang_Floor = static_cast<uint32_t>(CollsionObjectTag::Boomerang) | static_cast<uint32_t>(CollsionObjectTag::Floor)
	, Boomerang_Pillar = static_cast<uint32_t>(CollsionObjectTag::Boomerang) | static_cast<uint32_t>(CollsionObjectTag::Pillar)
	, Boomerang_Artillery = static_cast<uint32_t>(CollsionObjectTag::Boomerang) | static_cast<uint32_t>(CollsionObjectTag::Artillery)
	, Boomerang_ArtilleryBullet = static_cast<uint32_t>(CollsionObjectTag::Boomerang) | static_cast<uint32_t>(CollsionObjectTag::ArtilleryBullet)

	, ArtilleryBullet_Stage = static_cast<uint32_t>(CollsionObjectTag::ArtilleryBullet) | static_cast<uint32_t>(CollsionObjectTag::Stage)


	,EnemyParts_Boomerang = static_cast<uint32_t>(CollsionObjectTag::EnemyParts) | static_cast<uint32_t>(CollsionObjectTag::Boomerang)

	,Beam_Player = static_cast<uint32_t>(CollsionObjectTag::Beam) | static_cast<uint32_t>(CollsionObjectTag::Player)
	,Beam_Floor = static_cast<uint32_t>(CollsionObjectTag::Beam) | static_cast<uint32_t>(CollsionObjectTag::Floor)

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

	virtual void SetPosition(DirectX::SimpleMath::Vector3& Pos) = 0;

	virtual DirectX::SimpleMath::Vector3 GetPosition() = 0;

	////�����Ɠ����������Ɍp���I�ɌĂ΂��Update
	//virtual void OnCollisionUpdate(float elapsdTime) = 0;

};

#endif		// ICollisionObject_DEFINED
