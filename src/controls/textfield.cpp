#include "pch.h"
#include "qui.h"
using namespace qui;

textfield::textfield(std::string name, container* parent, std::string title, bool hide, control* prev_displayed)
	: control(name, parent, title, prev_displayed)
{
	m_hide = hide;
	m_value = "";
	m_cursor = m_value.end();
}

void textfield::draw()
{
	if (!title().empty())
		draw_title();

	draw_indent();

	std::string output;

	if (m_hide)
		output = std::string(m_value.length(), '*');
	else
		output = m_value;

	// draw cursor if control is selected
	if (is_selected())
	{
		unsigned int cursor_pos = m_cursor - m_value.begin();
		char cursor = cursor_pos < m_value.length() ? '|' : '_';
		output.insert(output.begin() + cursor_pos, cursor);
	}
	std::cout << "> " << output;
}

void textfield::handle_input(int key, int nav)
{
	if (nav)
	{
		if (nav == ARROW_LEFT && m_cursor > m_value.begin())
			m_cursor--;
		else if (nav == ARROW_RIGHT && m_cursor < m_value.end())
			m_cursor++;
		return;
	}

	switch (key)
	{
	case VK_BACK:
		if (m_cursor > m_value.begin())
			m_cursor = m_value.erase(std::prev(m_cursor));
		break;
	case VK_F16:
		if (m_cursor > m_value.begin())
			m_cursor = m_value.erase(find_space(), m_cursor);
		break;
	case VK_RETURN:
		if (on_enter)
			on_enter(this);
		return;
	default:
		m_cursor = m_value.insert(m_cursor, key);
		m_cursor++;
		break;
	}
	if (on_update)
		on_update(this);
}

void textfield::reset()
{
	set_value("");
}

std::string::iterator textfield::find_space()
{
	std::string::iterator it = std::prev(m_cursor);

	if (!m_hide)
	{
		while (--it > m_value.begin())
		{
			if (*it == ' ')
				return std::next(it);
		}
	}
	return m_value.begin();
}

std::string textfield::value()
{
	return m_value;
}

void textfield::set_value(std::string value)
{
	m_value = value;
	m_cursor = m_value.end();
}

bool textfield::hidden()
{
	return m_hide;
}

void textfield::set_hidden(bool hide_chars)
{
	m_hide = hide_chars;
}