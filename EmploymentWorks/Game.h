//
// Game.h
//

#pragma once

#include"GameBase/Common/DeviceResources.h"
#include"GameBase/Common/StepTimer.h"

// ��include�̒ǋL��
#include "GameBase/Common/Commons.h"
#include "GameBase/Scene/Scene.h"
#include "Game/Scene/SceneManager.h"
#include "Libraries/MyLib/DebugString.h"
#include "Libraries/MyLib/InputManager.h"
#include "Game/Fade/FadeManager.h"
#include "GameBase/Manager/SoundManager.h"

// A basic game implementation that creates a D3D11 device and
// provides a game loop.
class Game final : public DX::IDeviceNotify
{
public:

    Game() noexcept(false);
    ~Game() = default;

    Game(Game&&) = default;
    Game& operator= (Game&&) = default;

    Game(Game const&) = delete;
    Game& operator= (Game const&) = delete;

    // Initialization and management
    void Initialize(HWND window, int width, int height);

    // Basic game loop
    void Tick();

    // IDeviceNotify
    void OnDeviceLost() override;
    void OnDeviceRestored() override;

    // Messages
    void OnActivated();
    void OnDeactivated();
    void OnSuspending();
    void OnResuming();
    void OnWindowMoved();
    void OnDisplayChange();
    void OnWindowSizeChanged(int width, int height);

    // Properties
    void GetDefaultSize( int& width, int& height ) const noexcept;

private:

    void Update(DX::StepTimer const& timer);
    void Render();

    void Clear();

    void CreateDeviceDependentResources();
    void CreateWindowSizeDependentResources();

    // Device resources.
    std::unique_ptr<DX::DeviceResources>    m_deviceResources;

    // Rendering loop timer.
    DX::StepTimer                           m_timer;


    // ���ǋL�R�R���火������

    // �R�����X�e�[�g
    std::unique_ptr<DirectX::CommonStates>  m_commonStates;


    // �f�o�b�O�X�g�����O
    std::unique_ptr<mylib::DebugString>     m_debugString;

    // ���̓}�l�[�W��
    std::unique_ptr<mylib::InputManager>    m_inputManager;

    // �V�[���}�l�[�W��
    std::unique_ptr<SceneManager>           m_sceneManager;


    //�t�F�[�h�}�l�[�W���[
    FadeManager* m_fadeManager;
    //�T�E���h�}�l�[�W���[
    SoundManager* m_soundManager;

    // ���ǋL�R�R�܂Ł�������

    // �t���X�N���[���֘A
private:
    // ���ǋL
    BOOL m_fullScreen;

public:
    // �ǋL
    // ��ʃ��[�h��ύX����֐��iTRUE:�t���X�N���[���j
    void SetFullscreenState(BOOL value)
    {
        m_fullScreen = value;
        m_deviceResources->GetSwapChain()->SetFullscreenState(value, nullptr);
        if (value) m_deviceResources->CreateWindowSizeDependentResources();
    }

};
