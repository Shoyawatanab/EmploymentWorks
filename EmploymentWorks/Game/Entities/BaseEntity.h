/*
* プレイヤクラス　
*/

#pragma once


// 前方宣言
class CommonResources;

class BaseEntity
{
public:
	//共通リソース
	CommonResources* GetCommonResources() { return m_commonResources; }
	//IDの取得
	 int GetID() const { return m_id; }

	 static int GetNextID() { return m_nextId; };

	//座標の取得
	const DirectX::SimpleMath::Vector3& GetPosition() { return m_position ; };
	//座標の設定
	void SetPosition(const DirectX::SimpleMath::Vector3& position) 
	{ 
		m_position = position;  
		if (!m_parent) { m_localPosition = position; }; 
	};
	//大きさの取得
	const DirectX::SimpleMath::Vector3& GetScale() { return m_scale; };
	//大きさの設定
	void SetScale(const DirectX::SimpleMath::Vector3& scale) 
	{ 
		m_scale = scale; 
		if (!m_parent) { m_localScale = scale; };

	};

	//回転の取得
	const DirectX::SimpleMath::Quaternion& GetRotation() { return m_rotation; };
	//回転の設定
	void SetRotation(const DirectX::SimpleMath::Quaternion& rotation) 
	{ 
		m_rotation = rotation; 
		if (!m_parent) { m_rotation = rotation; };

	};
	//行列の取得
	const DirectX::SimpleMath::Matrix& GetWorldMatrix() { return m_worldMatrix; };
	//行列の設定
	void SetWorldMatrix(const DirectX::SimpleMath::Matrix& matrix) 
	{ 
		m_worldMatrix = matrix;
		if(!m_parent) { m_localMatrix = matrix; };

	}

	//ローカル座標の取得
	const DirectX::SimpleMath::Vector3& GetLocalPosition() { return m_parent ? m_localPosition : m_position; };
	//ローカル座標の設定
	void SetLocalPosition(const DirectX::SimpleMath::Vector3& position) { m_parent  ? m_localPosition = position : m_position = position; };
	//ローカル大きさの取得
	const DirectX::SimpleMath::Vector3& GetLocalScale() { return m_parent ? m_localScale : m_scale; };
	//ローカル大きさの設定
	void SetLocalScale(const DirectX::SimpleMath::Vector3& scale) { m_parent  ? m_localScale = scale : m_scale = scale  ; };
	//ローカル回転の取得
	const DirectX::SimpleMath::Quaternion& GetLocalRotation() { return m_parent  ? m_localRotation : m_rotation; };
	//ローカル回転の設定
	void SetLocalRotation(const DirectX::SimpleMath::Quaternion& rotation) { m_parent  ? m_localRotation = rotation :m_rotation = rotation ; };
	//速度の取得
	const DirectX::SimpleMath::Vector3& GetVelocity() { return m_velocity; }
	//速度の登録
	void SetVelocity(const DirectX::SimpleMath::Vector3& velocity) { m_velocity = velocity; }
	//重量が有効かどうか　true:有効  false:無効
	const bool GetIsGravity() { return m_isGravity; }
	//重力が有効かの登録 true:有効  false:無効
	void SetIsGravity(const bool& enabled) { m_isGravity = enabled; }

	//親の取得
	BaseEntity* GetParent() { return m_parent; }
	//親の登録
	void SetParent(BaseEntity* parent);
	//親がいるかどうか　true:あり  false:なし
	bool GetIsParent() { return m_isParent; }


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
	BaseEntity(CommonResources* resources,
				const DirectX::SimpleMath::Vector3&    scale, 
		        const DirectX::SimpleMath::Vector3&    position,
		        const DirectX::SimpleMath::Quaternion& rotation) ;

	//デストラクタ
	virtual ~BaseEntity();

	//初期化
	virtual void Initialize();
	//更新処理
	virtual void  Update(const float& elapsedTime);
	//描画
	virtual void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection);

private:
	// 共通リソース
	CommonResources* m_commonResources;
	//id
	int m_id;

	static int m_nextId;
	//エンティティが有効かどうか　true:有効  false:無効
	bool m_isEntityActive;
	//更新が有効かどうか　true:有効  false:無効
	bool m_isUpdateActive;
	//描画が有効かどうか　true:有効  false:無効
	bool m_isRenderActive;

	//座標
	DirectX::SimpleMath::Vector3 m_position;
	//大きさ
	DirectX::SimpleMath::Vector3 m_scale;
	//回転
	DirectX::SimpleMath::Quaternion m_rotation;
	//行列
	DirectX::SimpleMath::Matrix m_worldMatrix;

	//親クラス
	BaseEntity* m_parent;
	//親があるかどうか
	bool m_isParent;

	//ローカル座標
	DirectX::SimpleMath::Vector3 m_localPosition;
	//ローカル大きさ
	DirectX::SimpleMath::Vector3 m_localScale;
	//ローカル回転
	DirectX::SimpleMath::Quaternion m_localRotation;
	//ローカル行列
	DirectX::SimpleMath::Matrix m_localMatrix;
	//重力があるかどうか
	bool m_isGravity;
	//速度
	DirectX::SimpleMath::Vector3 m_velocity;
	//重力
	float m_gravity;

};


