#include "system/DialogSys.hpp"

#include "component/tag/AllTagComp.hpp"

#include "component/functional/LoadComp.hpp"
#include "component/functional/SizeComp.hpp"
#include "component/functional/TextComp.hpp"
#include "component/functional/PositionComp.hpp"
#include "component/functional/RenderableComp.hpp"
#include "component/functional/ClickableComp.hpp"
#include "component/functional/DialogComp.hpp"

#include "util/DialogParameters.hpp"
#include "util/FontContainer.hpp"

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics/Text.hpp>
#include <entt/entt.hpp>

#include "util/ApplicationParameters.hpp"

#include <sstream>
#include <iostream>

DialogSys::DialogSys(std::string systemConfigItem, entt::registry& rReg)
	: System(systemConfigItem)
	, m_state(State_t::WAITING)
    , mTimer(0)
    , k_mMaxTimer(30)
	, m_rReg(rReg)
{
	m_font = *FontContainer::GetFont(ApplicationParameters::k_fontPath);
}

void DialogSys::Update_()
{
    mTimer = std::min(mTimer + 1, k_mMaxTimer);
    switch (m_state)
    {
        case State_t::WAITING: ProcessWaiting(); return;
        case State_t::PRODUCING: ProcessProducing(); return;
        case State_t::FINISHED: ProcessFinished(); return;
        default: std::cout << "ERROR" << std::endl; return;
    }
}

void DialogSys::ProcessWaiting()
{
	mTimer = 0;
	m_rReg.view<DialogChainComp, StructuredDialogComp, TextComp, SizeComp>().each([&]
		(auto& textComp,
		auto& /*sizeComp*/)
	{
		std::istringstream iss(textComp.m_text);
		do
		{
			std::string subs;
			iss >> subs;
			if (subs.empty())
				break;
			if (subs.front() == '*' && subs.back() == '*')
			{
				if (m_pDialogContainer)
				{
					m_dialogContainerList.emplace_back(*m_pDialogContainer);
				}
				m_pDialogContainer = std::make_shared<DialogContainer>();
				m_pDialogContainer->portraitName = subs.substr(1, subs.length() - 2);
				m_pDialogContainer->contentList = std::list<std::list<std::string>>({{""}});
				continue;
			}
			if (subs.front() == '|' && subs.back() == '|')
			{
				if (!m_pDialogContainer)
				{
					m_pDialogContainer = std::make_shared<DialogContainer>();
				}
				m_pDialogContainer->nextFileToLoad = subs.substr(1, subs.length() - 2);
				m_dialogContainerList.emplace_back(*m_pDialogContainer);
				continue;
			}
			if (subs == "\\")
			{
				if (!m_pDialogContainer)
				{
					m_pDialogContainer = std::make_shared<DialogContainer>();
				}
				m_dialogContainerList.emplace_back(*m_pDialogContainer);
				continue;
			}

			sf::Text testText(m_pDialogContainer->contentList.back().back() + std::string(subs), m_font, static_cast<unsigned int>(DialogParameters::k_fTextHeight));
			int textActualWidth = static_cast<int>(testText.getLocalBounds().width);
			if (textActualWidth > DialogParameters::k_fTextWidth)
			{
				if (m_pDialogContainer->contentList.back().size() > 2)
				{
					m_pDialogContainer->contentList.push_back({""});
				}
				else
				{
					m_pDialogContainer->contentList.back().push_back("");
				}
			}
			m_pDialogContainer->contentList.back().back() += std::string(" ") + subs;
		}
		while (iss);
		m_state = State_t::PRODUCING;
	});
}

void DialogSys::ProcessProducing()
{
	bool dialogExists1 = false;
	m_rReg.view<DialogComp>().each([&](auto& /*dialogComp*/)
	{
		dialogExists1 = true;
	});
    if (m_dialogContainerList.empty() && !dialogExists1)
    {
        m_state = State_t::FINISHED;
    }
    else
    {
		bool dialogExists = false;
		m_rReg.view<DialogComp>().each([&](auto& /*dialogComp*/)
		{
			dialogExists = true;
		});
		if (!dialogExists)
		{
			auto entity = m_rReg.create();
			m_rReg.emplace<ClickableComp>(entity);
			auto& dialogComp = m_rReg.emplace<DialogComp>(entity);
			m_rReg.emplace<RenderableComp>(entity);

			m_rReg.emplace<SizeComp>(entity).m_size =
			{
				1714, 174
			};
			m_rReg.emplace<PositionComp>(entity).m_position =
			{
				960, 990
			};


			dialogComp.m_portrait = m_dialogContainerList.front().portraitName;
			for (auto& thingToAdd : m_dialogContainerList.front().contentList.front())
			{
				dialogComp.m_dialogList.emplace_back(thingToAdd);
			}
		}
    }
	bool clicked = false;

	m_rReg.view<ClickableComp, DialogComp>().each([&](auto& clickableComp, auto& /*dialogComp*/)
	{
		if (clickableComp.m_bLeftClicked)
		{
			clicked = true;
		}
	});

    if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && mTimer == k_mMaxTimer) || clicked)
    {
        mTimer = 0;
		bool dialogExists = false;
		m_rReg.view<DialogComp>().each([&](auto& /*dialogComp*/)
		{
			dialogExists = true;
		});
        if (dialogExists)
        {
			m_rReg.view<DialogComp>().each([&](
				auto entity,
				auto& /*dialogComp*/)
			{
				m_rReg.destroy(entity);
				if (m_dialogContainerList.front().nextFileToLoad != "")
				{
					auto loadEntity = m_rReg.create();
					m_rReg.emplace<LoadComp>(loadEntity) =
					{
						m_dialogContainerList.front().nextFileToLoad
					};
				}
			});
        	if (!m_dialogContainerList.empty())
			{
				if (m_dialogContainerList.front().contentList.size() > 1)
				{
					m_dialogContainerList.front().contentList.pop_front();
				}
				else
				{
					m_dialogContainerList.pop_front();
				}
			}
        }
    }
}

void DialogSys::ProcessFinished()
{
	m_rReg.view<StructuredDialogComp>().each([&](auto entity)
	{
		m_rReg.destroy(entity);
	});
	m_dialogContainerList.clear();
	m_pDialogContainer = nullptr;
	std::cout << "Finished" << std::endl;
	m_state = State_t::WAITING;
}
