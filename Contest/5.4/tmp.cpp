#include <cstdio>
#include <cctype>
#include <algorithm>
#include <tuple>
#include <cstring>

typedef unsigned int uint;
typedef long long unsigned int uint64;

constexpr uint Max_size = 1 << 24 | 5;
constexpr uint g = 3, Mod = 998244353;

inline uint norm_2(const uint x)
{
	return x < Mod * 2 ? x : x - Mod * 2;
}

inline uint norm(const uint x)
{
	return x < Mod ? x : x - Mod;
}

struct Z
{
	uint v;
	Z() { }
	Z(const uint _v) : v(_v) { }
};

inline Z operator+(const Z x1, const Z x2) { return norm(x1.v + x2.v); }
inline Z operator-(const Z x1, const Z x2) { return norm(x1.v + Mod - x2.v); }
inline Z operator-(const Z x) { return x.v ? Mod - x.v : 0; }
inline Z operator*(const Z x1, const Z x2) { return static_cast<uint64>(x1.v) * x2.v % Mod; }
inline Z &operator+=(Z &x1, const Z x2) { return x1 = x1 + x2; }
inline Z &operator-=(Z &x1, const Z x2) { return x1 = x1 - x2; }
inline Z &operator*=(Z &x1, const Z x2) { return x1 = x1 * x2; }

inline Z Power(Z Base, int Exp)
{
	Z res = 1;
	for (; Exp; Base *= Base, Exp >>= 1)
		if (Exp & 1)
			res *= Base;
	return res;
}

inline Z Rec(const Z x)
{
	return Power(x, Mod - 2);
}

Z _Rec[Max_size];

void init_Rec(const int n)
{
	_Rec[1] = 1;
	for (int i = 2; i != n; ++i)
		_Rec[i] = _Rec[i - 1] * (i - 1);
	Z R = Rec(_Rec[n - 1] * (n - 1));
	for (int i = n - 1; i != 1; --i)
		_Rec[i] *= R, R *= i;
}

int size;
uint w[Max_size], w_q[Max_size];

inline uint mult_Shoup_2(const uint x, const uint y, const uint y_q)
{
	uint q = static_cast<uint64>(x) * y_q >> 32;
	return x * y - q * Mod;
}

inline uint mult_Shoup(const uint x, const uint y, const uint y_q)
{
	return norm(mult_Shoup_2(x, y, y_q));
}

inline uint mult_Shoup_q(const uint x, const uint y, const uint y_q)
{
	uint q = static_cast<uint64>(x) * y_q >> 32;
	return q + (x * y - q * Mod >= Mod);
}

void init_w(const int n)
{
	for (size = 2; size < n; size <<= 1)
		;
	uint pr = Power(g, (Mod - 1) / size).v;
	uint pr_q = (static_cast<uint64>(pr) << 32) / Mod;
	uint pr_r = (static_cast<uint64>(pr) << 32) % Mod;
	size >>= 1;
	w[size] = 1, w_q[size] = (static_cast<uint64>(w[size]) << 32) / Mod;
	for (int i = 1; i < size; ++i)
	{
		//w[size + i] = mult_Shoup(w[size + i - 1], pr, pr_q);
		uint x = w[size + i - 1];
		uint64 p = static_cast<uint64>(x) * pr_q;
		uint q = p >> 32;
		w[size + i] = norm(x * pr - q * Mod);
		w_q[size + i] = static_cast<uint>(p) + mult_Shoup_q(pr_r, w[size + i - 1], w_q[size + i - 1]);
	}
	for (int i = size - 1; i; --i)
		w[i] = w[i * 2], w_q[i] = w_q[i * 2];
	size <<= 1;
}

