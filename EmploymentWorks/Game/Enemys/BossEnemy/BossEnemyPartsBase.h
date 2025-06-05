#pragma once
#include "Game/Entities/CompositeEntity.h"
#include "Game/Observer/EventParams.h"

class CommonResources;
class BossEnemy;

namespace WataLib
{
	class Animation;
}



class BossEnemyPartsBase : public CompositeEntity
{

public:

public:
	// コンストラクタ
	BossEnemyPartsBase(CommonResources* resources
		, BossEnemy* root
		, CharacterEntity* parent
		, const DirectX::SimpleMath::Vector3& scale
		, const DirectX::SimpleMath::Vector3& position
		, const DirectX::SimpleMath::Quaternion& rotation
		, const std::string& partsName
		, const int partsHP
		, const DirectX::SimpleMath::Vector3& boxColliderSize
		, const float SphereColliderSize);
	//デストラクタ
	~BossEnemyPartsBase()  override;



private:



};
