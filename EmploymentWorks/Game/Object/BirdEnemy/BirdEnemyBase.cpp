#include "pch.h"
#include "Interface/IComponent.h"
#include "Game/Object/BirdEnemy/BirdEnemyBase.h"
#include "DeviceResources.h"
#include "Game/CommonResources.h"
#include <unordered_map>
#include "Libraries/MyLib/Bounding.h"

void BirdEnemyBase::SetRunnginAnimationName(std::string name)
{
	//名前が同じなら
	if (m_runningAnimationName == name)
	{
		return;
	}

	//アニメーションがあるか探す
	auto it = m_animations.find(m_runningAnimationName);
	//あれば
	if (it != m_animations.end())
	{
		//変更前のアニメーションをリセット
		m_animations[m_runningAnimationName]->ResetAnimation();
		//回転もリセット　これはのちにいらなくなる　前のアニメーションと次のアニメーションの切り替えを違和感なくするために
		m_animationRotation = DirectX::SimpleMath::Quaternion::Identity;

	}


	m_runningAnimationName = name;





	// 部品を更新する
	for (auto& part : m_parts)
	{
		part->SetRunnginAnimationName(name);
	}

}

// コンストラクタ
BirdEnemyBase::BirdEnemyBase(CommonResources* resources,IComponent* parent,  DirectX::SimpleMath::Vector3 initialScale, const DirectX::SimpleMath::Vector3& positonFromParent, const DirectX::SimpleMath::Quaternion& initialAngle)
	:
	m_commonResources{resources},
	m_parent(parent),
	m_initialScale{initialScale},
	m_initialAngle(initialAngle),
	m_positonFromParent{positonFromParent},
	m_model{},
	m_parts{},
	m_worldMatrix{},
	m_animationPosition{},
	m_animationRotation{},
	m_animetionTime{}
{
}

// デストラクタ
BirdEnemyBase::~BirdEnemyBase()
{
	
}

// 初期化する
void BirdEnemyBase::Initialize()
{
}

// 初期化する
void BirdEnemyBase::Initialize(std::unique_ptr<DirectX::Model> model)
{
	// モデルを設定する
	m_model = std::move(model);

	m_bounding = std::make_unique<Bounding>();
}

// 更新する
void BirdEnemyBase::Update(const float& elapsdTime)
{
	UNREFERENCED_PARAMETER(elapsdTime);


	// 部品を更新する
	for (auto& part : m_parts)
	{
		part->Update(elapsdTime);
	}
}

// 砲塔部品を追加する
void BirdEnemyBase::Attach(std::unique_ptr<IComponent> turretPart)
{
	// 初期化する
	turretPart->Initialize();
	// 部品を追加する
	m_parts.emplace_back(std::move(turretPart));
}

// 部品を削除する
void BirdEnemyBase::Detach(std::unique_ptr<IComponent> turretPart)
{
	// 削除する部品を見つける
	auto it = std::find_if(m_parts.begin(), m_parts.end(),
		[&](const std::unique_ptr<IComponent>& turret_part)
		{
			return turret_part.get() == turretPart.get();
		}
	);
	// 削除する部品が見つかった場合は部品を削除する
	if (it != m_parts.end())
	{
		m_parts.erase(it);
	}
}

// 描画する(自身を描画しない)
void BirdEnemyBase::Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection)
{


	// 部品を描画する
	for (auto& turretPart : m_parts)
	{
		// 砲塔子部品を描画する
		turretPart->Render(view, projection);
	}
}

// 描画する(自身を描画する)
void BirdEnemyBase::Render(const DirectX::SimpleMath::Matrix& matrix, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection)
{
	using namespace DirectX::SimpleMath;



	m_worldMatrix = matrix;
	// モデルを描画する
	DrawModel(matrix,view,projection);

#ifdef _DEBUG
	// 境界ボックスを描画する
	DrawBoundingBox(matrix);
#endif

	//部品が存在するか
	if (m_parts.size() == 0) 
		return;
	// 部品を描画する
	for (auto& turretPart : m_parts)
	{
		// 部品を描画する
		turretPart->Render(view,projection);
	}

}

// モデルを描画する
void BirdEnemyBase::DrawModel(const DirectX::SimpleMath::Matrix& matrix, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection)
{

	auto context = BirdEnemyBase::GetResources()->GetDeviceResources()->GetD3DDeviceContext();
	auto states = BirdEnemyBase::GetResources()->GetCommonStates();


	// モデルのエフェクトを更新する
	m_model->UpdateEffects([&](DirectX::IEffect* effect)
		{
			// ベイシックエフェクトを取得する
			auto basicEffect = dynamic_cast<DirectX::BasicEffect*>(effect);
				// ディフューズカラーを設定する
				basicEffect->SetDiffuseColor(DirectX::Colors::LightSlateGray);
				// スペキュラカラーを設定する
				basicEffect->SetSpecularColor(DirectX::Colors::LightSlateGray);
				// スペキュラパワーを設定する
				basicEffect->SetSpecularPower(20.0f);
		});
	// 部品を描画する
	//m_graphics->DrawModel(m_model, matrix);
	m_model->Draw(context, *states, matrix, view, projection);
}

// 境界ボックスを描画する
void BirdEnemyBase::DrawBoundingBox(const DirectX::SimpleMath::Matrix& matrix)
{
}


// 後処理を行う
void BirdEnemyBase::Finalize()
{
}

void BirdEnemyBase::RegistrationCollionManager(CollisionManager* collsionManager)
{
	// 部品を当たり判定に登録
	for (auto& turretPart : m_parts)
	{
		// 部品を描画する
		turretPart->RegistrationCollionManager(collsionManager);
	}

}


void BirdEnemyBase::CreateBounding(DirectX::SimpleMath::Vector3 position,DirectX::SimpleMath::Quaternion rotate ,DirectX::SimpleMath::Vector3 boxExten, float SphereRadius)
{


	m_bounding->CreateOrientexBox(m_commonResources, position, boxExten,rotate);
	m_bounding->CreateBoundingSphere(m_commonResources, position, SphereRadius);


}

void BirdEnemyBase::BoundingUdate(DirectX::SimpleMath::Vector3 position,DirectX::SimpleMath::Quaternion rotate)
{

	m_bounding->OrientexBoxUpdate(position,rotate);

}

void BirdEnemyBase::BoundingRender(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection)
{
	m_bounding->DrawOrientexBox(view, projection);
	//m_bounding->DrawBoundingSphere(view, projection);


}

Animation::AnimationState BirdEnemyBase::AnimationUdate(const float& elapsdTime)
{
	using namespace DirectX::SimpleMath;

	//初期値としてアニメーション中とする
	Animation::AnimationState state = Animation::AnimationState::End;
	//アニメーションを探す
	auto it = m_animations.find(m_runningAnimationName);
	//アニメーションがあれば
	if (it != m_animations.end())
	{
		state = m_animations[m_runningAnimationName]->Update(elapsdTime);
		m_animationRotation = m_animations[m_runningAnimationName]->GetAnimationRotate();
	}


	// 部品のアニメーションを更新する
	for (auto& part : m_parts)
	{
		//子が実行中なら
		if (part->AnimationUdate(elapsdTime) == Animation::AnimationState::Running)
		{
			//アニメーション実行中に
			state = Animation::AnimationState::Running;
		}
	}

	return state;
}





// 入力値を制限する
inline float Clamp(const float& value, const float& min, const float& max)
{
	if (value < min) 	return min;
	else if (value > max) return max;
	return value;
}