//void DFT_fr_2(Z _A[], const int L)
//{
//	uint *A = reinterpret_cast<uint *>(_A);
//	for (int d = L >> 1; d; d >>= 1)
//		for (int i = 0; i != L; i += d << 1)
//			for (int j = 0; j != d; ++j)
//			{
//				uint x = norm_2(A[i + j] + A[i + d + j]);
//				uint y = mult_Shoup_2(A[i + j] + Mod * 2 - A[i + d + j], w[d + j], w_q[d + j]);
//				A[i + j] = x, A[i + d + j] = y;
//			}
//}
void DFT_fr_2(Z _A[], const int L)
{
	if (L == 1)
		return;
	uint *A = reinterpret_cast<uint *>(_A);
//	auto butterfly1 = [](uint &a, uint &b)
//	{
//		uint x = norm_2(a + b), y = norm_2(a + Mod * 2 - b);
//		a = x, b = y;
//	};
#define butterfly1(a, b)\
	do\
	{\
		uint _a = a, _b = b;\
		uint x = norm_2(_a + _b), y = norm_2(_a + Mod * 2 - _b);\
		a = x, b = y;\
	} while (0)
	if (L == 2)
	{
		butterfly1(A[0], A[1]);
		return;
	}
//	auto butterfly = [](uint &a, uint &b, const uint _w, const uint _w_q)
//	{
//		uint x = norm_2(a + b), y = mult_Shoup_2(a + Mod * 2 - b, _w, _w_q);
//		a = x, b = y;
//	};
#define butterfly(a, b, _w, _w_q)\
	do\
	{\
		uint _a = a, _b = b;\
		uint x = norm_2(_a + _b), y = mult_Shoup_2(_a + Mod * 2 - _b, _w, _w_q);\
		a = x, b = y;\
	} while (0)
	if (L == 4)
	{
		butterfly1(A[0], A[2]);
		butterfly(A[1], A[3], w[3], w_q[3]);
		butterfly1(A[0], A[1]);
		butterfly1(A[2], A[3]);
		return; 
	}
	for (int d = L >> 1; d != 4; d >>= 1)
		for (int i = 0; i != L; i += d << 1)
			for (int j = 0; j != d; j += 4)
			{
				butterfly(A[i + j + 0], A[i + d + j + 0], w[d + j + 0], w_q[d + j + 0]);
				butterfly(A[i + j + 1], A[i + d + j + 1], w[d + j + 1], w_q[d + j + 1]);
				butterfly(A[i + j + 2], A[i + d + j + 2], w[d + j + 2], w_q[d + j + 2]);
				butterfly(A[i + j + 3], A[i + d + j + 3], w[d + j + 3], w_q[d + j + 3]);
			}
	for (int i = 0; i != L; i += 8)
	{
		butterfly1(A[i + 0], A[i + 4]);
		butterfly(A[i + 1], A[i + 5], w[5], w_q[5]);
		butterfly(A[i + 2], A[i + 6], w[6], w_q[6]);
		butterfly(A[i + 3], A[i + 7], w[7], w_q[7]);
	}
	for (int i = 0; i != L; i += 8)
	{
		butterfly1(A[i + 0], A[i + 2]);
		butterfly(A[i + 1], A[i + 3], w[3], w_q[3]);
		butterfly1(A[i + 4], A[i + 6]);
		butterfly(A[i + 5], A[i + 7], w[3], w_q[3]);
	}
	for (int i = 0; i != L; i += 8)
	{
		butterfly1(A[i + 0], A[i + 1]);
		butterfly1(A[i + 2], A[i + 3]);
		butterfly1(A[i + 4], A[i + 5]);
		butterfly1(A[i + 6], A[i + 7]);
	}
#undef butterfly1
#undef butterfly
}

