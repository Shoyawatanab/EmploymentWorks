#include "pch.h"
#include "UIManager.h"
#include "GameBase/Component/UI/ButtonComponent.h"
#include "GameBase/Common/Commons.h"
#include "GameBase/Actor.h"
#include "GameBase/Component/Components.h"
#include "GameBase/Screen.h"

/// <summary>
/// �R���X�g���N
/// </summary>
UIManager::UIManager()
	:
	m_buttom{}
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
UIManager::~UIManager()
{
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="deltaTime">�X�V����</param>
void UIManager::Update(const float& deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
	using namespace DirectX;
	using namespace DirectX::SimpleMath;

	//�Ȃ����
	if(m_buttom.empty()) 
	{
		return;
	}

	const auto& state = CommonResources::GetInstance()->GetInputManager()->GetMouseState();


	RECT rect{ CommonResources::GetInstance()->GetDeviceResources()->GetOutputSize() };

	//��ʃT�C�Y�̎擾
	float widht = static_cast<float>(CommonResources::GetInstance()->GetDeviceResources()->GetOutputSize().right);
	float height = static_cast<float>(CommonResources::GetInstance()->GetDeviceResources()->GetOutputSize().bottom);

	Vector2 mousePosition = Vector2(state.x * Screen::WIDTH / widht, state.y * Screen::HEIGHT / height);

	for (auto& buttom : m_buttom)
	{
		//�}�E�X�ƃ{�^���͈͂̔���
		if (CheckInRange(mousePosition, buttom))
		{
			buttom->InRange();

			const auto& tracker = CommonResources::GetInstance()->GetInputManager()->GetMouseTracker();
			
			if (tracker->leftButton == Mouse::ButtonStateTracker::ButtonState::PRESSED)
			{

				buttom->OnClick();

			}
			break;
		}
		else
		{
			buttom->OutOfRange();
		}
	}

}

/// <summary>
/// �{�^���̒ǉ�
/// </summary>
/// <param name="buttom"></param>
void UIManager::AddButtomComponent(ButtonComponent* buttom)
{

	m_buttom.push_back(buttom);

}

/// <summary>
/// �{�^���͈͓����̃`�F�b�N
/// </summary>
/// <param name="mousePosition">�}�E�X���W</param>
/// <param name="buttom">�{�^���R���|�[�l���g</param>
/// <returns>true�F���������@false�F�������ĂȂ�</returns>
bool UIManager::CheckInRange(const DirectX::SimpleMath::Vector2& mousePosition, ButtonComponent* buttom)
{
	using namespace DirectX::SimpleMath;

	auto comp = buttom->GetActor()->GetComponent<ImageComponent>();

	Vector2 position = Vector2(buttom->GetActor()->GetTransform()->GetPosition().x,buttom->GetActor()->GetTransform()->GetPosition().y);
	Vector2 scale = Vector2(comp->GetWidth(),comp->GetHeight());

	// �l�p�`�̋��E���W���v�Z
	float rectLeft = position.x - scale.x / 2;
	float rectRight = position.x + scale.x / 2;
	float rectTop = position.y - scale.y / 2;
	float rectBottom = position.y + scale.x / 2;

	// �~�̒��S�ɍł��߂��l�p�`�̓_�����߂�
	float closestX = std::max(rectLeft, std::min(mousePosition.x, rectRight));
	float closestY = std::max(rectTop, std::min(mousePosition.y, rectBottom));

	// �~�̒��S�ƍŋߐړ_�̋������v�Z
	Vector2 diff = mousePosition - Vector2(closestX, closestY);
	float distanceSquared = diff.LengthSquared();

	// �����蔻��i�����̓�悪���a�̓��ȉ��Ȃ�Փˁj
	return distanceSquared <= (5 * 5);
}
