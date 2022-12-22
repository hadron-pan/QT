#include "enemyplane.h"

EnemyPlane::EnemyPlane()
{
    m_enemy.load(ENEMY_PATH);

    m_X = 0;
    m_Y = 0;

    m_Free = true;

    m_Speed = ENEMY_SPEED;

    m_Rect.setWidth(m_enemy.width());
    m_Rect.setHeight(m_enemy.height());
    m_Rect.moveTo(m_X,m_Y);
}

void EnemyPlane::updatePosition()
{
    //空闲状态，不计算坐标
    if(m_Free)
    {
        return;
    }

    m_Y += m_Speed;
    m_Rect.moveTo(m_X,m_Y);

    if(m_Y >= GAME_HEIGHT)
    {
        m_Free = true;
    }
}
