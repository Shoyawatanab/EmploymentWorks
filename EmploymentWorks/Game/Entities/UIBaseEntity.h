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
	UIBaseEntity(CommonResources* resources) ;

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

};


