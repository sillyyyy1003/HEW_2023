#include "ColliderManager.h"
#include "Game.h"

GameObject* FindObj(std::vector<GameObject*> Vobject, std::string& name) {

    auto it = std::find_if(Vobject.begin(), Vobject.end(), [&name](GameObject* obj) {
        return obj->m_name == name;
        });

    return (it != Vobject.end()) ? *it : nullptr;
};



ColliderManager::~ColliderManager()
{
}

ColliderManager* ColliderManager::Get()
{
    static ColliderManager instance;
    return &instance;
}

void ColliderManager::Update(Collider* collider)
{
}

bool ColliderManager::isCollide(Collider* collider1, Collider* collider2)
{
    bool result = collider1->isCollision(collider2);
    return result;
}

void ColliderManager::Collision(std::vector<GameObject*> Vobject)
{
}

bool ColliderManager::ClearCollision(Collider_Dir dir, std::string name1, std::string name2, ShadowObject::SIZE size)
{
    
    GameObject* obj = FindObj(Game::Get()->GetObjectList(), name1);
    GameObject* targetObj = FindObj(Game::Get()->GetObjectList(), name2);
    
    if (obj->m_shadowCollider == nullptr || targetObj->m_shadowCollider == nullptr) {
        return false;
    }

    if (!obj->GetStill()) {
    
        return false;
    }
    else {
        //オブジェクトが接触したら
        if (obj->m_shadowCollider->isCollision(targetObj->m_shadowCollider)) {

            //位置は設定と一致する
            if (obj->m_shadowCollider->GetCollisionDir(targetObj->m_shadowCollider) == dir) {

                //大きさも同じ
                if (targetObj->m_shadow->m_size == size) {
                    return true;
                }
                
            }

        }
        return false;
    }
    

}