//void IDFT_fr(Z _A[], const int L)
//{
//	uint *A = reinterpret_cast<uint *>(_A);
//	for (int d = 1; d != L; d <<= 1)
//		for (int i = 0; i != L; i += d << 1)
//			for (int j = 0; j != d; ++j)
//			{
//				uint x = norm_2(A[i + j]);
//				uint t = mult_Shoup_2(A[i + d + j], w[d + j], w_q[d + j]);
//				A[i + j] = x + t, A[i + d + j] = x + Mod * 2 - t;
//			}
//	std::reverse(A + 1, A + L);
//	if (L == 2)
//		A[0] = norm_2(A[0]), A[1] = norm_2(A[1]);
//	int k = __builtin_ctz(L);
//	for (int i = 0; i != L; ++i)
//	{
//		uint64 m = -A[i] & (L - 1);
//		A[i] = norm((A[i] + m * Mod) >> k);
//	}
//}
void IDFT_fr(Z _A[], const int L)
{
	if (L == 1)
		return;
	uint *A = reinterpret_cast<uint *>(_A);
//	auto butterfly1 = [](uint &a, uint &b)
//	{
//		uint x = norm_2(a), t = norm_2(b);
//		a = x + t, b = x + Mod * 2 - t;
//	};
#define butterfly1(a, b)\
	do\
	{\
		uint _a = a, _b = b;\
		uint x = norm_2(_a), t = norm_2(_b);\
		a = x + t, b = x + Mod * 2 - t;\
	} while (0)
	if (L == 2)
	{
		butterfly1(A[0], A[1]);
		A[0] = norm(norm_2(A[0])), A[0] = A[0] & 1 ? A[0] + Mod : A[0], A[0] /= 2;
		A[1] = norm(norm_2(A[1])), A[1] = A[1] & 1 ? A[1] + Mod : A[1], A[1] /= 2;
		return;
	}
//	auto butterfly = [](uint &a, uint &b, const uint _w, const uint _w_q)
//	{
//		uint x = norm_2(a), t = mult_Shoup_2(b, _w, _w_q);
//		a = x + t, b = x + Mod * 2 - t;
//	};
#define butterfly(a, b, _w, _w_q)\
	do\
	{\
		uint _a = a, _b = b;\
		uint x = norm_2(_a), t = mult_Shoup_2(_b, _w, _w_q);\
		a = x + t, b = x + Mod * 2 - t;\
	} while (0)
	if (L == 4)
	{
		butterfly1(A[0], A[1]);
		butterfly1(A[2], A[3]);
		butterfly1(A[0], A[2]);
		butterfly(A[1], A[3], w[3], w_q[3]);
		std::swap(A[1], A[3]);
		for (int i = 0; i != L; ++i)
		{
			uint64 m = -A[i] & 3;
			A[i] = norm((A[i] + m * Mod) >> 2);
		}
		return; 
	}
	for (int i = 0; i != L; i += 8)
	{
		butterfly1(A[i + 0], A[i + 1]);
		butterfly1(A[i + 2], A[i + 3]);
		butterfly1(A[i + 4], A[i + 5]);
		butterfly1(A[i + 6], A[i + 7]);
	}
	for (int i = 0; i != L; i += 8)
	{
		butterfly1(A[i + 0], A[i + 2]);
		butterfly(A[i + 1], A[i + 3], w[3], w_q[3]);
		butterfly1(A[i + 4], A[i + 6]);
		butterfly(A[i + 5], A[i + 7], w[3], w_q[3]);
	}
	for (int i = 0; i != L; i += 8)
	{
		butterfly1(A[i + 0], A[i + 4]);
		butterfly(A[i + 1], A[i + 5], w[5], w_q[5]);
		butterfly(A[i + 2], A[i + 6], w[6], w_q[6]);
		butterfly(A[i + 3], A[i + 7], w[7], w_q[7]);
	}
	for (int d = 8; d != L; d <<= 1)
		for (int i = 0; i != L; i += d << 1)
			for (int j = 0; j != d; j += 4)
			{
				butterfly(A[i + j + 0], A[i + d + j + 0], w[d + j + 0], w_q[d + j + 0]);
				butterfly(A[i + j + 1], A[i + d + j + 1], w[d + j + 1], w_q[d + j + 1]);
				butterfly(A[i + j + 2], A[i + d + j + 2], w[d + j + 2], w_q[d + j + 2]);
				butterfly(A[i + j + 3], A[i + d + j + 3], w[d + j + 3], w_q[d + j + 3]);
			}
#undef butterfly1
#undef butterfly
	std::reverse(A + 1, A + L);
	int k = __builtin_ctz(L);
	for (int i = 0; i != L; ++i)
	{
		uint64 m = -A[i] & (L - 1);
		A[i] = norm((A[i] + m * Mod) >> k);
	}
}

inline void reset(Z A[], const int n)
{
	std::memset(reinterpret_cast<uint *>(A), 0, n * sizeof(Z));
}

const uint _M_size = Max_size * 5;
Z _M[_M_size], *_M_pos = _M + _M_size;

