#pragma once
#include "GameBase/Component/Components.h"

class Camera;
class ParticleSystem;

class RenderManager
{
	
public:

	//コンストラクタ
	RenderManager();
	//デストラクタ
	~RenderManager();

	//描画処理
	void Render(const Camera& camera);
	//モデルの追加
	void AddModel(ModelComponent* comp);
	//モデルの削除
	void RemoveModel(ModelComponent* comp);
	//UIの追加
	void AddUserInterface(ImageComponent* comp);
	//UIの削除
	void RemoveUserInterface(ImageComponent* comp);

	//コライダーの追加　デバッグ　
	void AddCollider(ColliderComponent* comp);

	void AddParticle(ParticleSystem* system);

private:
	//モデルコンポーネント
	std::vector<ModelComponent*> m_models;
	//UIコンポーネント
	std::vector<ImageComponent*> m_uis;
	//
	std::vector<ParticleSystem*> m_particle;


	//デバッグ　
	//当たり判定
	std::vector<ColliderComponent*> m_colliders;
	//ベーシックエフェクト
	std::unique_ptr<DirectX::BasicEffect> m_effect;
	//インプットレイアウト
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_layout;
	//プリミティブバッチ
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColor>> m_batch;

	

};