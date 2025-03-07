#pragma once
/*
	@file	TargetMarker.h.h
	@brief	プレイシーンクラス
*/
#pragma once
#include "pch.h"
#include  "Game/Entities/EnemyEntity.h"
#include "Game/Interface/IObserver.h"
// 前方宣言
class CommonResources;
namespace WataLib
{
	class TPS_Camera;
	class DrawTexture;

}



class TargetMarker : public IObserver

{
public:

	//ターゲットの中心kらの距離
	static constexpr float RANGE{ 200.0f };

public:

	bool GetIsLockOn() { return m_isLockOn; }

	DirectX::SimpleMath::Vector3 GetTargetPosition() { return m_target; }


public:
	TargetMarker();
	~TargetMarker();

	void Initialize(CommonResources* resources);
	void Update(float elapsedTime);
	void Render();

	//クラスに必要な情報（ポインタ）を登録する
	void AddPointer(WataLib::TPS_Camera* tpsCamera);




	DirectX::SimpleMath::Vector2 FilterWithinRange(const std::vector<DirectX::SimpleMath::Vector3>& points, const DirectX::SimpleMath::Vector2& center, float range);

	//void AddTargetObject(ICharacter* object) { m_targetObject.push_back(object); }

	void AddTargetObject(std::vector<std::unique_ptr<EnemyEntity>>& object)
	{ 
		for (auto& ob : object)
		{
			m_targetObject.push_back(ob.get());
		}
	}


	//IObserver
//通知時に呼ばれる関数
	void Notify(EventParams::EventType type, void* datas)  override;


	//ワールド座標をスクリーン座標に変換する
	DirectX::SimpleMath::Vector2 WorldToScreen(const DirectX::SimpleMath::Vector3& worldPos,
		const DirectX::SimpleMath::Matrix& worldMatrix,
		const DirectX::SimpleMath::Matrix& viewMatrix,
		const DirectX::SimpleMath::Matrix& projectionMatrix,
		int screenWidth, int screenHeight);


private:
	//宣言
// 共通リソース
	CommonResources* m_commonResources;

	std::unique_ptr<WataLib::DrawTexture> m_marker;


	WataLib::TPS_Camera* m_tpsCamera;
	//構えているか
	bool m_isTargetMarker;
	//範囲内にターゲットがいるかどうか
	bool m_isLockOn;

	std::vector<EnemyEntity*> m_targetObject;

	std::pair<int, int> m_windowSize;

	DirectX::SimpleMath::Vector3 m_target;


};
