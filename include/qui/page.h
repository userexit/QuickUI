#pragma once
#include "container_control.h"

namespace qui
{
	/// <summary>
	/// Control to show arbitrary controls to be displayed at once in the menu
	/// </summary>
	class page : public container_control
	{
	private:
		void draw_title() override;

	public:
		/// <param name="name">Internal name used to identify the control</param>
		/// <param name="parent">Parent container. Control is automatically added to it</param>
		/// <param name="title">Text shown above control</param>
		/// <param name="prev_displayed">Only set when control is top-level. Pointer to control to be shown when Escape is pressed</param>
		page(std::string name, std::string title);

		// control overrides

		void draw() override;
		void handle_input(int key, int nav) override;
		void reset() override;

		std::function<void(page*)> on_enter;
	};
}