void Rec(const Z A[], Z res[], const int L)
{
	Z *B = _M_pos -= L;
	Z *dfta = _M_pos -= L + (L >> 1);
	Z *dftb = _M_pos -= L + (L >> 1);
	
	B[0] = Rec(A[0]);
	for (int d = 1; d != L; d *= 2)
	{
		std::copy_n(A, d * 2, dfta);
		DFT_fr_2(dfta, d * 2);
		for (int i = 0; i != d; ++i)
			dfta[d * 2 + i] = norm_2(mult_Shoup_2(A[i].v, w[d * 2 + i], w_q[d * 2 + i]) + mult_Shoup_2(A[d + i].v, w[d * 2 + d + i], w_q[d * 2 + d + i]));
		DFT_fr_2(dfta + d * 2, d);
		
		std::copy_n(B, d, dftb), reset(dftb + d, d);
		DFT_fr_2(dftb, d * 2);
		for (int i = 0; i != d; ++i)
			dftb[d * 2 + i] = mult_Shoup_2(B[i].v, w[d * 2 + i], w_q[d * 2 + i]);
		DFT_fr_2(dftb + d * 2, d);
		
		for (int i = 0; i != d * 3; ++i)
			dftb[i] *= dfta[i] * dftb[i];
		IDFT_fr(dftb, d * 2), IDFT_fr(dftb + d * 2, d);
		
		for (int i = 1; i != d; ++i)
			dftb[d * 2 + i] = mult_Shoup(Mod - dftb[d * 2 + i].v, w[d * 2 + d * 2 - i], w_q[d * 2 + d * 2 - i]);
		for (int i = 0; i != d; ++i)
		{
			Z x = mult_Shoup(dftb[i].v + dftb[d * 2 + i].v + (Mod - B[i].v) * 2, w[3], w_q[3]) - dftb[d + i];
			B[d + i] = (x.v & 1 ? x.v + Mod : x.v) / 2;
		}
	}
	std::copy_n(B, L, res);
	
	_M_pos += L * 4;
}

void Quo(const Z A[], const Z C[], Z res[], const int L)
{
	if (L == 1)
	{
		res[0] = C[0] * Rec(A[0]);
		return;
	}
	if (L == 2)
	{
		Z r0 = C[0] * Rec(A[0]), r1 = (C[1] - A[1] * r0) * Rec(A[0]);
		res[0] = r0, res[1] = r1;
		return;
	}
	Z *B = _M_pos -= L >> 1;
	Z *dfta = _M_pos -= L;
	Z *dftb = _M_pos -= L;
	Z *dftc = _M_pos -= L;
	B[0] = Rec(A[0]);
	for (int d = 1; d != L >> 1; d *= 2)
	{
		std::copy_n(A, d * 2, dfta);
		DFT_fr_2(dfta, d * 2);
		for (int i = 0; i != d; ++i)
			dfta[d * 2 + i] = norm_2(mult_Shoup_2(A[i].v, w[d * 2 + i], w_q[d * 2 + i]) + mult_Shoup_2(A[d + i].v, w[d * 2 + d + i], w_q[d * 2 + d + i]));
		DFT_fr_2(dfta + d * 2, d);
		
		std::copy_n(B, d, dftb), reset(dftb + d, d);
		DFT_fr_2(dftb, d * 2);
		for (int i = 0; i != d; ++i)
			dftb[d * 2 + i] = mult_Shoup_2(B[i].v, w[d * 2 + i], w_q[d * 2 + i]);
		DFT_fr_2(dftb + d * 2, d);
		
		for (int i = 0; i != d * 3; ++i)
			dfta[i] *= dftb[i] * dftb[i];
		IDFT_fr(dfta, d * 2), IDFT_fr(dfta + d * 2, d);
		
		for (int i = 1; i != d; ++i)
			dfta[d * 2 + i] = mult_Shoup(Mod - dfta[d * 2 + i].v, w[d * 2 + d * 2 - i], w_q[d * 2 + d * 2 - i]);
		for (int i = 0; i != d; ++i)
		{
			Z x = mult_Shoup(dfta[i].v + dfta[d * 2 + i].v + (Mod - B[i].v) * 2, w[3], w_q[3]) - dfta[d + i];
			B[d + i] = (x.v & 1 ? x.v + Mod : x.v) / 2;
		}
	}
	int d = L >> 1;
	
	std::copy_n(B + (d >> 1), d >> 1, dftb + d), reset(dftb + d + (d >> 1), d >> 1);
	DFT_fr_2(dftb + d, d);
	
	std::copy_n(C, d >> 1, dftc), reset(dftc + (d >> 1), d >> 1);
	DFT_fr_2(dftc, d);
	std::copy_n(C + (d >> 1), d >> 1, dftc + d), reset(dftc + d + (d >> 1), d >> 1);
	DFT_fr_2(dftc + d, d);
	
	for (int i = 0; i != d; ++i)
		dftc[d + i] = (static_cast<uint64>(dftc[d + i].v) * dftb[i].v + static_cast<uint64>(dftc[i].v) * dftb[d + i].v) % Mod;
	for (int i = 0; i != d; ++i)
		dftc[i] *= dftb[i];
	IDFT_fr(dftc, d), IDFT_fr(dftc + d, d);
	for (int i = 0; i != d >> 1; ++i)
		dftc[(d >> 1) + i] += dftc[d + i];
	
	std::copy_n(dftc, d, B);
	
	reset(dftc + d, d);
	DFT_fr_2(dftc, d * 2);
	std::copy_n(A, d * 2, dfta);
	DFT_fr_2(dfta, d * 2);
	for (int i = 0; i != d * 2; ++i)
		dftc[i] *= dfta[i];
	IDFT_fr(dftc, d * 2);
	for (int i = d; i != d * 2; ++i)
		dftc[i] = C[i] - dftc[i];
	
	std::copy_n(dftc + d + (d >> 1), d >> 1, dftc), reset(dftc + (d >> 1), d >> 1);
	DFT_fr_2(dftc, d);
	reset(dftc + d + (d >> 1), d >> 1);
	DFT_fr_2(dftc + d, d);
	for (int i = 0; i != d; ++i)
		dftc[i] = (static_cast<uint64>(dftc[i].v) * dftb[i].v + static_cast<uint64>(dftc[d + i].v) * dftb[d + i].v) % Mod;
	for (int i = 0; i != d; ++i)
		dftc[d + i] *= dftb[i];
	IDFT_fr(dftc, d), IDFT_fr(dftc + d, d);
	
	std::copy_n(B, d, res);
	std::copy_n(dftc + d, d >> 1, res + d);
	for (int i = 0; i != d >> 1; ++i)
		res[d + (d >> 1) + i] = dftc[d + (d >> 1) + i] + dftc[i];
	
	_M_pos += L * 3 + (L >> 1);
}

