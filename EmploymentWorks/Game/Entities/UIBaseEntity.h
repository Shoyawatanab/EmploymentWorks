/*
* プレイヤクラス　
*/

#pragma once


// 前方宣言
class CommonResources;
class UserInterface;

class UIBaseEntity
{
public:
	//共通リソース
	CommonResources* GetCommonResources() { return m_commonResources; }
	//座標の取得
	const DirectX::SimpleMath::Vector2& GetPosition() { return m_position ; };
	//座標の設定
	void SetPosition(const DirectX::SimpleMath::Vector2& position) 
	{ 
		m_position = position;  
	};
	//大きさの取得
	const DirectX::SimpleMath::Vector2& GetScale() { return m_scale; };
	//大きさの設定
	void SetScale(const DirectX::SimpleMath::Vector2& scale) 
	{ 
		m_scale = scale; 
	};

	//オブジェクトが有効かどうかの登録　true:有効  false:無効
	void SetIsEntityActive(const bool& isActive) { m_isEntityActive = isActive;  if(m_isEntityActive)OnEnable(); else OnDisable(); }
	//オブジェクトが有効かどうかの取得　true:有効  false:無効
	const bool& GetIsEntityActive() { return m_isEntityActive; }

	//更新が有効かどうかの登録　true:有効  false:無効
	void SetIsUpdateActive(const bool& isActive) { m_isUpdateActive = isActive; }
	//更新が有効かどうかの取得　true:有効  false:無効
	const bool& GetIsUpdateActive() { return m_isUpdateActive; }

	//描画が有効かどうかの登録　true:有効  false:無効
	void SetIsRenderActive(const bool& isActive) { m_isRenderActive = isActive; }
	//描画が有効かどうかの取得　true:有効  false:無効
	const bool& GetIsRenderActive() { return m_isRenderActive; }
	//有効になったら
	virtual void OnEnable()  {};
	//無効になったら
	virtual void OnDisable() {};

public:
	//コンストラクタ
	UIBaseEntity(CommonResources* resources,
				const DirectX::SimpleMath::Vector2&    scale, 
		        const DirectX::SimpleMath::Vector2&    position
		       ) ;

	//デストラクタ
	virtual ~UIBaseEntity();

	//初期化
	virtual void Initialize();
	//更新処理
	virtual void  Update(const float& elapsedTime);
	//描画
	virtual void Render();

private:

	// 共通リソース
	CommonResources* m_commonResources;
	//エンティティが有効かどうか　true:有効  false:無効
	bool m_isEntityActive;
	//更新が有効かどうか　true:有効  false:無効
	bool m_isUpdateActive;
	//描画が有効かどうか　true:有効  false:無効
	bool m_isRenderActive;

	//座標
	DirectX::SimpleMath::Vector2 m_position;
	//大きさ
	DirectX::SimpleMath::Vector2 m_scale;

};


