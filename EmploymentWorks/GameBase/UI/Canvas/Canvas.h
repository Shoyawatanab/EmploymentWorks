/*
	クラス名     : Canvas
	説明         : UIキャンバスの基底クラス
	補足・注意点 :
*/
#pragma once
#include "GameBase/Actor.h"

class ImageComponent;
class Camera;

class Canvas : public Actor
{
public:

	//描画タイプ
	enum  class RenderType
	{
	
		SpaceOverlay  //常に画面に移り続ける
		, WorldSpace  //３D空間のオブジェクトとして配置
	};

public:

	//描画タイプの取得
	RenderType GetRenderType() const { return m_type; };

	//ImageComponentの取得
	std::vector<ImageComponent*> GetImageComponent() { return m_imageComponent; }

public:

	//コンストラクタ
	Canvas(Scene * scene, RenderType type);
	//デストラクタ
	~Canvas();

	//描画
	virtual void Render(const Camera& camera) { UNREFERENCED_PARAMETER(camera); };


	//ImageComponentの追加
	void AddImageComponent(ImageComponent* comp);

private:
	//描画の種類
	RenderType m_type;
	//画像コンポーネント配列
	std::vector<ImageComponent*> m_imageComponent;

};




