#include "system/DialogSys.hpp"

#include "component/tag/AllTagComp.hpp"

#include "component/functional/LoadComp.hpp"
#include "component/functional/SizeComp.hpp"
#include "component/functional/TextComp.hpp"
#include "component/functional/PositionComp.hpp"
#include "component/functional/RenderableComp.hpp"
#include "component/functional/ClickableComp.hpp"

#include "util/ApplicationParameters.hpp"
#include "util/EntityLoaderUtils.hpp"
#include "util/Helper.hpp"

#include <entt/entt.hpp>

#include <SFML/Graphics.hpp>

#include <iostream>

DialogSys::DialogSys(entt::registry& rReg)
	: m_rReg(rReg)
	, m_dialogSysState(DialogSysState_t::WAITING)
{}

void DialogSys::Update()
{
	switch (m_dialogSysState)
	{
		case DialogSysState_t::WAITING: UpdateWaitingState_(); break;
		case DialogSysState_t::PRODUCING: UpdateProducingState_(); break;
		case DialogSysState_t::PENDING: UpdatePendingState_(); break;
		case DialogSysState_t::LOADING: UpdateLoadingState_(); break;
		case DialogSysState_t::FINISHED: UpdateFinishedState_(); break;
		default: std::cout << "Dialog sys state broken!" << std::endl; break;
	}
}

void DialogSys::UpdateWaitingState_()
{
	bool bDialogChainFound = false;
	m_rReg.view<DialogChainComp>().each([&bDialogChainFound](auto entity)
	{
		bDialogChainFound = true;
	});
	m_dialogSysState = (bDialogChainFound ? DialogSysState_t::PRODUCING : DialogSysState_t::WAITING);
}

void DialogSys::UpdateProducingState_()
{
	m_rReg.view<DialogChainComp, RandomComp, TextComp, SizeComp>().each([&]
		(auto entity,
		auto& textComp,
		auto& sizeComp)
	{
		auto fragmentEntity = m_rReg.create();
		m_rReg.emplace<DialogChainFragmentComp>(fragmentEntity);

		std::string textFragment = textComp.m_text.substr(0, textComp.m_text.find(ApplicationParameters::k_dialogDelimiter));
		textComp.m_text = (textComp.m_text.find(ApplicationParameters::k_dialogDelimiter) == std::string::npos) ?
			"" :
			textComp.m_text.substr(textComp.m_text.find(ApplicationParameters::k_dialogDelimiter) + 1);

		if (textFragment.at(0) == ApplicationParameters::k_dialogEscapeChar &&
			textFragment.at(textFragment.length() - 1) == ApplicationParameters::k_dialogEscapeChar)
		{
			auto& fragmentLoadComp = m_rReg.emplace<LoadComp>(fragmentEntity);
			fragmentLoadComp.m_filePath = textFragment.substr(1, textFragment.length() - 2);
			m_dialogSysState = DialogSysState_t::LOADING;
			return;
		}

		auto& fragmentTextComp = m_rReg.emplace<TextComp>(fragmentEntity);
		fragmentTextComp.m_text = textFragment;

		auto& fragmentSizeComp = m_rReg.emplace<SizeComp>(fragmentEntity);
		fragmentSizeComp.m_size.width = EntityLoaderUtils::GetTextWidth(fragmentTextComp.m_text, sizeComp.m_size.height);
		fragmentSizeComp.m_size.height = sizeComp.m_size.height;

		auto& fragmentPositionComp = m_rReg.emplace<PositionComp>(fragmentEntity);
		fragmentPositionComp.m_position.x =
			Helper::Rand(
				fragmentSizeComp.m_size.width/2,
				ApplicationParameters::k_screenWidth - fragmentSizeComp.m_size.width/2);
		fragmentPositionComp.m_position.y =
			Helper::Rand(
				fragmentSizeComp.m_size.height/2,
				ApplicationParameters::k_screenHeight - fragmentSizeComp.m_size.height/2);

		auto& fragmentRenderableComp = m_rReg.emplace<RenderableComp>(fragmentEntity);
		fragmentRenderableComp.m_bRendered = false;

		m_rReg.emplace<ClickableComp>(fragmentEntity);
		m_dialogSysState = DialogSysState_t::PENDING;
	});
}

void DialogSys::UpdatePendingState_()
{
	bool bLiveFragment = true;
	bool bLiveChain = true;
	m_rReg.view<DialogChainFragmentComp, ClickableComp>().each([&](auto entity, auto& clickableComp)
	{
		if (clickableComp.m_bLeftClicked)
		{
			m_rReg.destroy(entity);
			bLiveFragment = false;

			m_rReg.view<DialogChainComp, TextComp>().each([&](auto entity, auto& textComp)
			{
				if (textComp.m_text.empty())
				{
					m_rReg.destroy(entity);
					bLiveChain = false;
				}
			});
		}
	});

	if (!bLiveChain)
	{
		m_rReg.view<DialogChainFragmentComp, ClickableComp>().each([&](auto entity, auto& clickableComp)
		{
			m_rReg.destroy(entity);
		});
	}

	m_dialogSysState = !bLiveChain ?
		DialogSysState_t::FINISHED :
			(bLiveFragment ?
				DialogSysState_t::PENDING :
				DialogSysState_t::PRODUCING);
}

void DialogSys::UpdateLoadingState_()
{
	bool bFinished = false;

	m_rReg.view<DialogChainComp, TextComp>().each([&](auto entity, auto& textComp)
	{
		if (textComp.m_text.empty())
		{
			m_rReg.destroy(entity);
			bFinished = true;
		}
	});
	m_dialogSysState = bFinished ?
		DialogSysState_t::FINISHED :
		DialogSysState_t::PRODUCING;
}

void DialogSys::UpdateFinishedState_()
{
	std::cout << "Finished" << std::endl;
	m_dialogSysState = DialogSysState_t::WAITING;
}