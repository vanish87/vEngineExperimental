
#include <RENDERING_API.h>


class RENDERING_API RenderEngine
{
	public:
	virtual void Render() = 0;

	private:
	void CreateInternal();
};