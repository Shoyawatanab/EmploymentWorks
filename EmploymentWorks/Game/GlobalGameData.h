#pragma once
#include "Libraries/WataLib/Singleton.h"

class GlobalGameData : public Singleton<GlobalGameData>
{
	friend class Singleton<GlobalGameData>;
public:

	//�I���X�e�[�W�ԍ��̃Z�b�g
	void SetSelectStateNumber(int number) { m_selectStageNumber = number; }
	//�X�e�[�W�ԍ��̎擾
	int GetSelectStateNumber() const { return m_selectStageNumber; }

public:
	//�R���X�g���N
	GlobalGameData();
	//�f�X�g���N�^
	~GlobalGameData() override;


private:

	//�I�΂ꂽ�X�e�[�W�ԍ�
	int m_selectStageNumber;


};