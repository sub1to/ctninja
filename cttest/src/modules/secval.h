/*
	Copyright 2025-9999 sub1to

	This file is part of CTNinja

	CTNinja is free software; See LICENSE.txt or https://opensource.org/license/mit
*/

#pragma once

namespace secval
{
	typedef ctninja::SecureValue32<float>		SV32_Float;
	typedef ctninja::SecureValue32<uint32_t>	SV32_U32;
	typedef ctninja::SecureValue32<int32_t>		SV32_I32;

#ifdef _M_X64
	typedef ctninja::SecureValue64<BYTE*>		SVP_BYTE;
#else
	typedef ctninja::SecureValue32<BYTE*>		SVP_BYTE;
#endif // _M_X64

	#define ASTEST(t, s) if(!(t)) { test->err = s; return false; }

	void	reg()
	{
		REGISTER_TEST("ctninja::SecureValue -> Comparison", [](UNIT_TEST* test)->bool{
			float			fRaw;
			SV32_Float		fSec;

			fRaw	= 1234.5678f;
			fSec	= fRaw;

			BCASS(fSec == fRaw);
			BCASS(fSec <= fRaw);
			BCASS(fSec >= fRaw);

			fRaw += 5.f;

			BCASS(fSec != fRaw);
			BCASS(fSec <= fRaw);
			BCASS(fRaw >= fSec);
			BCASS(fSec < fRaw);
			BCASS(fRaw > fSec);

			fRaw -= 10.f;

			BCASS(fSec != fRaw);
			BCASS(fSec >= fRaw);
			BCASS(fRaw <= fSec);
			BCASS(fSec > fRaw);
			BCASS(fRaw < fSec);

			return true;
		});

		REGISTER_TEST("ctninja::SecureValue -> Obfuscation", [](UNIT_TEST* test)->bool{
			uint32_t		ulKey;
			uint32_t		ulVal;
			float			fRaw;
			SV32_Float		fSec;

			fRaw	= 1234.5678f;
			fSec	= fRaw;
			ulKey	= fSec._dbg_get_key();
			ulVal	= fSec._dbg_get_val_u32();

			// check if the key and obfuscated val are still the same
			BCASS(ulKey == fSec._dbg_get_key());
			BCASS(ulVal == fSec._dbg_get_val_u32());

			// the accessor should re-roll the key
			BCASS(fSec == fRaw);

			// check if the key and obfuscated val have changed
			BCASS(ulKey != fSec._dbg_get_key());
			BCASS(ulVal != fSec._dbg_get_val_u32());

			// check if the stored value is still valid
			BCASS(fSec == fRaw);

			// check if assignment rerolls
			ulKey	= fSec._dbg_get_key();
			ulVal	= fSec._dbg_get_val_u32();
			fSec	+= 2.f;
			fRaw	+= 2.f;

			// check if the key and obfuscated val have changed
			BCASS(ulKey != fSec._dbg_get_key());
			BCASS(ulVal != fSec._dbg_get_val_u32());

			// check if the stored value is still valid
			BCASS(fSec == fRaw);

			return true;
		});

		REGISTER_TEST("ctninja::SecureValue -> Assignment", [](UNIT_TEST* test)->bool{
			uint32_t		ulRaw;
			SV32_U32		ulSec;

			ulRaw	= 0xdeadbeef;
			ulSec	= ulRaw;

			ulSec	-= 3;
			ulRaw	-= 3;
			ASTEST(ulSec == ulRaw && ulRaw == 0xdeadbeec, "SecureValue -> -=")

			ulSec	+= 5;
			ulRaw	+= 5;
			ASTEST(ulSec == ulRaw && ulRaw == 0xdeadbef1, "SecureValue -> +=");

			ulSec	/= 2;
			ulRaw	/= 2;
			ASTEST(ulSec == ulRaw && ulRaw == 0x6f56df78, "SecureValue -> /=");

			ulSec	%= 0xbeef;
			ulRaw	%= 0xbeef;
			ASTEST(ulSec == ulRaw && ulRaw == 0x1140, "SecureValue -> %=");

			ulSec	*= 2;
			ulRaw	*= 2;
			ASTEST(ulSec == ulRaw && ulRaw == 0x2280, "SecureValue -> *=");

			ulSec	^= 0xbeefdead;
			ulRaw	^= 0xbeefdead;
			ASTEST(ulSec == ulRaw && ulRaw == 0xbeeffc2d, "SecureValue -> ^=");

			ulSec	|= 0xbeefdead;
			ulRaw	|= 0xbeefdead;
			ASTEST(ulSec == ulRaw && ulRaw == 0xbeeffead, "SecureValue -> |=");

			ulSec	&= 0xbeefdead;
			ulRaw	&= 0xbeefdead;
			ASTEST(ulSec == ulRaw && ulRaw == 0xbeefdead, "SecureValue -> |=");

			ulSec	<<= 5;
			ulRaw	<<= 5;
			ASTEST(ulSec == ulRaw && ulRaw != 0, "SecureValue -> <<=");

			ulSec	>>= 3;
			ulRaw	>>= 3;
			ASTEST(ulSec == ulRaw && ulRaw != 0, "SecureValue -> >>=");

			return true;
		});

		REGISTER_TEST("ctninja::SecureValue -> Arithmatic Unsigned", [](UNIT_TEST* test)->bool{
			uint32_t		ulRaw;
			SV32_U32		ulSec;

			ulRaw	= 0xdeadbeef;
			ulSec	= ulRaw;

			#pragma warning( suppress: 4146 )
			BCASS((-(ulSec)) == (-(ulRaw)));

			BCASS((ulSec - 0xdeadu) == (ulRaw - 0xdeadu));
			BCASS((ulSec + 0xdeadu) == (ulRaw + 0xdeadu));
			BCASS((ulSec / 4u) == (ulRaw / 4u));
			BCASS((ulSec % 0xbeefu) == (ulRaw % 0xbeefu));
			BCASS((ulSec * 2u) == (ulRaw * 2u));
			BCASS((ulSec ^ 0xbeefdeadu) == (ulRaw ^ 0xbeefdeadu));
			BCASS((ulSec | 0xbeefdeadu) == (ulRaw | 0xbeefdeadu));
			BCASS((ulSec & 0xbeefdeadu) == (ulRaw & 0xbeefdeadu));
			BCASS((ulSec << 5u) == (ulRaw << 5u));
			BCASS((ulSec >> 5u) == (ulRaw >> 5u));

			return true;
		});

		REGISTER_TEST("ctninja::SecureValue -> Arithmatic Signed", [](UNIT_TEST* test)->bool{
			int32_t			iRaw;
			SV32_I32		iSec;

			iRaw	= 0xdeadbeef;
			iSec	= iRaw;

			BCASS((-(iSec)) == (-(iRaw)));

			BCASS((iSec - 0xdead) == (iRaw - 0xdead));
			BCASS((iSec + 0xdead) == (iRaw + 0xdead));
			BCASS((iSec / 4) == (iRaw / 4));
			BCASS((iSec % 0xbeef) == (iRaw % 0xbeef));
			BCASS((iSec * 2) == (iRaw * 2));
			BCASS((iSec ^ 0xeefdead) == (iRaw ^ 0xeefdead));
			BCASS((iSec | 0xeefdead) == (iRaw | 0xeefdead));
			BCASS((iSec & 0xeefdead) == (iRaw & 0xeefdead));
			BCASS((iSec << 5) == (iRaw << 5));
			BCASS((iSec >> 5) == (iRaw >> 5));

			return true;
		});

		REGISTER_TEST("ctninja::SecureValue -> Pointers", [](UNIT_TEST* test)->bool{
			static BYTE		buf[0x20];

			BYTE*		pRaw;
			SVP_BYTE	pSec;

			memset(buf, 0, sizeof(buf));

			pRaw	= buf;
			pSec	= buf;

			BCASS(pSec == pRaw);

			pRaw[0]	= 0x1f;

			BCASS(pRaw[0] == 0x1f);
			BCASS(*pSec == 0x1f);
			BCASS(pSec[0] == 0x1f);

			pSec[1] = 0x2e;

			BCASS(pRaw[1] == 0x2e);
			BCASS(*(pSec + 1) == 0x2e);

#ifdef _M_X64
			BCASS((pSec._dbg_get_key() & 0xFFFFFFFF'00000000) != 0);
#endif // _M_X64

			return true;
		});
	}
}