#pragma once
#include "Libraries/WataLib/Singleton.h"

class GlobalGameData : public Singleton<GlobalGameData>
{
	friend class Singleton<GlobalGameData>;
public:

	//選択ステージ番号のセット
	void SetSelectStateNumber(int number) { m_selectStageNumber = number; }
	//ステージ番号の取得
	int GetSelectStateNumber() const { return m_selectStageNumber; }

public:
	//コンストラク
	GlobalGameData();
	//デストラクタ
	~GlobalGameData() override;


private:

	//選ばれたステージ番号
	int m_selectStageNumber;


};