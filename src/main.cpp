// stolen from https://github.com/TheSillyDoggo/GeodeMenu/blob/e21637af2559d287b50ed92e8f3b400bdcbfe4c5/src/Hacks/CommentHistory.cpp bc why not
// just decided to make a standalone mod out of it
// I also added some of my own features

#include <Geode/Geode.hpp>
#include <Geode/modify/ProfilePage.hpp>

using namespace geode::prelude;

class $modify(MyProfilePage, ProfilePage)
{
	void loadPageFromUserInfo(GJUserScore* p0)
	{
		int commentHistoryState = p0->m_commentHistoryStatus;
		p0->m_commentHistoryStatus = 0;
		ProfilePage::loadPageFromUserInfo(p0);

		if (Mod::get()->getSettingValue<bool>("enable")) {
			if ((commentHistoryState == 1 || commentHistoryState == 2) && Mod::get()->getSettingValue<bool>("change-icon")) { // if they only activated it for their friends / to nobody (lazy to check if you are friend with this user)
				auto mainMenu = this->m_mainLayer->getChildByID("main-menu");
				auto commentHistoryButton = mainMenu->getChildByID("comment-history-button");
				if (typeinfo_cast<CCMenuItemSpriteExtra*>(commentHistoryButton) == nullptr) {
					log::error("typeinfo_cast = nullptr");
					Notification::create("Couldn't change 'comment history button' opacity", NotificationIcon::Warning)->show();
				} else {
					typeinfo_cast<CCMenuItemSpriteExtra*>(commentHistoryButton)->setOpacity(127);
				}
				
			}

			p0->m_commentHistoryStatus = commentHistoryState;
		}
	}
};