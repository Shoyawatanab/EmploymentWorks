#pragma once

//	前方宣言
class CommonResources;

namespace WataLib
{


	/// <summary>
	/// DirectX::Modelのラッパークラス
	/// </summary>
	class Model3D
	{
	//	ゲッター
	public:

		//	座標の取得
		const DirectX::SimpleMath::Vector3& GetPosition() const { return m_position; }
		//	スケールの取得
		const DirectX::SimpleMath::Vector3& GetScale() const { return m_scale; }
		//	回転の取得
		const DirectX::SimpleMath::Quaternion& GetRotate() const { return m_rotate; }

	//	セッター
	public:

		//	座標の設定
		void SetPosition(const DirectX::SimpleMath::Vector3& position) { m_position = position; }
		//	スケールの設定
		void SetScale(const DirectX::SimpleMath::Vector3& scale) { m_scale = scale; }
		//	回転の設定
		void SetRotate(const DirectX::SimpleMath::Quaternion& rotate) { m_rotate = rotate; }

	//	公開関数
	public:

		//	コンストラクタ
		Model3D();
		//	デストラクタ
		~Model3D() = default;

		//	開始関数
		void Initialize
		(
			CommonResources* resouce, const wchar_t* szFileName,DirectX::SimpleMath::Vector3 Pos,DirectX::SimpleMath::Vector3 Scale
		);

		//	描画関数
		void Render(DirectX::CXMMATRIX view, DirectX::CXMMATRIX projection);

	//	内部パラメータ
	private:
		//モデル
		std::unique_ptr<DirectX::Model> m_model;


		DirectX::SimpleMath::Vector3	m_position;	//	座標
		DirectX::SimpleMath::Vector3	m_scale;	//	スケール
		DirectX::SimpleMath::Quaternion m_rotate;	//	回転

		CommonResources* m_commonResources;

	};
}