void Sqrt(const Z C[], const Z r0, Z res[], const int L)
{
	if (L == 1)
	{
		res[0] = r0;
		return;
	}
	if (L == 2)
	{
		Z r1 = C[1] * Rec(r0 + r0);
		res[0] = r0, res[1] = r1;
		return;
	}
	Z *A = _M_pos -= L;
	Z *B = _M_pos -= L >> 1;
	Z *dfta = _M_pos -= L;
	Z *dftb = _M_pos -= L;
	A[0] = r0;
	B[0] = Rec(A[0]);
	dfta[0] = r0;
	for (int d = 1; d != L >> 1; d *= 2)
	{
		for (int i = 0; i != d; ++i)
			dfta[i] *= dfta[i];
		IDFT_fr(dfta, d);
		for (int i = 0; i != d; ++i)
			dfta[i] = C[i] + C[d + i] - dfta[i];
		
		reset(dfta + d, d);
		DFT_fr_2(dfta, d * 2);
		
		std::copy_n(B, d, dftb), reset(dftb + d, d);
		DFT_fr_2(dftb, d * 2);
		
		for (int i = 0; i != d * 2; ++i)
			dfta[i] *= dftb[i];
		IDFT_fr(dfta, d * 2);
		
		for (int i = 0; i != d; ++i)
			A[d + i] = (dfta[i].v & 1 ? dfta[i].v + Mod : dfta[i].v) / 2;
		
		
		std::copy_n(A, d * 2, dfta);
		DFT_fr_2(dfta, d * 2);
		for (int i = 0; i != d; ++i)
			dfta[d * 2 + i] = norm_2(mult_Shoup_2(A[i].v, w[d * 2 + i], w_q[d * 2 + i]) + mult_Shoup_2(A[d + i].v, w[d * 2 + d + i], w_q[d * 2 + d + i]));
		DFT_fr_2(dfta + d * 2, d);
		
//		std::copy_n(B, d, dftb), reset(dftb + d, d);
//		DFT_fr_2(dftb, d * 2);
		for (int i = 0; i != d; ++i)
			dftb[d * 2 + i] = mult_Shoup_2(B[i].v, w[d * 2 + i], w_q[d * 2 + i]);
		DFT_fr_2(dftb + d * 2, d);
		
		if (d != L >> 2)
		{
			for (int i = 0; i != d * 3; ++i)
				dftb[i] *= dfta[i] * dftb[i];
		}
		else
		{
			for (int i = d * 2; i != d * 3; ++i)
				dftb[i] *= dfta[i] * dftb[i];
			std::copy_n(dftb, d * 2, dfta + d * 2);
			for (int i = 0; i != d * 2; ++i)
				dftb[i] *= dfta[i] * dftb[i];
		}
		IDFT_fr(dftb, d * 2), IDFT_fr(dftb + d * 2, d);
		
		for (int i = 1; i != d; ++i)
			dftb[d * 2 + i] = mult_Shoup(Mod - dftb[d * 2 + i].v, w[d * 2 + d * 2 - i], w_q[d * 2 + d * 2 - i]);
		for (int i = 0; i != d; ++i)
		{
			Z x = mult_Shoup(dftb[i].v + dftb[d * 2 + i].v + (Mod - B[i].v) * 2, w[3], w_q[3]) - dftb[d + i];
			B[d + i] = (x.v & 1 ? x.v + Mod : x.v) / 2;
		}
	}
	int d = L >> 1;
	
	std::copy_n(dfta + d, d, dftb);
	
	for (int i = 0; i != d; ++i)
		dfta[i] *= dfta[i];
	IDFT_fr(dfta, d);
	for (int i = 0; i != d; ++i)
		dfta[i] = C[i] + C[d + i] - dfta[i];
	
	std::copy_n(dfta + (d >> 1), d >> 1, dfta + d), reset(dfta + d + (d >> 1), d >> 1);
	DFT_fr_2(dfta + d, d);
	reset(dfta + (d >> 1), d >> 1);
	DFT_fr_2(dfta, d);
	
	std::copy_n(B + (d >> 1), d >> 1, dftb + d), reset(dftb + d + (d >> 1), d >> 1);
	DFT_fr_2(dftb + d, d);
	
	for (int i = 0; i != d; ++i)
		dfta[d + i] = (static_cast<uint64>(dfta[d + i].v) * dftb[i].v + static_cast<uint64>(dfta[i].v) * dftb[d + i].v) % Mod;
	for (int i = 0; i != d; ++i)
		dfta[i] *= dftb[i];
	IDFT_fr(dfta, d), IDFT_fr(dfta + d, d);
	for (int i = 0; i != d >> 1; ++i)
		dfta[(d >> 1) + i] += dfta[d + i];
	
	for (int i = 0; i != d; ++i)
		A[d + i] = (dfta[i].v & 1 ? dfta[i].v + Mod : dfta[i].v) / 2;
	
	std::copy_n(A, L, res);
	
	_M_pos += L * 3 + (L >> 1);
}

