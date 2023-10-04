#include "ToolBox.h"

ToolBox::ToolBox()
	:IconButton{ Button(ToolsButtonInitializer,Vector2f(10.f,605.f)) }
{
}

bool ToolBox::EventCheck(Vector2i MousePos, std::vector<Fourier> fouriers)
{
	if (!fouriers.size()) {
		IconButton.setColor(Color(255, 255, 255, 100));
		return false;
	}
	else
		IconButton.setColor(Color(255, 255, 255, 255));

	if (IconButton.EventCheck(MousePos) > 0)
		return true;
	return false;
}

void ToolBox::Render(Renderer& renderer)
{
	IconButton.Render(renderer);
}
