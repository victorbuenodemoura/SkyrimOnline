#include <stdafx.h>
#include <Logic/States/ShardList.hpp>
#include <GameWorld.h>
#include <Overlay/Message.h>

#include <Game/MassiveMessageManager.hpp>

namespace Skyrim
{
	namespace Logic
	{
		namespace State
		{
			//--------------------------------------------------------------------------------
			ShardList::ShardList()
			{
				mShardList = boost::make_shared<Overlay::ShardList>(Overlay::TheSystem->GetGui());
				mShardList->Hide();
				mShardList->OnHost.connect(boost::bind(&ShardList::OnHost, this));
				mShardList->OnShardPick.connect(boost::bind(&ShardList::OnShardPick, this, _1));
			}
			//--------------------------------------------------------------------------------
			ShardList::~ShardList()
			{

			}
			//--------------------------------------------------------------------------------
			void ShardList::OnEnter()
			{
				TheGameWorld->SetMode(false);
				mShardList->Show();
			}
			//--------------------------------------------------------------------------------
			void ShardList::OnLeave()
			{
				mShardList->Hide();
			}
			//--------------------------------------------------------------------------------
			void ShardList::OnUpdate(uint32_t pDelta)
			{
				::Game::DisablePlayerControls(true,true,true,true,true,true,true,true,1);
				::Game::SetInChargen(true, true, false);

				mShardList->Update(0.0);
				Overlay::TheSystem->SetCursor(true);
			}
			//--------------------------------------------------------------------------------
			void ShardList::OnShardPick(const std::string& pShard)
			{
				System::Log::Debug(std::string("Shard picked : ") + pShard);
				Overlay::TheMessage->SetCaption("Joining is disabled for now !");
				Overlay::TheMessage->Show();

				/*TheMassiveMessageMgr->SetAddress(pShard);
				TheMassiveMessageMgr->SetPort(kGamePort);
				TheMassiveMessageMgr->BeginMultiplayer(false);*/
			}
			//--------------------------------------------------------------------------------
			void ShardList::OnHost()
			{
				System::Log::Debug("Hosting a server...");

				TheMassiveMessageMgr->SetPort(kGamePort);
				TheMassiveMessageMgr->BeginMultiplayer(true);

				TheGameWorld->SetState("InGame");
			}
			//--------------------------------------------------------------------------------
			bool ShardList::IsSwitchingAllowed()
			{
				return false;
			}
			//--------------------------------------------------------------------------------
		}
	}
}