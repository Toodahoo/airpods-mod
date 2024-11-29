#include "simulation/ElementCommon.h"

int Element_AIRP_update(UPDATE_FUNC_ARGS);

void Element::Element_AIRP()
{
	Identifier = "PT_AIRP";
	Name = "AIRP";
	Colour = 0xF4F4F4_rgb;
	MenuVisible = 1;
	MenuSection = SC_SPECIAL;
	Enabled = 1;

	Advection = 0.4f;
	AirDrag = 0.04f * CFDS;
	AirLoss = 0.94f;
	Loss = 0.95f;
	Collision = -0.1f;
	Gravity = 0.18f;
	Diffusion = 0.00f;
	HotAir = 0.000f	* CFDS;
	Falldown = 1;

	Flammable = 0;
	Explosive = 0;
	Meltable = 0;
	Hardness = 30;

	Weight = 85;

	HeatConduct = 70;
	Description = "Airpods. Made in China. Most expensive particle in TPT. Enables STKM to vibe.";

	Properties = TYPE_PART;

	LowPressure = IPL;
	LowPressureTransition = NT;
	HighPressure = IPH;
	HighPressureTransition = NT;
	LowTemperature = ITL;
	LowTemperatureTransition = NT;
	HighTemperature = 3000.0f;
	HighTemperatureTransition = PT_BREC;

	Update = &Element_AIRP_update;
}

int Element_AIRP_update(UPDATE_FUNC_ARGS)
{
	for (auto rx = -1; rx <= 1; rx++)
	{
		for (auto ry = -1; ry <= 1; ry++)
		{
			if (rx || ry)
			{
				auto r = pmap[y+ry][x+rx];
				if (!r)
					continue;
				switch (TYP(r))
				{
					case PT_VIBR:
					case PT_BVBR:
					{
						if (parts[ID(r)].life != 0)
						{
							if (sim->rng.chance(1,10))
								sim->part_change_type(i,x,y,PT_BVBR);
						}
					}
					case PT_FIGH:
					{	// FIGH may steal dropped AIRP
						if (sim->rng.chance(1,5))
						{
							sim->kill_part(i);
							return 0;
						}
						break;
					}
					default:
						break;
				}
			}
		}
	}
	return 0;
}
