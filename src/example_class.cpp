#include "example_class.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/godot.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/classes/os.hpp>

//OS::get_singleton()->delay_msec(250);
void ExampleClass::_bind_methods()
{
	godot::ClassDB::bind_method(D_METHOD("print_type", "variant"), &ExampleClass::print_type);
}

void ExampleClass::print_type(const Variant &p_variant) const
{
	print_line(vformat("Type: %d", p_variant.get_type()));
}

void GDNewEx::_bind_methods()
{
	//GDVIRTUAL_BIND(_my_virtual_method_name, "argument_0_name")
	//GDVIRTUAL_BIND(_another_virtual_method_name, "argument_0_name", "argument_1_name")
	//GDVIRTUAL_BIND(_process, "delta");
	GDVIRTUAL_BIND(printy);
	GDVIRTUAL_BIND(printyparam, "stringy")
	ClassDB::bind_method(D_METHOD("get_speed"), &GDNewEx::get_speed);
	ClassDB::bind_method(D_METHOD("set_speed", "speed"), &GDNewEx::set_speed);
	ClassDB::add_property("GDNewEx", PropertyInfo(Variant::FLOAT, "speed"), "set_speed", "get_speed");
}

GDNewEx::GDNewEx()
{
	// Initialize any variables here.
	time_passed = 0.0;

	// Disable the process updates while in regular edito mode
	if (Engine::get_singleton()->is_editor_hint())
	{
		set_process_mode(Node::PROCESS_MODE_DISABLED);
	}
}

GDNewEx::~GDNewEx()
{
	// Add your cleanup here.
}

void GDNewEx::_process(double delta)
{
	Sprite2D::_process(delta);
	if (m_velocity.x >= 1)
	{
		printy();
		printyparam("basey");
	}

	time_passed += delta;
	Vector2 new_position = Vector2(10.0 + (10.0 * sin(time_passed * 2.0)), 10.0 + (10.0 * cos(time_passed * 1.5)));

	Input& inputSingleton = *Input::get_singleton();
	if (inputSingleton.is_action_pressed("d")) {
		m_velocity.x += 1;
	}
	if (inputSingleton.is_action_pressed("a"))
	{
		m_velocity.x -= 1;
	}
	set_position(new_position + m_velocity * m_speed * delta);
}

void GDNewEx::set_speed(const float in_speed)
{
	m_speed = in_speed;
}

float GDNewEx::get_speed() const
{
	return m_speed;
}

void GDNewEx::printy()
{
	if (!GDVIRTUAL_IS_OVERRIDDEN(printy)) {
		UtilityFunctions::print("a_printy");
	} else {
		GDVIRTUAL_CALL(printy);
	}
	UtilityFunctions::print("printy");
}


void GDNewEx::printyparam(String stringy)
{
	if (!GDVIRTUAL_IS_OVERRIDDEN(printyparam)) {
		UtilityFunctions::print("b_printy");
	} else {
		GDVIRTUAL_CALL(printyparam, stringy);
	}
	UtilityFunctions::print(stringy);
}