inline void Der(const Z A[], Z res[], const int L)
{
	for (int i = 1; i != L; ++i)
		res[i - 1] = A[i] * i;
	res[L - 1] = 0;
}

inline void Int(const Z A[], Z res[], const int L)
{
	for (int i = L - 1; i; --i)
		res[i] = A[i - 1] * _Rec[i];
	res[0] = 0;
}

inline void Log(const Z A[], Z res[], const int L)
{
	Z *der = _M_pos -= L;
	Der(A, der, L);
	Quo(A, der, der, L);
	Int(der, res, L);
	_M_pos += L;
}

int L;
Z A[Max_size], F[Max_size], pre[Max_size];

typedef long long LL;

const int mod = 998244353;

int main()
{
    int n, k, a, b; scanf("%d%d%d%d", &n, &k, &a, &b);
    A[0].v = 1, A[1].v = (-2 * a - (LL)4 * k * b) % mod, A[1].v = (A[1].v + mod) % mod, A[2].v = (LL)a * a % mod; 
	for (L = 1; L < n + 1; L <<= 1)
		;
	init_w(L);
	
	Sqrt(A, 1, A, L); Z inv = Power(2 * b % Mod, Mod - 2);
	
	for (int i = 1; i <= n; i++) F[i] = -A[i];
	
	F[0] = F[0] + 1, F[1] = F[1] - a;
	
	for (int i = 1; i <= n; i++) {
	    F[i] = F[i] * inv;
	    pre[i] = pre[i - 1] + F[i] * F[i];
    }
    
    int q; scanf("%d", &q);
    while (q--) {
        int l, r; scanf("%d%d", &l, &r);
        printf("%d\n", (pre[r] - pre[l - 1]).v);
    }
	
	return 0;
}
