#include "pch.h"
#include "InputMessenger.h"

/// <summary>
/// �R���X�g���N
/// </summary>
InputMessenger::InputMessenger()
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
InputMessenger::~InputMessenger()
{
	
}

/// <summary>
/// �ʒm�𑗂�
/// </summary>
/// <param name="keyboardState"></param>
void InputMessenger::Notify(const DirectX::Keyboard::State& keyboardState)
{
	// �u�ώ@�҃��X�g�v����L�[�ƃL�[�͈̔�(�J�n�C���f�b�N�X�ƏI���C���f�b�N�X)�����o��
	for (const auto& keyRange : m_keysRangeList)
	{
		// �ώ@�҂��������ׂ��L�[���ǂ����𒲂ׂ�
		if (keyboardState.IsKeyDown(keyRange.first))
		{
			// �L�[�̊J�n�C���f�b�N�X����I���C���f�b�N�X�܂ł̃C���f�b�N�X���o��
			for (auto range = keyRange.second[0].first; range <= keyRange.second[0].second; range++)
			{

				// �ώ@�҂̒ʒm�֐��ɉ�������ꂽ�L�[��ʒm����
				m_keybordList[range].second(m_keybordList[range].first);

			}
		}
	}

}

/// <summary>
/// �o�^
/// </summary>
/// <param name="key">�L�[�^�C�v</param>
/// <param name="function">�֐�</param>
void InputMessenger::Rigister(const DirectX::Keyboard::Keys& key
	, std::function<void(const DirectX::Keyboard::Keys& key)> function)
{
	m_keybordList.emplace_back(std::make_pair(key, function));

}

void InputMessenger::SortObserverList()
{
	// �u�ώ@�҃��X�g�v���L�[�Ń\�[�g����
	std::sort(
		m_keybordList.begin(),
		m_keybordList.end(),
		[](const std::pair<DirectX::Keyboard::Keys, std::function<void(const DirectX::Keyboard::Keys& key)>>& a
			, const std::pair<DirectX::Keyboard::Keys, std::function<void(const DirectX::Keyboard::Keys& key)>>& b)
		{
			return a.first < b.first;
		});

}

void InputMessenger::CreateKeyRangeList()
{
	// �J�n�C���f�b�N�X��ݒ肷��
	size_t  startIndex = 0;
	// �u�L�[�͈̓��X�g�v�Ńf�[�^�����݂���ꍇ�́u�L�[�͈̓��X�g�v���N���A����
	if (m_keysRangeList.size())
		m_keysRangeList.clear();
	// �u�ώ@�҃��X�g�v�̊J�n�L�[�����݂̃L�[�ɂ���
	DirectX::Keyboard::Keys currentKey = m_keybordList[startIndex].first;
	// �u�ώ@�҃��X�g�v�̊J�n����I���܂ŌJ��Ԃ�
	for (size_t index = 1; index < m_keybordList.size(); index++)
	{
		// �u�ώ@�҃��X�g�v�̃L�[�ƌ��݂̃L�[���������Ȃ��Ȃ����ꍇ
		if (m_keybordList[index].first != currentKey)
		{
			// �L�[�ƃL�[�͈̔�(�J�n�C���f�b�N�X�ƏI���C���f�b�N�X)���u�L�[�͈̓��X�g�v�ɒǉ�����
			m_keysRangeList[currentKey].push_back(std::make_pair(startIndex, index - 1));
			// �C���f�b�N�X���J�n�C���f�b�N�X�ɐݒ肷��
			startIndex = index;
			// �u�ώ@�҃��X�g�v�̃L�[�����݂̃L�[�ɐݒ肷��
			currentKey = m_keybordList[index].first;
		}
	}
	// �L�[�ƃL�[�͈̔�(�J�n�C���f�b�N�X�ƏI���C���f�b�N�X)���u�L�[�͈̓��X�g�v�ɒǉ�����
	m_keysRangeList[currentKey].push_back(std::make_pair(startIndex, m_keybordList.size() - 1));

}
