#pragma once

#include <godot_cpp/classes/ref_counted.hpp>
#include <godot_cpp/classes/wrapped.hpp>
#include <godot_cpp/variant/variant.hpp>
#include <godot_cpp/classes/sprite2d.hpp>
#include <godot_cpp/core/binder_common.hpp>
#include <godot_cpp/core/gdvirtual.gen.inc>

using namespace godot;

class ExampleClass : public RefCounted
{
	GDCLASS(ExampleClass, RefCounted)

protected:
	static void _bind_methods();

public:
	ExampleClass() = default;
	~ExampleClass() override = default;

	void print_type(const Variant &p_variant) const;
};

class GDNewEx : public Sprite2D
{
	GDCLASS(GDNewEx, Sprite2D)
public:
	GDNewEx();
	~GDNewEx();

	/// if the macro ends with the "RC" suffix, the virtual method will returns a value,
	/// which is the first argument of the macro, followed by the virtual name method
	/// and the arguments expected by the macro name itself
//	GDVIRTUAL1RC(float, _my_virtual_method_name, Array);
	/// if the macro does not end with that suffix, then the first
//	GDVIRTUAL2(_another_virtual_method_name, Array, double);
	//GDVIRTUAL1(_process, double);

	virtual void _process(double delta) override;

	void set_speed(const float in_speed);
	float get_speed() const;

	GDVIRTUAL0(printy);
	virtual void printy();

	GDVIRTUAL1(printyparam, String);
	virtual void printyparam(String stringy);

protected:
	static void _bind_methods();

private:
	double time_passed = 0.0f;
	Vector2 m_velocity = Vector2(0,0);
	float m_speed = 0.0f;
};
