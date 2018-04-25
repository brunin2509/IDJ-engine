#include "Rect.h"
#include "Vec2.h"

#include <algorithm>
#include <cmath>

class Collision {

	public:
		// Observação: IsColliding espera ângulos em graus!
		// Logo no inicio da funcao, esses valores sao convertidos em radianos!
		static inline bool IsColliding(Rect& a, Rect& b, float angleOfA, float angleOfB) {
			angleOfA *= PI/180;
			angleOfB *= PI/180;

			Vec2 A[] = { Vec2( a.x, a.y + a.h ),
						  Vec2( a.x + a.w, a.y + a.h ),
						  Vec2( a.x + a.w, a.y ),
						  Vec2( a.x, a.y )
						};
			Vec2 B[] = { Vec2( b.x, b.y + b.h ),
						  Vec2( b.x + b.w, b.y + b.h ),
						  Vec2( b.x + b.w, b.y ),
						  Vec2( b.x, b.y )
						};

			for (auto& v : A) {
				v = Vec2::Rotate(v - a.Center(), angleOfA) + a.Center();
			}

			for (auto& v : B) {
				v = Vec2::Rotate(v - b.Center(), angleOfB) + b.Center();
			}

			Vec2 axes[] = { Vec2::Norm(A[0] - A[1]), Vec2::Norm(A[1] - A[2]), Vec2::Norm(B[0] - B[1]), Vec2::Norm(B[1] - B[2]) };

			for (auto& axis : axes) {
				float P[4];

				for (int i = 0; i < 4; ++i) P[i] = Vec2::Dot(A[i], axis);

				float minA = *std::min_element(P, P + 4);
				float maxA = *std::max_element(P, P + 4);

				for (int i = 0; i < 4; ++i) P[i] = Vec2::Dot(B[i], axis);

				float minB = *std::min_element(P, P + 4);
				float maxB = *std::max_element(P, P + 4);

				if (maxA < minB || minA > maxB)
					return false;
			}

			return true;
		}
};

// Aqui estão três operadores que sua classe Vec2 deve precisar, se já não tiver. 
// Se sua classe tiver métodos para Mag, Norm, Dot e/ou Rotate, você pode substituir
// os usos desses métodos por usos dos seus, mas garanta que deem resultados corretos.

// Vec2 operator+(const Vec2& rhs) const {
//    return Vec2(x + rhs.x, y + rhs.y);
// }

// Vec2 operator-(const Vec2& rhs) const {
//    return Vec2(x - rhs.x, y - rhs.y);
// }

// Vec2 operator*(const float rhs) const {
//    return Vec2(x * rhs, y * rhs);
// }
