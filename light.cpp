#include "light.h"

Light::Light(Vector ipos, Color rgb, bool type) {
	pos = ipos;
	color = rgb;
	isdir = type;
}
