#pragma once

class Actor;
class View;
struct UpdateEvent;
struct DrawEvent;

class Component
{
public:
	virtual void Init()											= 0;
	virtual void OnUpdate(const UpdateEvent* UE)				= 0;
	virtual void OnDraw(const DrawEvent* DE)					= 0;
	virtual void CleanUp()										= 0;
private:

};

