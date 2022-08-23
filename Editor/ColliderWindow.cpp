#include "stdafx.h"
#include "ColliderWindow.h"
#include "Editor.h"

using namespace wi::ecs;
using namespace wi::scene;

void ColliderWindow::Create(EditorComponent* _editor)
{
	editor = _editor;

	wi::gui::Window::Create(ICON_COLLIDER " Collider", wi::gui::Window::WindowControls::COLLAPSE | wi::gui::Window::WindowControls::CLOSE);
	SetSize(XMFLOAT2(670, 260));

	closeButton.SetTooltip("Delete ColliderComponent");
	OnClose([=](wi::gui::EventArgs args) {

		wi::Archive& archive = editor->AdvanceHistory();
		archive << EditorComponent::HISTORYOP_COMPONENT_DATA;
		editor->RecordEntity(archive, entity);

		editor->GetCurrentScene().colliders.Remove(entity);

		editor->RecordEntity(archive, entity);

		editor->optionsWnd.RefreshEntityTree();
		});

	float x = 60;
	float y = 4;
	float hei = 20;
	float step = hei + 2;
	float wid = 220;

	shapeCombo.Create("Shape: ");
	shapeCombo.SetSize(XMFLOAT2(wid, hei));
	shapeCombo.SetPos(XMFLOAT2(x, y));
	shapeCombo.AddItem("Sphere", (uint64_t)ColliderComponent::Shape::Sphere);
	shapeCombo.AddItem("Capsule", (uint64_t)ColliderComponent::Shape::Capsule);
	shapeCombo.OnSelect([=](wi::gui::EventArgs args) {
		wi::scene::Scene& scene = editor->GetCurrentScene();
		ColliderComponent* collider = scene.colliders.GetComponent(entity);
		if (collider == nullptr)
			return;

		collider->shape = (ColliderComponent::Shape)args.userdata;
	});
	AddWidget(&shapeCombo);

	radiusSlider.Create(0, 10, 0, 100000, "Radius: ");
	radiusSlider.SetSize(XMFLOAT2(wid, hei));
	radiusSlider.SetPos(XMFLOAT2(x, y += step));
	radiusSlider.OnSlide([&](wi::gui::EventArgs args) {
		wi::scene::Scene& scene = editor->GetCurrentScene();
		ColliderComponent* collider = scene.colliders.GetComponent(entity);
		if (collider == nullptr)
			return;

		collider->radius = args.fValue;
		});
	AddWidget(&radiusSlider);


	y += step;


	offsetX.Create(-10, 10, 0, 10000, "Offset X: ");
	offsetX.SetSize(XMFLOAT2(wid, hei));
	offsetX.SetPos(XMFLOAT2(x, y += step));
	offsetX.OnSlide([=](wi::gui::EventArgs args) {
		wi::scene::Scene& scene = editor->GetCurrentScene();
		ColliderComponent* collider = scene.colliders.GetComponent(entity);
		if (collider == nullptr)
			return;

		collider->offset.x = args.fValue;
		});
	AddWidget(&offsetX);

	offsetY.Create(-10, 10, 0, 10000, "Offset Y: ");
	offsetY.SetSize(XMFLOAT2(wid, hei));
	offsetY.SetPos(XMFLOAT2(x, y += step));
	offsetY.OnSlide([=](wi::gui::EventArgs args) {
		wi::scene::Scene& scene = editor->GetCurrentScene();
		ColliderComponent* collider = scene.colliders.GetComponent(entity);
		if (collider == nullptr)
			return;

		collider->offset.y = args.fValue;
		});
	AddWidget(&offsetY);

	offsetZ.Create(-10, 10, 0, 10000, "Offset Z: ");
	offsetZ.SetSize(XMFLOAT2(wid, hei));
	offsetZ.SetPos(XMFLOAT2(x, y += step));
	offsetZ.OnSlide([=](wi::gui::EventArgs args) {
		wi::scene::Scene& scene = editor->GetCurrentScene();
		ColliderComponent* collider = scene.colliders.GetComponent(entity);
		if (collider == nullptr)
			return;

		collider->offset.z = args.fValue;
		});
	AddWidget(&offsetZ);


	y += step;


	tailX.Create(-10, 10, 0, 10000, "Tail X: ");
	tailX.SetSize(XMFLOAT2(wid, hei));
	tailX.SetPos(XMFLOAT2(x, y += step));
	tailX.OnSlide([=](wi::gui::EventArgs args) {
		wi::scene::Scene& scene = editor->GetCurrentScene();
		ColliderComponent* collider = scene.colliders.GetComponent(entity);
		if (collider == nullptr)
			return;

		collider->tail.x = args.fValue;
		});
	AddWidget(&tailX);

	tailY.Create(-10, 10, 0, 10000, "Tail Y: ");
	tailY.SetSize(XMFLOAT2(wid, hei));
	tailY.SetPos(XMFLOAT2(x, y += step));
	tailY.OnSlide([=](wi::gui::EventArgs args) {
		wi::scene::Scene& scene = editor->GetCurrentScene();
		ColliderComponent* collider = scene.colliders.GetComponent(entity);
		if (collider == nullptr)
			return;

		collider->tail.y = args.fValue;
		});
	AddWidget(&tailY);

	tailZ.Create(-10, 10, 0, 10000, "Tail Z: ");
	tailZ.SetSize(XMFLOAT2(wid, hei));
	tailZ.SetPos(XMFLOAT2(x, y += step));
	tailZ.OnSlide([=](wi::gui::EventArgs args) {
		wi::scene::Scene& scene = editor->GetCurrentScene();
		ColliderComponent* collider = scene.colliders.GetComponent(entity);
		if (collider == nullptr)
			return;

		collider->tail.z = args.fValue;
		});
	AddWidget(&tailZ);


	SetMinimized(true);
	SetVisible(false);

	SetEntity(INVALID_ENTITY);
}


void ColliderWindow::SetEntity(Entity entity)
{
	if (this->entity == entity)
		return;

	this->entity = entity;

	Scene& scene = editor->GetCurrentScene();

	const ColliderComponent* collider = scene.colliders.GetComponent(entity);

	if (collider != nullptr)
	{
		shapeCombo.SetSelectedByUserdataWithoutCallback((uint64_t)collider->shape);
		radiusSlider.SetValue(collider->radius);
		offsetX.SetValue(collider->offset.x);
		offsetY.SetValue(collider->offset.y);
		offsetZ.SetValue(collider->offset.z);
		tailX.SetValue(collider->tail.x);
		tailY.SetValue(collider->tail.y);
		tailZ.SetValue(collider->tail.z);
	}
}
