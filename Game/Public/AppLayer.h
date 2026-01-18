#pragma once

#include "Layer.h"

class AppLayer : public Core::Layer
{
public:
	AppLayer();
	virtual ~AppLayer();

	virtual void OnUpdate(float dt) override;
	virtual void OnRender() override;
};
