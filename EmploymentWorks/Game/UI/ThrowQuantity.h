#pragma once
#include "Game/Entities/UIBaseEntity.h"
#include "Game/Interface/IObserver.h"

class UserInterface;

class ThrowQuantity : public UIBaseEntity , public IObserver<GamePlayMessageType>
{

private:

	//状態
	enum  class State
	{
		ONE,     //１つなげる
		THREE	 //３つなげる
	};


	static constexpr DirectX::SimpleMath::Vector2 THROW_QUANTITYUI_POSITION{1100, 670};
	static constexpr DirectX::SimpleMath::Vector2 THROW_QUANTITYUI_SCALE{0.15f, 0.15f};

	static constexpr DirectX::SimpleMath::Vector2 THROW_QUANTITYUI_OFFSET_POSITION{100, 0};

	static constexpr DirectX::SimpleMath::Vector2 THROW_QUANTITYUI_UP_POSITION{0, -20};


public:


public:
	//コンストラクタ
	ThrowQuantity(CommonResources* resources);
	//デストラクタ
	~ThrowQuantity();

	//初期化
	void Initialize();
	//更新処理
	void  Update(const float& elapsedTime);
	//描画
	void Render();



private:
	//IObserver
	//通知時に呼ばれる関数
	void Notify(const Telegram<GamePlayMessageType>& telegram)  override;


	//状態の切り替え
	void ChangeState();

private:
	//状態
	State m_state;

	//ブーメランの投げる個数UI
	std::vector<std::unique_ptr<UserInterface>> m_throwQuantityUI;


};