#pragma once

#include <functional>

#include "IEvent.hpp"

namespace Flounder
{
	/// <summary>
	/// A class that acts as a basic change listener for a value.
	/// </summary>
	/// @param <T> The type of value to find change with. </param>
	template<typename t>
	class EventChange :
		public IEvent
	{
	private:
		t *m_reference;
		t m_current;
		std::function<void()> m_onEvent;
	public:
		/// <summary>
		/// Creates a new change event.
		/// </summary>
		/// <param name="reference"> The reference to listen to. </param>
		/// <param name="onEvent"> A function called when the event is triggered. </param>
		EventChange(t *reference, const std::function<void()> &onEvent);

		bool EventTriggered() override;

		void OnEvent() override;

		bool RemoveAfterEvent() override { return false; }
	};
}