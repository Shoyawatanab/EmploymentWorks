#include "pch.h"
#include "PlayerDust.h"
#include "GameBase/Component/Components.h"

PlayerDust::PlayerDust(Scene* scene)
	:
	Actor(scene)
{

	auto a = AddComponent<ParticleSystem>(this);

	GetTransform()->SetPosition(DirectX::SimpleMath::Vector3(0, -0.5f, 0));

	ParticleSystem::MainModule setting;
	setting.LifeTime = { 1 };
	setting.StartSpeed = 0.1f;
	setting.MinSize = { DirectX::SimpleMath::Vector3(0.2f,0.2f,0.2f) };
	setting.MaxSize = { DirectX::SimpleMath::Vector3(0.3f,0.3f,0.3f) };
	setting.MaxParticles = 10000;
	setting.SimulationSpaceType = ParticleSystem::SimulationSpaceType::World;
	setting.StartColor = { DirectX::SimpleMath::Color(1.0f,1.0f,1.0f,1.0f) };

	auto cone = std::make_shared<ShapeCone>(0.1f, 30, DirectX::SimpleMath::Vector3::Up);

	ParticleSystem::EmissionModule emitter;
	emitter.RateOverTime = 2;


	a->SetMainModule(setting);
	a->SetEmission(emitter);
	a->SetShape(cone);
	//a->AddBurst(0, 100);

}

PlayerDust::~PlayerDust()
{
}
