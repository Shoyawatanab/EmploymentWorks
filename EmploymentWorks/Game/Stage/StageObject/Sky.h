#pragma once
#include "GameBase/Actor.h"

class Camera;
class ModelComponent;

class Sky : public Actor
{
public:
	//コンストラク
	Sky(Scene* scene);
	//デストラクタ
	~Sky() override;

private:

	void Render(const Camera& camera);

private:
	//モデルコンポーネント
	ModelComponent* m_modelComponent;


};
