#pragma once

class Actor;
class CommonResources;
class RenderManager;
class CollisionManager2;
class RigidbodyManager;
class Camera;

class Scene
{
public:
	// シーンID
	enum class SceneID : unsigned int
	{
		NONE,
		TITLE,
		PLAY,
		STAGESELECT,
		RESULT
	};

public:

	//マネージャーの取得
	RenderManager* GetRenderMangaer() { return m_renderMangaer.get(); }
	CollisionManager2* GetCollisionManager() { return m_collisionManager.get(); }
	RigidbodyManager* GetRigidbodyManager() { return m_rigidbodyManager.get(); }

	//カメラの取得
	virtual Camera* GetCamera() const = 0;

public:
	// コンストラクタ、デストラクタ
	Scene();
	virtual ~Scene();
	// 初期化
	virtual void Initialize() = 0;
	// 更新処理
	void Update(float deltaTime);
	// 派生クラス更新処理
	virtual void SceneUpdate(float deltaTime) = 0;
	// 描画処理
	void Render();
	virtual void SceneRender() = 0;
	// 終了処理
	virtual void Finalize() = 0;
	
	// シーンIDを取得
	virtual SceneID GetSceneID() const = 0;
	// シーン切り替え
	void ChangeScene(SceneID nextScene) { m_nextSceneID = nextScene; }
	// 次シーンID取得
	SceneID GetNextSceneID() { return m_nextSceneID; }
	// アクター削除フラグをオンにする
	void ActorDestroyOn() { m_isActorDestroy = true; }

public:
	// アクター追加
	template<typename Act , typename...Args>
	Act* AddActor(Args&&... args);
	// アクター削除
	void RemoveActor();


private:
	// 次シーンID
	SceneID m_nextSceneID;
	// チェンジフラグ
	bool m_isChangeScene;
	// 管理アクター
	std::vector<std::unique_ptr<Actor>> m_actors;
	// 保留アクター
	std::vector<std::unique_ptr<Actor>> m_holdActors;
	// アップデート確認用フラグ
	bool m_updateNow;
	// アクター削除フラグ
	bool m_isActorDestroy;

	//描画のマネージャー
	std::unique_ptr<RenderManager> m_renderMangaer;
	//当たり判定のマネージャー
	std::unique_ptr<CollisionManager2> m_collisionManager;
	//リジットボディーマネージャー
	std::unique_ptr<RigidbodyManager> m_rigidbodyManager;




};

template<typename Act , typename...Args>
inline Act* Scene::AddActor(Args&&...args)
{
	// アクターの生成
	auto actor = std::make_unique<Act>(std::forward<Args>(args)...);
	// 戻り値
	Act* act = actor.get();
	// アップデート中の場合
	if (m_updateNow)
	{
		m_holdActors.push_back(std::move(actor));
	}
	else
	{
		m_actors.push_back(std::move(actor));
	}
	return act;
}

