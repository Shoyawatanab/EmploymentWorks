#include "pch.h"
#include "Game/BehaviorTree/Root.h"
#include "Root.h"



Root::Root()
{

}

Root::~Root()
{
	Finalize();
}

void Root::Initialize()
{

}


IBehaviorNode::State Root::Update(float elapsedTime)
{

	return 	m_childNode->Update(elapsedTime);

}

IBehaviorNode::State Root::RunningUpdate(float elapsedTime)
{


	return	m_childNode->RunningUpdate(elapsedTime);

}

void Root::Render()
{

}

void Root::Finalize()
{
}

void Root::AddNode(std::unique_ptr<IBehaviorNode> node)
{
	node->Initialize();

	m_childNode = std::move(node);

}


