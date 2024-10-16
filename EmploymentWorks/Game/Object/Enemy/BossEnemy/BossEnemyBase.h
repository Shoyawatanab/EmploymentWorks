#pragma once
#ifndef BossEnemyBase_DEFINED
#define BossEnemyBase_DEFINED
#include "Interface/IComponent.h"
#include <unordered_map>

class CommonResources;
class Bounding;


class BossEnemyBase : public IComponent
{
public:

	struct AnimationKeyFrame
	{
		DirectX::SimpleMath::Vector3 Scale;        //大きさ
		DirectX::SimpleMath::Vector3 Position;      //座標
		DirectX::SimpleMath::Quaternion Rotation;   //回転　
		float Time;                                 //発生する時間
	};


public:
	// 親を取得する
	IComponent* GetParent() const { return m_parent; }
	//初期大きさを取得
	DirectX::SimpleMath::Vector3 GetInitialScale() const { return m_initialScale; }
	//初期回転角を取得する
	DirectX::SimpleMath::Quaternion GetInitialAngle() const { return m_initialAngle; }
	//モデルを取得する
	DirectX::Model* GetModel() { return nullptr; }
	//ワールド行列を取得する
	DirectX::SimpleMath::Matrix& GetWorldMatrix() { return m_worldMatrix; }
	//親座標からの距離を取得
	DirectX::SimpleMath::Vector3 GetPositonFromParent() { return m_positonFromParent; }
	CommonResources* GetResources() { return m_commonResources; }

	//アニメーションの登録 
	void SetAnimations(std::vector<AnimationKeyFrame> animations, std::string name) { m_animations[name] = animations; }


	//アニメーション座標の取得
	DirectX::SimpleMath::Vector3 GetAnimationPosition() { return m_animationPosition; }
	//アニメーションの回転の取得
	DirectX::SimpleMath::Quaternion GetAnimationRotation() { return m_animationRotation; }

public:
	// 砲塔部品番号をリセットする(-1から開始する)
	static int ResetPartsNumber() { s_partsNumber = -1;  return s_partsNumber; }
	// 砲塔部品番号のインクリメント後に砲塔部品番号を取得する
	static int GetPartsNumberAfterIncrement() { return ++s_partsNumber; }

public:
	// コンストラクタ
	BossEnemyBase(CommonResources* resources,IComponent* parent,DirectX::SimpleMath::Vector3 initialScale, const DirectX::SimpleMath::Vector3& positonFromParent, const DirectX::SimpleMath::Quaternion& initialAngle);
	// デストラクタ
	virtual ~BossEnemyBase();
	// 初期化する
	virtual void Initialize();
	// 初期化する
	virtual void Initialize( std::unique_ptr<DirectX::Model> model);
	// 更新する
	inline virtual void Update(const float& elapsdTime);
	// 砲塔部品を追加する
	virtual void Attach(std::unique_ptr<IComponent> turretPart);
	// 砲塔部品を削除する
	virtual void Detach(std::unique_ptr<IComponent> turretPart);
	// 描画する
	virtual void Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection);
	// 描画する
	inline virtual void Render(const DirectX::SimpleMath::Matrix& matrix,DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection);
	// モデルを描画する
	inline virtual void DrawModel(const DirectX::SimpleMath::Matrix& matrix, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection);
	// 境界ボックスを描画する
	inline void DrawBoundingBox(const DirectX::SimpleMath::Matrix& matrix);
	// 後処理を行う
	virtual void Finalize();

public:

	//バウンディングの生成
	void CreateBounding(DirectX::SimpleMath::Vector3 position, DirectX::SimpleMath::Quaternion rotate , DirectX::SimpleMath::Vector3 boxExten,float SphereRadius);
	//バウンディングの更新　座標
	void BoundingUdate(DirectX::SimpleMath::Vector3 position,DirectX::SimpleMath::Quaternion rotate);

	void BoundingRender(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection);

	//アニメーションの実行
	AnimationStage AnimationUdate(const float& elapsdTime);

	//アニメーションを実行中アニメーションに登録
	void RegistrationRungingAnimation(std::string name);

private:
	// 砲塔部品カウント
	static int s_partsNumber;

private:
	// モデル
	std::unique_ptr<DirectX::Model> m_model;

	std::unique_ptr<Bounding> m_bounding;

	// 親
	IComponent* m_parent;
	//初期大きさ
	DirectX::SimpleMath::Vector3 m_initialScale;
	// 初期回転角
	DirectX::SimpleMath::Quaternion m_initialAngle;
	// 部品配列
	std::vector<std::unique_ptr<IComponent>> m_parts;
	//	ワールド行列
	DirectX::SimpleMath::Matrix m_worldMatrix;

	//親座標からの距離
	DirectX::SimpleMath::Vector3 m_positonFromParent;
	// 共通リソース
	CommonResources* m_commonResources;
	//実行中のアニメーション
	std::vector<AnimationKeyFrame> m_runningKeyFrames;
	//アニメーションの保存変数
	std::unordered_map<std::string, std::vector<AnimationKeyFrame>> m_animations;
	//アニメーションの座標
	DirectX::SimpleMath::Vector3 m_animationPosition;
	//アニメーションの回転
	DirectX::SimpleMath::Quaternion m_animationRotation;
	//アニメーションの切り替え回数
	int  m_animationSwitchingCount;
	//アニメーションの実行中時間
	float m_animetionTime;

};
#endif		// BossEnemyBase_DEFINED
