#pragma once
#include <unordered_map>
#include "Libraries/WataLib/Json.h"


namespace WataLib
{
	class Animation final
	{
	public:

		struct KeyFram
		{
			float Time;                                //経過時間
			DirectX::SimpleMath::Vector3 Data;
		};

		struct AnimationData
		{
			std::string TypeName;
			float TotalTime;                              //アニメーション全体の時間
			float Speed;								  //アニメーションの進行スピード
			bool IsLoop;								  //1アニメーションをループさせるか
			std::vector<KeyFram> Position;
			std::vector<KeyFram> Rotation;

		};

		struct FromTo
		{
			int Index = 0;
			KeyFram keyFrame;
		};

	public:

		const DirectX::SimpleMath::Vector3& GetPosition() { return m_position; };

		const DirectX::SimpleMath::Quaternion& GetRotation() { return m_rotation; }

	public:
		//コンストラクタ
		Animation();
		//デストラクタ
		~Animation();
		//更新処理
		bool Update(const float& elapsedTime);
		//座標のアニメーションの更新
		void PositionUpdate(const float& elapsedTime);
		//回転のアニメーションの更新
		void RotationUpdate(const float& elapsedTime);

		//アニメーション情報の登録
		void SetAnimationData(const std::string& animationType, const WataLib::Json::AnimationData& data, bool isNormalAnimation = false);
		//実行アニメーションの切り替え
		void ChangeAnimation(const std::string& animationType);
		//実行アニメーションの情報の初期化
		void InitializAnimationData(const std::string& animationType);
		//座標のキーフレームの切り替え
		void ChangePositionKeyFrame();
		//回転のキーフレームの切り替え
		void ChangeRotationKeyFrame();


	private:
		//アニメーションデータ
		std::unordered_map<std::string, AnimationData> m_animationData;
		//実行中のアニメーションデータ
		AnimationData m_currentAnimationData;
		//座標
		DirectX::SimpleMath::Vector3 m_position;
		//回転
		DirectX::SimpleMath::Quaternion m_rotation;
		//ペア座標
		std::pair<FromTo, FromTo> m_fromToPosition;
		//ペア回転
		std::pair<FromTo, FromTo> m_fromToRotation;
		//時間
		float m_time;
		//通常アニメーション
		std::string m_normalAnimationType;

	};
}

//animationDataには最低でも２つのデータが必要　ない場合でもアニメーション全体のはじめとおわりで０初期化の値を入れている


