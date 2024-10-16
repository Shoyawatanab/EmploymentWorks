#pragma once
#ifndef ICOMPONENT_DEFINED
#define ICOMPONENT_DEFINED
#include "StepTimer.h"
#include "Interface/ICollisionObject.h"

//敵だけに必要な物もあるので今後分ける

// IComponentインターフェースを定義する
class IComponent : public ICollisionObject
{
public:
	enum AnimationStage
	{
		Success,         //成功
		Runngin      //実行中

	};
public:
	// 親を取得する
	virtual IComponent* GetParent() const = 0;
	//現在の大きさを取得
	virtual DirectX::SimpleMath::Vector3 GetScale() const = 0;
	// 現在の位置を取得する
	//virtual DirectX::SimpleMath::Vector3 GetPosition() const = 0;
	// 現在の位置を設定する
	//virtual void SetPosition(const DirectX::SimpleMath::Vector3& curretPosition) = 0;
	// 現在の回転角を取得する
	virtual DirectX::SimpleMath::Quaternion GetAngle() const = 0;
	// 現在の回転角を設定する
	virtual void SetAngle(const DirectX::SimpleMath::Quaternion& angle) = 0;
	// モデルを取得する
	virtual DirectX::Model* GetModel() = 0;

public:
	// 仮想デストラクタ
	virtual ~IComponent() = default;
	// 初期化する
	virtual void Initialize() = 0;
	// 更新する
	virtual void Update(const float& elapsdTime) = 0;
	// 砲塔部品を追加する
	virtual void Attach(std::unique_ptr<IComponent> turretParts) = 0;
	// 砲塔部品を削除する
	virtual void Detach(std::unique_ptr<IComponent> turretPart) = 0;
	// 描画する
	virtual void Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection) = 0;
	// 後処理を行う
	virtual void Finalize() = 0;

	virtual AnimationStage AnimationUdate(const float& elapsdTime) = 0;
	//アニメーションを実行中アニメーションに登録
	virtual void RegistrationRungingAnimation(std::string name) = 0;

};

#endif		// ICOMPONENT_DEFINED
