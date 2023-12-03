#ifndef COLOR_H
#define COLOR_H
#include "Vector.hpp"
#include <math.h>

namespace Engine {
	struct Color {
		int r, g, b, a;
		public:
		Color(): r(0), g(0), b(0), a(0) {}
		private:
		Color(int r, int g, int b, int a): r(r), g(g), b(b), a(a) {}

		public:
		static Color FromRGB(int r, int g, int b) { return Color(r,g,b,255); } 
		static Color FromHSV(int h, int s, int v) {
			h %= 360; 							// ensure h is in the range 0..360
			float satP = s / 100.f; // [0..100] -> [0..1]
			float valP = v / 100.f; // [0..100] -> [0..1]
			float c = valP * satP;
			float x = c * (1 - abs((h / 60) % 2 - 1));
			float m = v - c;
			Vector3 cP;
			if (h >= 0   && h < 60 ) cP = Vector3(c, x, 0);
			if (h >= 60  && h < 120) cP = Vector3(x, c, 0);
			if (h >= 120 && h < 180) cP = Vector3(0, c, x);
			if (h >= 180 && h < 240) cP = Vector3(0, x, c);
			if (h >= 240 && h < 300) cP = Vector3(x, 0, c);
			if (h >= 300 && h < 360) cP = Vector3(c, 0, x);
			return FromRGB((cP.x+m)*255, (cP.y+m)*255, (cP.z+m)*255);
		}

		static Color Black() { return FromRGB(0,   0,   0  ); }
		static Color White() { return FromRGB(255, 255, 255); }
		static Color Blue()  { return FromRGB(0,   0,   255); }
		static Color Green() { return FromRGB(0,   255, 0  ); }
		static Color Red()   { return FromRGB(255, 0,   0  ); }
	};
}

#endif
