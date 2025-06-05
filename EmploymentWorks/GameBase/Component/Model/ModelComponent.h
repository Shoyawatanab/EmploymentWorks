#pragma once
#include "GameBase/Component/Components.h"

class CommonResources;
class Camera;

class ModelComponent : public Component
{

public:
	//コンストラクタ
	ModelComponent(Actor* owner, std::string modelMame);
	//デストラクタ
	~ModelComponent() override ;
	//描画
	void Render(const Camera& camera);

private:
	//モデル
	DirectX::Model* m_model;
	//共通リソース
	CommonResources* m_commonResources;

};