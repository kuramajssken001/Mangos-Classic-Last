/*####################
## npc_training_dummy     //ÑµÁ·¼ÙÈË
######################*/
#include "precompiled.h"
#include "Spell.h"

#define OUT_OF_COMBAT_TIME 5000

struct npc_training_dummyAI : public ScriptedAI
 {
	npc_training_dummyAI(Creature* pCreature) : ScriptedAI(pCreature) { Reset(); }
	
	uint32 combat_timer;
	
	void Reset() override
	 {
		combat_timer = 0;
		}
	
		void DamageTaken(Unit* pDoneBy, uint32 &uiDamage) override
		 {
		combat_timer = 0;
		}
	
		void UpdateAI(const uint32 diff) override
		 {
		if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
			 return;
		
			m_creature->ModifyHealth(m_creature->GetMaxHealth());
		
			combat_timer += diff;
		if (combat_timer > OUT_OF_COMBAT_TIME)
			 EnterEvadeMode();
		}
};

CreatureAI* GetAI_npc_training_dummy(Creature* pCreature)
{
	return new npc_training_dummyAI(pCreature);
}

void AddSC_npc_training_dummy()
 {
	Script* pNewScript;
		
	pNewScript = new Script;
	pNewScript->Name = "npc_training_dummy";
	pNewScript->GetAI = &GetAI_npc_training_dummy;
	pNewScript->RegisterSelf();
	
}